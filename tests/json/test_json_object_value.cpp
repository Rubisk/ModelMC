#include <gtest/gtest.h>

#include "json/object_value.h"
#include "json/simple_values.h"

using namespace json;

TEST(ObjectValueTest, GetKey) {
  const std::string key = "some_key";
  Value** valueptr;
  Value* value = new ObjectValue();
  EXPECT_EQ(value->GetValueType(), kObjectValue);
  Status s = value->GetChild(key, valueptr);
  ASSERT_TRUE(s.IsOk());
  Value* null_ptr = NULL;
  EXPECT_EQ(*valueptr, null_ptr);

  *valueptr = new IntValue(5);
  Value** new_valueptr;
  ASSERT_TRUE(value->GetChild(key, new_valueptr).IsOk());
  int32_t output;
  ASSERT_TRUE((*new_valueptr)->GetIntValue(&output).IsOk());
  EXPECT_EQ(output, 5);
  delete value;
}

TEST(ObjectValueTest, LoadFromStream) {
  std::stringstream ss;
  ss.str("{\"int_value\":5,\"string_value\":\"string\"}{|)");
  Value* value = new ObjectValue();
  Status s = value->LoadFromStream(ss);
  ASSERT_TRUE(s.IsOk());

  std::stringstream os;
  ss >> os.rdbuf();
  EXPECT_EQ(os.str(), "{|)");

  Value** output;
  int int_value;

  s = value->GetChild("int_value", output);
  ASSERT_TRUE(s.IsOk());
  s = (*output)->GetIntValue(&int_value);
  ASSERT_TRUE(s.IsOk());
  std::string string_value;
  s = value->GetChild("string_value", output);
  ASSERT_TRUE(s.IsOk());
  s = (*output)->GetStringValue(&string_value);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(int_value, 5);
  EXPECT_EQ(string_value, "string");
  delete value;
}

TEST(ObjectValueTest, SaveToStream) {
  const std::string test_str = "{\"int_value\":5,\"string_value\":\"string\"}";
  std::stringstream input_stream;
  input_stream.str(test_str);
  Value* value = new ObjectValue();
  Status s = value->LoadFromStream(input_stream);
  ASSERT_TRUE(s.IsOk());

  std::stringstream output_stream;
  value->SaveToStream(&output_stream);
  EXPECT_EQ(output_stream.str(), test_str);
  delete value;
}

