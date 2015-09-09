#ifndef UTILTEST_H
#define	UTILTEST_H

#include <cppunit/extensions/HelperMacros.h>

class UtilTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(UtilTest);

  CPPUNIT_TEST(testFindType);
  CPPUNIT_TEST(testLoadName);
  CPPUNIT_TEST(testLoadValue);

  CPPUNIT_TEST_SUITE_END();

public:
  UtilTest();
  virtual ~UtilTest();
  void setUp();
  void tearDown();

private:
  void testFindType();
  void testLoadName();
  void testLoadValue();

};

#endif	// UTILTEST_H

