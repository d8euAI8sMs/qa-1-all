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
        o << str.substr(0, pos) << " author=\"alexander василевский vasilevsky\"";
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

    WorldMetadataAwareXmlPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "lib5mins";
    status = CxxTest::Main< CxxTest::XmlPrinter >( tmp, argc, argv );

    return status;
}