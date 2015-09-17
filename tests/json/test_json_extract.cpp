#include <gtest\gtest.h>

#include "json/extract.h"
#include "json/object_value.h"
#include "json/vector_value.h"
#include "json/simple_values.h"
#include "json/util.h"

using namespace json;

class ExtractTest : public testing::Test {
protected:
  virtual void SetUp() {
    s_ = LoadFromFile("./tests/testfiles/test_extract.json", root_tag_);
    if (!s_.IsOk()) {
      root_tag_ = NULL;
      ASSERT_TRUE(false) << s_;
    }
  }

  virtual void TearDown() {
    if (root_tag_ != NULL) {
      delete root_tag_;
    }
    path.clear();
    s_ = Status(kGood);
    output_ = NULL;
  }

  StringVector path;
  Value* root_tag_;
  Status s_;
  Value* output_;
};

TEST_F(ExtractTest, FindValueForPath) {
  path = StringVector {"first_key", "1", "third_key",
    "fourth_key", "5", "final_key"};
  s_ = FindValueForPath(root_tag_, path, output_);

  ASSERT_TRUE(s_.IsOk());
  std::string string_output;
  s_ = output_->GetStringValue(&string_output);

  ASSERT_TRUE(s_.IsOk());
  EXPECT_EQ(string_output, "Find me please!");
}

TEST_F(ExtractTest, FindValueForInvalidPath) {
  std::string cant_find = "Can't find me, hah!";
  path = StringVector {cant_find};
  s_ = FindValueForPath(root_tag_, path, output_);
  ASSERT_TRUE(!s_.IsOk());
  EXPECT_EQ(s_.GetError(), kIOException);
  EXPECT_EQ(*s_.GetErrorMessage(), "Invalid key: " + cant_find);
}

TEST_F(ExtractTest, LoadIntArray) {
  int32_t output_array[7];

  s_ = LoadIntArray(root_tag_, "int_array_key", 7, output_array);
  ASSERT_TRUE(s_.IsOk());
  EXPECT_EQ(output_array[6], 7);
}

TEST_F(ExtractTest, LoadStringValue) {
  std::string output_string;
  path = StringVector {"string_value_key", "0"};

  s_ = LoadStringValue(root_tag_, path, output_string);
  ASSERT_TRUE(s_.IsOk());
  EXPECT_EQ(output_string, "load_me");
}