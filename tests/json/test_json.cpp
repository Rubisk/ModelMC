#include <fstream>
#include <gtest/gtest.h>

#include "json/json.h"

using namespace json;

class JsonTest : public testing::Test {
protected:
  void SetUp() {
    value_ = Value();
  }

  Value value_;
};

TEST_F(JsonTest, DefaultValue) {
  EXPECT_EQ(value_.GetType(), kNullValue);
}

TEST_F(JsonTest, ValueConstructValue) {
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

TEST_F(JsonTest, IntValue) {
  EXPECT_NO_THROW(value_ = 5)
    << "Couldn't assign an integer.";
  EXPECT_EQ(value_.GetType(), kIntValue)
    << "Type didn't change properly.";
  EXPECT_EQ((int32_t) value_, 5)
    << "Value didn't get assigned properly.";
}

TEST_F(JsonTest, StringValue) {
  EXPECT_NO_THROW(value_ = "first_string")
    << "Couldn't assign an string.";
  EXPECT_EQ(value_.GetType(), kStringValue)
    << "Value type isn't string.";
  EXPECT_EQ((std::string) value_, "first_string")
    << "Value didn't get assigned properly.";
}

TEST_F(JsonTest, BoolValue) {
  EXPECT_NO_THROW(value_ = true)
    << "Couldn't assign a bool.";
  EXPECT_EQ(value_.GetType(), kBoolValue)
    << "Value type isn't bool.";
  EXPECT_EQ((bool) value_, true)
    << "Value didn't get assigned properly.";
}

TEST_F(JsonTest, ObjectValue) {
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

  Value &string_value = value_["preset_key"];
  EXPECT_EQ(string_value.GetType(), kStringValue)
    << "Couldn't edit existing child properly.";
  EXPECT_EQ((std::string) string_value, "some_string")
    << "Edited value didn't have correct value.";
}

TEST_F(JsonTest, ArrayValue) {
  Value::Array empty_array(5);
  ASSERT_NO_THROW(value_ = empty_array)
    << "Couldn't assign an array to a value.";
  EXPECT_THROW(value_[8], json_exception)
    << "Asking for non-existant value didn't throw.";

  Value &value = value_[3];
  EXPECT_EQ(value.GetType(), kNullValue)
    << "Couldn't get existing child.";
  value = "some_string";
  ASSERT_EQ(value.GetType(), kStringValue)
    << "Value didn't write properly";

  Value &string_value = value_[3];
  EXPECT_EQ(string_value.GetType(), kStringValue)
    << "Couldn't edit existing child properly.";
  EXPECT_EQ((std::string) string_value, "some_string")
    << "Edited value didn't have correct value.";
}


TEST_F(JsonTest, CopyAssignValue) {
  value_ = Value(5);
  EXPECT_EQ((int32_t) value_, 5)
    << "Failed to copy int value.";
  value_ = Value("some_string");
  EXPECT_EQ((std::string) value_, "some_string")
    << "Failed to copy string value.";
  value_ = Value(true);
  EXPECT_EQ((bool) value_, true)
    << "Failed to copy bool value.";

  Value::Object object;
  object["key"] = std::make_shared<Value>(5);
  value_ = Value(object);
  EXPECT_EQ((int32_t) value_["key"], 5)
    << "Failed to copy object value.";

  Value::Array array_(3);
  array_[1] = std::make_shared<Value>(1);
  value_ = Value(array_);
  EXPECT_EQ((int32_t) value_[1], 1)
    << "Failed to copy array value.";

}

TEST_F(JsonTest, CopyConstructValue) {
  value_ = -1;
  std::unique_ptr<Value> value(new Value(value_));
  EXPECT_EQ((int32_t) *value, -1)
    << "Copy constructor is broken.";
}