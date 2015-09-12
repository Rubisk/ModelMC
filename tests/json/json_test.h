#ifndef JSONTEST_H
#define	JSONTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "json/json.h"

// Only used to be able to test json::Value default behavior;

class TestValue : public json::Value {

  json::ValueType GetValueType() {
  }

  void SaveToStream(std::ostream* output) {
  }

  Status LoadFromStream(std::istream &stream) {
  }
};

class JsonTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(JsonTest);

  CPPUNIT_TEST(testAs_bool);
  CPPUNIT_TEST(testAs_int);
  CPPUNIT_TEST(testAs_string);
  CPPUNIT_TEST(testGet);
  CPPUNIT_TEST(testSaveFromFile);
  CPPUNIT_TEST(testLoadFromFile);

  CPPUNIT_TEST_SUITE_END();

public:
  JsonTest();
  virtual ~JsonTest();
  void setUp();
  void tearDown();

private:
  void testAs_bool();
  void testAs_int();
  void testAs_string();
  void testGet();
  void testSaveFromFile();
  void testLoadFromFile();

};

#endif	// JSONTEST_H

