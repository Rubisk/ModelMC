#ifndef SIMPLEVALUESTEST_H
#define	SIMPLEVALUESTEST_H

#include <sstream>
#include <cppunit/extensions/HelperMacros.h>

#include "json/simple_values.h"

class SimpleValuesTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(SimpleValuesTest);

  CPPUNIT_TEST(TestGetBool);
  CPPUNIT_TEST(TestLoadFromStreamBool);
  CPPUNIT_TEST(TestSaveToStreamBool);
  CPPUNIT_TEST(TestGetString);
  CPPUNIT_TEST(TestLoadFromStreamString);
  CPPUNIT_TEST(TestSaveToStreamString);
  CPPUNIT_TEST(TestGetInt);
  CPPUNIT_TEST(TestLoadFromStreamInt);
  CPPUNIT_TEST(TestSaveToStreamInt);

  CPPUNIT_TEST_SUITE_END();

public:
  SimpleValuesTest();
  virtual ~SimpleValuesTest();
  void setUp();
  void tearDown();

private:
  void TestGetBool();
  void TestLoadFromStreamBool();
  void TestSaveToStreamBool();
  void TestGetString();
  void TestLoadFromStreamString();
  void TestSaveToStreamString();
  void TestGetInt();
  void TestLoadFromStreamInt();
  void TestSaveToStreamInt();

  json::IntValue* int_;
  json::StringValue* string_;
  json::BoolValue* bool_;
  std::stringstream string_stream_;
  Status s_;

  void AssertRemainder_(std::string remainder);
};

#endif	// SIMPLEVALUESTEST_H

