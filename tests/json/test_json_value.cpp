#include <fstream>
#include <gtest/gtest.h>

#include "json/value.h"

using namespace json;

class JsonValueTest : public testing::Test {
protected:
  void SetUp() {
    value_ = Value();
  }

  Value value_;
};

TEST_F(JsonValueTest, DefaultValue) {
  EXPECT_EQ(value_.GetType(), kNullValue);
}

TEST_F(JsonValueTest, ValueConstructValue) {
  std::unique_ptr<Value> int_value(new Value(5));
  EXPECT_EQ((int32_t) (*int_value), 5)
    << "Constructor for integer is broken.";

  std::unique_ptr<Value> string_value(new Value("some_string"));
  EXPECT_EQ((std::string) (*string_value), "some_string")
    << "Constructor for string is broken.";

  std::unique_ptr<Value> bool_value(new Value(false));
  EXPECT_EQ((bool) (*bool_value), false)
    << "Constructor for boolean is broken.";

  Value::Object object;
  object["key"] = std::make_shared<Value>();
  Value object_value(object);
  EXPECT_EQ(object_value["key"].GetType(), kNullValue)
    << "Constructor for object value is broken.";

  Value::Array array_(3);
  Value array_value(array_);
  EXPECT_EQ(array_value[2].GetType(), kNullValue)
    << "Constructor for array value is broken.";
}

TEST_F(JsonValueTest, IntValue) {
  int32_t output;
  EXPECT_NO_THROW(value_ = 5)
    << "Couldn't assign an integer.";
  EXPECT_EQ(value_.GetType(), kIntValue)
    << "Type didn't change properly.";
  EXPECT_NO_THROW(output = value_)
    << "Couldn't cast back to int properly.";
  EXPECT_EQ(output, 5)
    << "Int didn't have correct value.";
}

TEST_F(JsonValueTest, StringValue) {
  std::string output;
  EXPECT_NO_THROW(value_ = "first_string")
    << "Couldn't assign an string.";
  EXPECT_EQ(value_.GetType(), kStringValue)
    << "Value type isn't string.";
  EXPECT_NO_THROW(output = value_)
    << "Couldn't cast to string properly.";
  EXPECT_EQ(output, "first_string")
    << "String didn't have correct value.";
}

TEST_F(JsonValueTest, BoolValue) {
  bool output;
  EXPECT_NO_THROW(value_ = true)
    << "Couldn't assign a bool.";
  EXPECT_EQ(value_.GetType(), kBoolValue)
    << "Value type isn't bool.";
  EXPECT_NO_THROW(output = value_)
    << "Couldn't cast to bool properly.";
  EXPECT_EQ(output, true)
    << "Bool didn't have correct value.";
}

TEST_F(JsonValueTest, ObjectValue) {
  Value::Object empty_map;
  empty_map["preset_key"] = std::make_shared<Value>();
  ASSERT_NO_THROW(value_ = empty_map)
    << "Couldn't assign a map to a value.";
  EXPECT_THROW(value_["New empty value"], json_exception)
    << "Asking for non-existant value didn't throw.";

  Value &value = value_["preset_key"];
  EXPECT_EQ(value.GetType(), kNullValue)
    << "Couldn't get existing child.";
  value = "some_string";
  ASSERT_EQ(value.GetType(), kStringValue)
    << "Value didn't write properly";
  EXPECT_EQ(value_["preset_key"].GetType(), kStringValue)
    << "Couldn't edit existing child properly.";

  std::string string_value;
  ASSERT_NO_THROW(string_value = value_["preset_key"])
    << "Couldn't cast back to string properly.";
  EXPECT_EQ(string_value, "some_string")
    << "Edited value didn't have correct value.";
}

TEST_F(JsonValueTest, ArrayValue) {
  Value::Array empty_array(5);
  ASSERT_NO_THROW(value_ = empty_array)
    << "Couldn't assign an array to a value.";
  EXPECT_THROW(value_[5], json_exception)
    << "Asking for non-existant value didn't throw.";

  Value &value = value_[3];
  EXPECT_EQ(value.GetType(), kNullValue)
    << "Couldn't get existing child.";
  value = "some_string";
  ASSERT_EQ(value.GetType(), kStringValue)
    << "Value didn't write properly";
  EXPECT_EQ(value_[3].GetType(), kStringValue)
    << "Couldn't edit existing child properly.";

  std::string string_value;
  ASSERT_NO_THROW(string_value = value_[3])
    << "Couldn't cast back to string properly.";
  EXPECT_EQ(string_value, "some_string")
    << "Edited value didn't have correct value.";
}

