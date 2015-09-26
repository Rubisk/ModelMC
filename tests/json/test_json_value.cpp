#include <fstream>
#include <gtest/gtest.h>
#include <utility>

#include "json/value.h"

using namespace json;
using namespace std;

class JsonValueTest : public testing::Test {
protected:
  void SetUp() {
    null_value = Value::Null;
    int_value = 5;
    double_value = 5.25;
    bool_value = false;
    string_value = "my_string";

    Value::Array new_array;
    new_array.push_back(make_shared<Value>(null_value));
    new_array.push_back(make_shared<Value>(int_value));
    array_value = new_array;
    array_value.Append(double_value);
    array_value.Append(bool_value);
    array_value.Append(string_value);

    Value::Object new_object;
    new_object["Preset null"] = make_shared<Value>(null_value);
    new_object["Preset int"] = make_shared<Value>(int_value);

    object_value = new_object;
    object_value.Add("Preset double", double_value);
    object_value.Add("Preset bool", bool_value);
    object_value.Add("Preset string", string_value);
  }

  Value null_value;
  Value int_value;
  Value double_value;
  Value bool_value;
  Value string_value;
  Value array_value;
  Value object_value;

  int32_t int_output;
  double_t double_output;
  string string_output;
  bool bool_output;
};

TEST_F(JsonValueTest, IntValue) {
  EXPECT_EQ(int_value, 5);
  int_output = int_value;
  EXPECT_EQ(int_value, int_output);
  EXPECT_EQ(int_output, (int32_t) int_value);
}

TEST_F(JsonValueTest, DoubleValue) {
  EXPECT_EQ(double_value, 5.25);
  double_output = double_value;
  EXPECT_EQ(double_value, double_output);
  EXPECT_EQ(double_output, (double_t) double_value);
}

TEST_F(JsonValueTest, StringValue) {
  EXPECT_EQ(string_value, "my_string");
  string_output = string_value;
  EXPECT_EQ(string_value, string_output);
  EXPECT_EQ(string_output, (string) string_value);
}

TEST_F(JsonValueTest, BoolValue) {
  EXPECT_EQ(bool_value, false);
  bool_output = bool_value;
  EXPECT_EQ(bool_value, bool_output);
  EXPECT_EQ(bool_output, (bool) bool_value);
}

TEST_F(JsonValueTest, ArrayValue) {
  EXPECT_EQ(array_value[4], "my_string");
  array_value.Remove(1);
  EXPECT_THROW(array_value[4], json_exception);
  array_value.Append(8);
  EXPECT_EQ(array_value[4], 8);
}

TEST_F(JsonValueTest, ObjectValue) {
  EXPECT_EQ(object_value["Preset int"], 5);
  object_value.Remove("Preset int");
  EXPECT_THROW(object_value["Preset int"], json_exception);
  object_value.Add("New int", 8);
  EXPECT_EQ(object_value["New int"], 8);
}

TEST_F(JsonValueTest, DoubleToInt) {
  double_value = static_cast<double_t>(int_value);
  EXPECT_EQ(double_value, 5);
  EXPECT_FALSE(double_value == 5.25);
}

TEST_F(JsonValueTest, IntToDouble) {
  int_value = static_cast<int32_t>(double_value);
  EXPECT_EQ(int_value, 5.0);
  EXPECT_FALSE(int_value == 5.25);
}

TEST_F(JsonValueTest, ValueTypeConstruct) {
  null_value = Value::Null;
  ASSERT_EQ(null_value, Value::Null);
  int_value = Value::IntVal;
  ASSERT_EQ(int_value, 0);
  double_value = Value::DoubleVal;
  ASSERT_EQ(double_value, 0.0);
  bool_value = Value::BoolVal;
  ASSERT_EQ(bool_value, false);
  string_value = Value::StringVal;
  ASSERT_EQ(string_value, "");
  array_value = Value::ArrayVal;
  ASSERT_NO_THROW(array_value.Append(null_value));
  object_value = Value::ObjectVal;
  ASSERT_NO_THROW(object_value.Add("Preset string", string_value));
}

TEST_F(JsonValueTest, CopyValues) {
  Value second_int = int_value;
  EXPECT_EQ(int_value, second_int);
  int_value = false;
  EXPECT_EQ(second_int, 5);

  // Explicit test on std::string, since 
  // that's the only raw value stored as a pointer.
  Value second_string = string_value;
  EXPECT_EQ(second_string, "my_string");
  string_value = 0;
  // Make sure the string itself gets copied to.
  EXPECT_EQ(second_string, "my_string");

  Value second_array = array_value;
  EXPECT_EQ(second_array[4], "my_string");
  EXPECT_EQ(array_value[4], "my_string");
  array_value = 0;
  // Make sure the string gets copied to.
  EXPECT_EQ(second_array[4], "my_string"); 

  Value second_object = object_value;
  EXPECT_EQ(second_object["Preset string"], "my_string");
  EXPECT_EQ(object_value["Preset string"], "my_string");
  object_value = 0;
  // Make sure the string gets copied to.
  EXPECT_EQ(second_object["Preset string"], "my_string");
}

TEST_F(JsonValueTest, MoveValues) {
  Value second_int = std::move(int_value);
  ASSERT_EQ(int_value, Value::Null);
  EXPECT_EQ(second_int, 5);

  // Explicit test on std::string, since 
  // that's the only raw value stored as a pointer.
  Value second_string = std::move(string_value);
  ASSERT_EQ(string_value, Value::Null);
  EXPECT_EQ(second_string, "my_string");

  Value second_array = std::move(array_value);
  ASSERT_EQ(array_value, Value::Null);
  EXPECT_EQ(second_array[4], "my_string");

  Value second_object = std::move(object_value);
  EXPECT_EQ(object_value, Value::Null);
  EXPECT_EQ(second_object["Preset string"], "my_string");
}
