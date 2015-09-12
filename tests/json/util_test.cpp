#include "util_test.h"
#include "json/json.h"
#include "json/util.h"
#include "json/object_value.h"
#include "json/vector_value.h"
#include "json/simple_values.h"

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

void UtilTest::TestFindType() {
  ValueType output;
  std::stringstream ss;
  Status s;

  ss.str("1");
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
  s = LoadValue(ss, &output);
  CPPUNIT_ASSERT(s.IsOk());
  std::string value_of;
  s = output->GetStringValue(&value_of);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(value_of == "my_name");
  delete output;
}

void UtilTest::TestFindValueForPath() {
  Status s;
  Value** output;

  Value* value = new ObjectValue();
  Value* first_layer = new VectorValue();
  Value* second_layer = new ObjectValue();
  Value* third_layer = new ObjectValue();
  Value* fourth_layer = new VectorValue();
  Value* fifth_layer = new ObjectValue();
  Value* final_value = new StringValue("Find me please!");

  s = value->GetChild("first_key", output);
  CPPUNIT_ASSERT(s.IsOk());
  *output = first_layer;
  s = first_layer->GetChild(1, output);
  CPPUNIT_ASSERT(s.IsOk());
  *output = second_layer;
  s = second_layer->GetChild("third_key", output);
  CPPUNIT_ASSERT(s.IsOk());
  *output = third_layer;
  s = third_layer->GetChild("fourth_key", output);
  CPPUNIT_ASSERT(s.IsOk());
  *output = fourth_layer;
  s = fourth_layer->GetChild(5, output);
  CPPUNIT_ASSERT(s.IsOk());
  *output = fifth_layer;
  s = fifth_layer->GetChild("final_key", output);
  CPPUNIT_ASSERT(s.IsOk());
  *output = final_value;

  std::string s_keys[] = {"first_key", "third_key", "fourth_key", "final_key"};
  int i_keys[] = {1, 5};
  std::vector<void*> path = {&s_keys[0], &i_keys[0], &s_keys[1], &s_keys[2], &i_keys[1], &s_keys[3]};
  s = FindValueForPath(value, path, *output);
  CPPUNIT_ASSERT(s.IsOk());
  std::string string_output;
  s = (*output)->GetStringValue(&string_output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(string_output == "Find me please!");
  delete value;
}