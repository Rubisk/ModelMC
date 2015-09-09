#include "util_test.h"
#include "json/util.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(UtilTest);

UtilTest::UtilTest() {
}

UtilTest::~UtilTest() {
}

void UtilTest::setUp() {
}

void UtilTest::tearDown() {
}

void UtilTest::testFindType() {
  ValueType output;
  std::stringstream ss;
  Status s;

  ss.str("1");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kIntValue);
  ss.str("\"");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kStringValue);
  ss.str("t");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kBoolValue);
  ss.str("{");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kObjectValue);
  ss.str("[");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kVectorValue);
  ss.str("}");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s == kParseError);
}

void UtilTest::testLoadName() {
  std::string output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = LoadName(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == "my_name");
}

void UtilTest::testLoadValue() {
  Value* output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = LoadValue(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  std::string value_of;
  s = output->GetStringValue(&value_of);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(value_of == "my_name");
  delete output;
}

