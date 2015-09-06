#include "json_object_test.h"

#include "src/json/json.h"
#include "src/json/object_value.h"
#include "src/json/simple_values.h"
#include "debug_new.h"


using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(JsonObjectTest);

JsonObjectTest::JsonObjectTest() {

}

JsonObjectTest::~JsonObjectTest() {

}

void JsonObjectTest::setUp() {
  Value* int_value = new IntValue(99);
  Value* string_value = new StringValue("a_value");
  ValueMap* value_map = new ValueMap();

  value_map->insert(std::pair<std::string, Value*>("int", int_value));
  value_map->insert(std::pair<std::string, Value*>("string", string_value));

  object_ = new ObjectValue(value_map);
}

void JsonObjectTest::tearDown() {
  delete object_;
}

void JsonObjectTest::testAccessAnExistingMember() {
  CPPUNIT_ASSERT((*object_)["int"]->as_int() == 99);
  CPPUNIT_ASSERT((*object_)["string"]->as_string() == "a_value");
  *(*object_)["int"] = 5;
  *(*object_)["string"] = "a_new_value";
  CPPUNIT_ASSERT((*object_)["int"]->as_int() == 5);
  CPPUNIT_ASSERT((*object_)["string"]->as_string() == "a_new_value");
}

void JsonObjectTest::testAddAMember() {
  Value* value = new StringValue("A");

  (*object_)["new_string"] = value;
  CPPUNIT_ASSERT((*object_)["new_string"]->as_string() == "A");
}

