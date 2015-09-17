#include <gtest/gtest.h>

#include "json/simple_values.h"
#include "json/vector_value.h"

using namespace json;

TEST(VectorValueTest, GetChild) {
  Value** valueptr;
  Value* value = new VectorValue();
  EXPECT_EQ(value->GetValueType(), kVectorValue);
  Status s = value->GetChild(5, valueptr);
  ASSERT_TRUE(s.IsOk());
  ASSERT_TRUE(*valueptr == NULL);

  *valueptr = new IntValue(10);

  Value** new_value_pointer;
  s = value->GetChild(5, new_value_pointer);
  ASSERT_TRUE(s.IsOk());
  int32_t output;
  s = (*new_value_pointer)->GetIntValue(&output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, 10);
  delete value;
}

TEST(VectorValueTest, LoadFromStream) {
  std::stringstream ss;
  ss.str("[5,8]");
  Value* value = new VectorValue();
  Status s = value->LoadFromStream(ss);
  ASSERT_TRUE(s.IsOk());

  std::stringstream os;
  ss >> os.rdbuf();
  EXPECT_EQ(os.str(), "");

  Value** output;

  int int_value;
  s = value->GetChild(0, output);
  ASSERT_TRUE(s.IsOk());
  s = (*output)->GetIntValue(&int_value);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(int_value, 5);
  s = value->GetChild(1, output);
  ASSERT_TRUE(s.IsOk());
  s = (*output)->GetIntValue(&int_value);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(int_value, 8);
  delete value;
}

TEST(VectorValueTest, SaveToStream) {
  const std::string test_str = "[5,\"string\"]";
  std::stringstream input_stream;
  input_stream.str(test_str);
  Value* value = new VectorValue();
  Status s = value->LoadFromStream(input_stream);
  ASSERT_TRUE(s.IsOk());

  std::stringstream output_stream;
  value->SaveToStream(&output_stream);
  EXPECT_EQ(output_stream.str(), test_str);
  delete value;
}

