/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_ServerConfigTest_init = false;
#include "MyTestSuite.h"

static ServerConfigTest suite_ServerConfigTest;

static CxxTest::List Tests_ServerConfigTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ServerConfigTest( "MyTestSuite.h", 7, "ServerConfigTest", suite_ServerConfigTest, Tests_ServerConfigTest );

static class TestDescription_suite_ServerConfigTest_testServerConfigFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ServerConfigTest_testServerConfigFile() : CxxTest::RealTestDescription( Tests_ServerConfigTest, suiteDescription_ServerConfigTest, 14, "testServerConfigFile" ) {}
 void runTest() { suite_ServerConfigTest.testServerConfigFile(); }
} testDescription_suite_ServerConfigTest_testServerConfigFile;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
