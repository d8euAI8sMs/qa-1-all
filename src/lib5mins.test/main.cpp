#include <fstream>

#include "runner.cpp"

#include <cxxtest/XmlPrinter.h>

class WorldMetadataAwareXmlPrinter : public CxxTest::XmlPrinter
{
private:
    std::ostringstream os;
    CXXTEST_STD(ostream) &o;
public:

    WorldMetadataAwareXmlPrinter(CXXTEST_STD(ostream) &o = CXXTEST_STD(cout)) :
        XmlPrinter(os), o(o) {}

    void leaveWorld(const CxxTest::WorldDescription& desc)
    {
        XmlPrinter::leaveWorld(desc);
        auto str = os.str();
        auto pos = str.find(">", str.find("?>") + 2);
        o << str.substr(0, pos)
            .replace(str.find("UTF-8"), 5, "windows-1251")
            << " author=\"Василевский Александр\"";
        o << str.substr(pos);
        o.flush();
    }

    std::string currentDateTimeStr()
    {
        std::string retVal;
        const time_t now(time(NULL));
        char current_date_string[27];

        if (ctime_s(current_date_string, sizeof(current_date_string)-1, &now) == 0)
        {
            retVal = current_date_string;
            retVal.erase(retVal.find_last_not_of(" \n\r\t")+1); // trim trailing whitespace
        }

        return retVal;
    }
};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "RU");

    int status;

    bool xml = false;

    /* remove custom args because cxxtest doesn't like them */

    auto argv0 = new char * [argc];
    auto argc0 = argc;

    for (size_t i = 0, j = 0; i < argc; ++i)
    {
        argv0[j++] = argv[i];
        if (strcmp(argv[i], "-a") == 0) { xml = true; --argc0; --j; }
        if (strcmp(argv[i], "-b") == 0) { xml = false; --argc0; --j; }
    }

    CxxTest::RealWorldDescription::_worldName = "lib5mins";

    /* conditionally print test results to xml or to console */

    if (xml)
    {
        std::ofstream fs("report.xml");
        WorldMetadataAwareXmlPrinter tmp(fs);
        status = CxxTest::Main < CxxTest::XmlPrinter > (tmp, argc0, argv0);
    }
    else
    {
        CxxTest::ErrorPrinter tmp;
        status = CxxTest::Main < CxxTest::ErrorPrinter > (tmp, argc0, argv0);
    }

    return status;
}