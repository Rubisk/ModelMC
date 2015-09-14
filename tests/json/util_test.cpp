#include "util_test.h"
#include "json/json.h"
#include "json/util.h"
#include "json/object_value.h"
#include "json/vector_value.h"
#include "json/simple_values.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(UtilTest);

UtilTest::UtilTest() { }

UtilTest::~UtilTest() { }

void UtilTest::setUp() { }

void UtilTest::tearDown() { }

void UtilTest::TestFindType() {
  ValueType output;
  std::stringstream ss;
  Status s;

  ss.str("1");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == kIntValue);
  ss.str("-1");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == kIntValue);
  ss.str("\"");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == kStringValue);
  ss.str("t");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == kBoolValue);
  ss.str("{");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == kObjectValue);
  ss.str("[");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == kVectorValue);
  ss.str("}");
  s = FindType(ss, &output);
  CPPUNIT_ASSERT(!s.IsOk());
}

void UtilTest::TestLoadName() {
  std::string output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = LoadName(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output == "my_name");
}

void UtilTest::TestLoadValue() {
  Value* output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = LoadValue(ss, output);
  CPPUNIT_ASSERT(s.IsOk());
  std::string value_of;
  s = output->GetStringValue(&value_of);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(value_of == "my_name");
  delete output;
}