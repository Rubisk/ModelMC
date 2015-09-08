#ifndef OBJECTVALUETEST_H
#define	OBJECTVALUETEST_H

#include <cppunit/extensions/HelperMacros.h>

class ObjectValueTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ObjectValueTest);

  CPPUNIT_TEST(testGet);
  CPPUNIT_TEST(testLoadFrom);
  CPPUNIT_TEST(testSave);

  CPPUNIT_TEST_SUITE_END();

public:
  ObjectValueTest();
  virtual ~ObjectValueTest();
  void setUp();
  void tearDown();

private:
  void testGet();
  void testLoadFrom();
  void testSave();

};

#endif	// OBJECTVALUETEST_H

