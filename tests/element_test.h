#ifndef ELEMENTTEST_H
#define	ELEMENTTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "json/json.h"

class ElementTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ElementTest);

  CPPUNIT_TEST(TestLoadFullElement);

  CPPUNIT_TEST_SUITE_END();

public:
  ElementTest();
  virtual ~ElementTest();
  void setUp();
  void tearDown();

private:
  void TestLoadFullElement();

  Status s_;
  json::Value* root_tag_ = NULL;
};

#endif	// ELEMENTTEST_H

