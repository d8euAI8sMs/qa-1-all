#include "quadeq.hpp"

#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(QuadEqTest);

int main(int argc, char ** argv)
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::OFileStream o;
    bool toXml = false;
    for (int i = 1; i < argc; ++i)
        if (strcmp(argv[i], "-xml") == 0) toXml = true;
    if (toXml)
    {
        o.open("result.xml");
        runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), o));
    }
    else
        runner.setOutputter(new CppUnit::TextOutputter(&runner.result(), std::cout));
	bool result = runner.run();
	return result ? 0 : 1;
}