TEST_F(JsonValueTest, CopyAssignValue) {
  value_ = Value(5);
  ASSERT_NO_THROW(value_ = value_)
    << "Failed to prevent self-assignment.";
  EXPECT_EQ((int32_t) value_, 5)
    << "Failed to copy int value.";
  value_ = Value("some_string");
  ASSERT_NO_THROW(value_ = value_)
    << "Failed to prevent self-assignment.";
  EXPECT_EQ((std::string) value_, "some_string")
    << "Failed to copy string value.";
  value_ = Value(true);
  ASSERT_NO_THROW(value_ = value_)
    << "Failed to prevent self-assignment.";
  EXPECT_EQ((bool) value_, true)
    << "Failed to copy bool value.";

  Value::Object object;
  object["key"] = std::make_shared<Value>(5);
  value_ = Value(object);
  ASSERT_NO_THROW(value_ = value_)
    << "Failed to prevent self-assignment.";
  EXPECT_EQ((int32_t) value_["key"], 5)
    << "Failed to copy object value.";

  Value::Array array_(3);
  array_[1] = std::make_shared<Value>(1);
  value_ = Value(array_);
  ASSERT_NO_THROW(value_ = value_)
    << "Failed to prevent self-assignment.";
  EXPECT_EQ((int32_t) value_[1], 1)
    << "Failed to copy array value.";

}

TEST_F(JsonValueTest, CopyConstructValue) {
  value_ = -1;
  std::unique_ptr<Value> value(new Value(value_));
  EXPECT_EQ((int32_t) *value, -1)
    << "Copy constructor is broken.";
}

TEST_F(JsonValueTest, AddToObjectValue) {
  Value::Object map_;
  map_["key_1"];
  map_["key_2"];
  value_ = Value(map_);
  value_.Add("key_3", 5);
  EXPECT_EQ((int32_t) value_["key_3"], 5)
    << "Couldn't add to an ObjectValue properly.";
}

TEST_F(JsonValueTest, AddToArrayValue) {
  Value::Array array_(5);
  value_ = Value(array_);
  value_.Append("some_string");
  EXPECT_EQ((std::string) value_[5], "some_string")
    << "Couldn't append to an ArrayValue properly.";
}

TEST_F(JsonValueTest, RemoveFromObjectValue) {
  Value::Object map_;
  map_["key 1"];
  map_["key 2"];
  value_ = Value(map_);
  value_["key 2"] = 5;
  value_.Remove("key 2");
  ASSERT_NO_THROW(value_.Remove("Invalid key."))
    << "Exception on removing invalid key.";
  ASSERT_THROW(value_["key 2"], json_exception)
    << "Value not removed properly.";
}

TEST_F(JsonValueTest, RemoveFromArrayValue) {
  Value::Array array_(5);
  value_ = Value(array_);
  value_.Remove(3);
  ASSERT_NO_THROW(value_.Remove(6))
    << "Exception on removing out of bounds.";
  ASSERT_THROW(value_[4], json_exception)
    << "Value not removed properly.";
}

TEST_F(JsonValueTest, BooleanCompareValue) {
  Value first, second;
  EXPECT_EQ(first, second)
    << "Invalid comparsion null <-> null";
  first = "5";
  EXPECT_FALSE(first == second)
    << "Invalid comparsion int <-> null";
  second = "5";
  EXPECT_EQ(first, second)
    << "Invalid comparsion int <-> int";
  first = true;
  EXPECT_FALSE(first == second)
    << "Invalid comparsion bool <-> int";
  second = true;
  EXPECT_EQ(first, second)
    << "Invalid comparsion bool <-> bool";
  first = 5;
  EXPECT_FALSE(first == second)
    << "Invalid comparsion string <-> bool";
  second = 5;
  EXPECT_EQ(first, second)
    << "Invalid comparsion string <-> bool";
  Value::Object object_1;
  first = Value(object_1);
  first.Add("Key 1", "Value 1");
  first.Add("Key 2", "Value 2");
  EXPECT_FALSE(first == second)
    << "Invalid comparsion string <-> object";
  second = Value(object_1);
  EXPECT_FALSE(first == second)
    << "Invalid comparsion object_1 <-> object_2";
  second.Add("Key 2", "Value 2");
  second.Add("Key 1", "Value 1");
  EXPECT_EQ(first, second)
    << "Invalid comparsion object_1 <-> object_1";
  second["Key 2"] = "Not Value 2";
  EXPECT_TRUE(first != second)
    << "Invalid comparsion object_1 <-> object_3";

  Value::Array array_1;
  first = Value(array_1);
  first.Append("Some sort of value");
  EXPECT_FALSE(first == second)
    << "Invalid comparsion array <-> object";
  second = Value(array_1);
  EXPECT_FALSE(first == second)
    << "Invalid comparsion array_1 <-> array_2";
  second.Append("Some sort of value");
  EXPECT_EQ(first, second)
    << "Invalid comparsion array_1 <-> array_1";
  first[(size_t) 0] = "Not some sort of value";
  EXPECT_FALSE(first == second)
    << "Invalid comparsion array_1 <-> array_3";
}
