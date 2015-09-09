#include "object_values_test.h"
#include "src/json/object_value.h"
#include "src/json/simple_values.h"

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
  Status s = value->GetChild(key, valueptr);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(*valueptr == NULL);

  *valueptr = new IntValue(5);
  Value** new_valueptr;
  CPPUNIT_ASSERT(value->GetChild(key, new_valueptr) == kOk);
  int32_t output;
  CPPUNIT_ASSERT((*new_valueptr)->GetIntValue(&output) == kOk);
  CPPUNIT_ASSERT(output == 5);
  delete value;
}

void ObjectValueTest::testLoadFrom() {
  std::stringstream ss;
  ss.str("{\"int_value\":5,\"string_value\":\"string\"}{|)");
  Value* value = new ObjectValue();
  Status s = value->LoadValue(ss);
  CPPUNIT_ASSERT(s == kOk);

  std::stringstream os;
  ss >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == "{|)");

  Value** output;

  int int_value;
  s = value->GetChild("int_value", output);
  CPPUNIT_ASSERT(s == kOk);
  s = (*output)->GetIntValue(&int_value);
  CPPUNIT_ASSERT(s == kOk);
  std::string string_value;
  s = value->GetChild("string_value", output);
  CPPUNIT_ASSERT(s == kOk);
  s = (*output)->GetStringValue(&string_value);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(int_value == 5);
  CPPUNIT_ASSERT(string_value == "string");
  delete value;
}

void ObjectValueTest::testSave() {
  const std::string test_str = "{\"int_value\":5,\"string_value\":\"string\"}";
  std::stringstream input_stream;
  input_stream.str(test_str);
  Value* value = new ObjectValue();
  Status s = value->LoadValue(input_stream);
  CPPUNIT_ASSERT(s == kOk);

  std::stringstream output_stream;
  value->SaveValue(&output_stream);
  CPPUNIT_ASSERT(output_stream.str() == test_str);
  delete value;
}

