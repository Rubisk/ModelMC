#include "util_test.h"
#include "src/json/util.h"

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
  s = findType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kIntValue);
  ss.str("\"");
  s = findType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kStringValue);
  ss.str("t");
  s = findType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kBoolValue);
  ss.str("{");
  s = findType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kObjectValue);
  ss.str("[");
  s = findType(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == kVectorValue);
  ss.str("}");
  s = findType(ss, &output);
  CPPUNIT_ASSERT(s == kParseError);
}

void UtilTest::testLoadName() {
  std::string output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = loadName(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == "my_name");
}

void UtilTest::testLoadValue() {
  Value* output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = loadValue(ss, &output);
  CPPUNIT_ASSERT(s == kOk);
  std::string value_of;
  s = output->as_string(&value_of);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(value_of == "my_name");
  delete output;
}

