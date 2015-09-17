#include <gtest/gtest.h>

#include "json/json.h"
#include "json/util.h"
#include "json/object_value.h"
#include "json/vector_value.h"
#include "json/simple_values.h"

using namespace json;

TEST(UtilTest, FindType) {
  ValueType output;
  std::stringstream ss;
  Status s;

  ss.str("1");
  s = FindType(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, kIntValue);
  ss.str("-1");
  s = FindType(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, kIntValue);
  ss.str("\"");
  s = FindType(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, kStringValue);
  ss.str("t");
  s = FindType(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, kBoolValue);
  ss.str("{");
  s = FindType(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, kObjectValue);
  ss.str("[");
  s = FindType(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, kVectorValue);
  ss.str("}");
  s = FindType(ss, &output);
  EXPECT_FALSE(s.IsOk());
}

TEST(UtilTest, TestLoadName) {
  std::string output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = LoadName(ss, &output);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(output, "my_name");
}

TEST(UtilTest, LoadValue) {
  Value* output;
  std::stringstream ss;
  Status s;
  ss.str("\"my_name\"");
  s = LoadValue(ss, output);
  ASSERT_TRUE(s.IsOk());
  std::string value_of;
  s = output->GetStringValue(&value_of);
  ASSERT_TRUE(s.IsOk());
  EXPECT_EQ(value_of, "my_name");
  delete output;
}
