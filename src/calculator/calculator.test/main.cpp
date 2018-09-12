#include "quadeq.hpp"
#include "quadeq_bbd.hpp"

#include <cppunit/XmlOutputter.h>
#include <cppunit/XmlOutputterHook.h>
#include <cppunit/tools/XmlDocument.h>
#include <cppunit/tools/XmlElement.h>
#include <cppunit/TextOutputter.h>
#include <iostream>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(QuadEqTest, QuadEqTest::name());
CPPUNIT_REGISTRY_ADD_TO_DEFAULT(QuadEqTest::name());
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(QuadEqBBDTest, QuadEqBBDTest::name());
CPPUNIT_REGISTRY_ADD_TO_DEFAULT(QuadEqBBDTest::name());

class TestSuiteAttributeAwareXmlOutputterHook : public CppUnit::XmlOutputterHook
{
private:
    CppUnit::TestSuite * _suite;
public:
    TestSuiteAttributeAwareXmlOutputterHook(CppUnit::TestSuite * s)
        : _suite(s)
    {
    }
public:
    void beginDocument(CppUnit::XmlDocument *document) override
    {
        auto n = new CppUnit::XmlElement("Suite", _suite->getName());
        auto a = new CppUnit::XmlElement("Author", "Alexander Vasilevsky");
        auto d = new CppUnit::XmlElement("Date",   local_date());
        document->rootElement().addElement(n);
        document->rootElement().addElement(a);
        document->rootElement().addElement(d);
    }
};

int main(int argc, char ** argv)
{
	CppUnit::TextTestRunner runner;

    bool bbd = true;
    for (int i = 1; i < argc; ++i)
        if (strcmp(argv[i], "-no-bbd") == 0) bbd = false;

    auto test = dynamic_cast < CppUnit::TestSuite * > (
        CppUnit::TestFactoryRegistry::getRegistry(
            bbd ? QuadEqBBDTest::name() : QuadEqTest::name()).makeTest());

	runner.addTest(test);

    CppUnit::OFileStream o;
    bool toXml = false;
    for (int i = 1; i < argc; ++i)
        if (strcmp(argv[i], "-xml") == 0) toXml = true;
    if (toXml)
    {
        o.open("result.xml");
        auto xo = new CppUnit::XmlOutputter(&runner.result(), o);
        xo->setStyleSheet("report.xsl");
        xo->addHook(new TestSuiteAttributeAwareXmlOutputterHook(test));
        runner.setOutputter(xo);
    }
    else
        runner.setOutputter(new CppUnit::TextOutputter(&runner.result(), std::cout));
	bool result = runner.run();
	return result ? 0 : 1;
}
