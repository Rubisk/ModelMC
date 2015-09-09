#ifndef VECTORVALUETEST_H
#define	VECTORVALUETEST_H

#include <cppunit/extensions/HelperMacros.h>

class VectorValueTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(VectorValueTest);

  CPPUNIT_TEST(testGet);
  CPPUNIT_TEST(testLoadFrom);
  CPPUNIT_TEST(testSave);

  CPPUNIT_TEST_SUITE_END();

public:
  VectorValueTest();
  virtual ~VectorValueTest();
  void setUp();
  void tearDown();

private:
  void testGet();
  void testLoadFrom();
  void testSave();

};

#endif	// VECTORVALUETEST_H

