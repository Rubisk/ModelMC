#ifndef EXTRACTJSONTEST_H
#define	EXTRACTJSONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ExtractJsonTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ExtractJsonTest);

  CPPUNIT_TEST(TestFindValueForPath);
  CPPUNIT_TEST(TestFindValueForInvalidPath);
  CPPUNIT_TEST(TestLoadIntArray);

  CPPUNIT_TEST_SUITE_END();

public:
  ExtractJsonTest();
  virtual ~ExtractJsonTest();
  void setUp();
  void tearDown();

private:
  void TestFindValueForPath();
  void TestFindValueForInvalidPath();
  void TestLoadIntArray();

};

#endif	// EXTRACTJSONTEST_H

