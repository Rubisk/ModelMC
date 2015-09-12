#ifndef UTILTEST_H
#define	UTILTEST_H

#include <cppunit/extensions/HelperMacros.h>

class UtilTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(UtilTest);

  CPPUNIT_TEST(TestFindType);
  CPPUNIT_TEST(TestLoadName);
  CPPUNIT_TEST(TestLoadValue);
  CPPUNIT_TEST(TestFindValueForPath);

  CPPUNIT_TEST_SUITE_END();

public:
  UtilTest();
  virtual ~UtilTest();
  void setUp();
  void tearDown();

private:
  void TestFindType();
  void TestLoadName();
  void TestLoadValue();
  void TestFindValueForPath();
};

#endif	// UTILTEST_H

