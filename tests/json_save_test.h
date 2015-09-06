#ifndef JSON_SAFE_TEST_H
#define	JSON_SAFE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "src/json/json.h"

class JsonSaveTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(JsonSaveTest);

  CPPUNIT_TEST(testSaveString);
  CPPUNIT_TEST(testSaveBoolean);
  CPPUNIT_TEST(testSaveInt);
  CPPUNIT_TEST(testSaveVector);
  CPPUNIT_TEST(testSaveObject);
  CPPUNIT_TEST(testSaveComplexObject);

  CPPUNIT_TEST_SUITE_END();

public:
  JsonSaveTest();
  virtual ~JsonSaveTest();
  void setUp();
  void tearDown();

private:
  void testSaveString();
  void testSaveBoolean();
  void testSaveInt();
  void testSaveVector();
  void testSaveObject();
  void testSaveComplexObject();

  json::Value* object_;
};


#endif	// JSON_SAFE_TEST_H

