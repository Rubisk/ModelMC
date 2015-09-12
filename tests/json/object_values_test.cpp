#include "object_values_test.h"
#include "json/object_value.h"
#include "json/simple_values.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(ObjectValueTest);

ObjectValueTest::ObjectValueTest() {
}

ObjectValueTest::~ObjectValueTest() {
}

void ObjectValueTest::setUp() {
}

void ObjectValueTest::tearDown() {
}

void ObjectValueTest::testGet() {
  const std::string key = "some_key";
  Value** valueptr;
  Value* value = new ObjectValue();
  CPPUNIT_ASSERT(value->GetValueType() == kObjectValue);
  Status s = value->GetChild(key, valueptr);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(*valueptr == NULL);

  *valueptr = new IntValue(5);
  Value** new_valueptr;
  CPPUNIT_ASSERT(value->GetChild(key, new_valueptr).IsOk());
  int32_t output;
  CPPUNIT_ASSERT((*new_valueptr)->GetIntValue(&output).IsOk());
  CPPUNIT_ASSERT(output == 5);
  delete value;
}

void ObjectValueTest::testLoadFrom() {
  std::stringstream ss;
  ss.str("{\"int_value\":5,\"string_value\":\"string\"}{|)");
  Value* value = new ObjectValue();
  Status s = value->LoadFromStream(ss);
  CPPUNIT_ASSERT(s.IsOk());

  std::stringstream os;
  ss >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == "{|)");

  Value** output;

  int int_value;
  s = value->GetChild("int_value", output);
  CPPUNIT_ASSERT(s.IsOk());
  s = (*output)->GetIntValue(&int_value);
  CPPUNIT_ASSERT(s.IsOk());
  std::string string_value;
  s = value->GetChild("string_value", output);
  CPPUNIT_ASSERT(s.IsOk());
  s = (*output)->GetStringValue(&string_value);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(int_value == 5);
  CPPUNIT_ASSERT(string_value == "string");
  delete value;
}

void ObjectValueTest::testSave() {
  const std::string test_str = "{\"int_value\":5,\"string_value\":\"string\"}";
  std::stringstream input_stream;
  input_stream.str(test_str);
  Value* value = new ObjectValue();
  Status s = value->LoadFromStream(input_stream);
  CPPUNIT_ASSERT(s.IsOk());

  std::stringstream output_stream;
  value->SaveToStream(&output_stream);
  CPPUNIT_ASSERT(output_stream.str() == test_str);
  delete value;
}

