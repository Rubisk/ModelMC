#ifndef ELEMENTTEST_H
#define	ELEMENTTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ElementTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ElementTest);

  CPPUNIT_TEST(testLoadElement);
  CPPUNIT_TEST(testLoadElement2);
  CPPUNIT_TEST(testSaveElement);
  CPPUNIT_TEST(testSaveElement2);

  CPPUNIT_TEST_SUITE_END();

public:
  ElementTest();
  virtual ~ElementTest();
  void setUp();
  void tearDown();

private:
  void testLoadElement();
  void testLoadElement2();
  void testSaveElement();
  void testSaveElement2();

};

#endif	// ELEMENTTEST_H

