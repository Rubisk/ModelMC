#include <gtest/gtest.h>

#include "json/simple_values.h"

using namespace json;

namespace {

const std::string evil_string = "<>?:\"{} | _ + ";
const std::string int_to_load = "53-110" + evil_string;
const std::string bool_to_load = "truefalse" + evil_string;
const std::string string_to_load = "\"simple_string\"\"'between quotations!'\"" + evil_string;

}

class ValuesTest : public testing::Test {
protected:
  virtual void SetUp() {
    int_ = new IntValue(1);
    string_ = new StringValue("standard_value");
    bool_ = new BoolValue(false);
    string_stream_.clear();
  }

  virtual void TearDown() {
    delete int_;
    delete string_;
    delete bool_;
  }

  void AssertRemainder_(std::string remainder) {
    std::stringstream os;
    string_stream_ >> os.rdbuf();
    EXPECT_EQ(os.str(), remainder);
  }

  std::stringstream string_stream_;
  Value* int_;
  Value* bool_;
  Value* string_;
  Status s_;
  bool bool_output;
  std::string string_output;
  int int_output;
};

TEST_F(ValuesTest, GetValueType) {

  EXPECT_EQ(bool_->GetValueType(), kBoolValue);
  EXPECT_EQ(int_->GetValueType(), kIntValue);
  EXPECT_EQ(string_->GetValueType(), kStringValue);
}

TEST_F(ValuesTest, GetValue) {
  s_ = bool_->GetBoolValue(&bool_output);
  ASSERT_TRUE(s_.IsOk());
  s_ = int_->GetIntValue(&int_output);
  ASSERT_TRUE(s_.IsOk());
  s_ = string_->GetStringValue(&string_output);
  ASSERT_TRUE(s_.IsOk());
  EXPECT_EQ(bool_output, false);
  EXPECT_EQ(int_output, 1);
  EXPECT_EQ(string_output, "standard_value");
}

TEST_F(ValuesTest, SetValue) {
  *bool_ = true;
  *int_ = 100;
  *string_ = "new_string";
  s_ = bool_->GetBoolValue(&bool_output);
  ASSERT_TRUE(s_.IsOk());
  s_ = int_->GetIntValue(&int_output);
  ASSERT_TRUE(s_.IsOk());
  s_ = string_->GetStringValue(&string_output);
  ASSERT_TRUE(s_.IsOk());
  EXPECT_EQ(bool_output, true);
  EXPECT_EQ(int_output, 100);
  EXPECT_EQ(string_output, "new_string");
}


TEST_F(ValuesTest, LoadFromStreamBool) {
  string_stream_.str(bool_to_load);

  s_ = bool_->LoadFromStream(string_stream_);
  ASSERT_TRUE(s_.IsOk());
  s_ = bool_->GetBoolValue(&bool_output);
  EXPECT_TRUE(s_.IsOk());
  EXPECT_EQ(bool_output, true);

  s_ = bool_->LoadFromStream(string_stream_);
  ASSERT_TRUE(s_.IsOk());
  s_ = bool_->GetBoolValue(&bool_output);
  EXPECT_TRUE(s_.IsOk());
  EXPECT_EQ(bool_output, false);
  AssertRemainder_(evil_string);
}

TEST_F(ValuesTest, LoadFromStreamInt) {
  string_stream_.str(int_to_load);

  s_ = int_->LoadFromStream(string_stream_);
  ASSERT_TRUE(s_.IsOk());
  s_ = int_->GetIntValue(&int_output);
  EXPECT_TRUE(s_.IsOk());
  EXPECT_EQ(int_output, 53);

  s_ = int_->LoadFromStream(string_stream_);
  ASSERT_TRUE(s_.IsOk());
  s_ = int_->GetIntValue(&int_output);
  EXPECT_TRUE(s_.IsOk());
  EXPECT_EQ(int_output, -110);
  AssertRemainder_(evil_string);
}

TEST_F(ValuesTest, LoadFromStreamString) {
  string_stream_.str(string_to_load);

  s_ = string_->LoadFromStream(string_stream_);
  ASSERT_TRUE(s_.IsOk());
  s_ = string_->GetStringValue(&string_output);
  EXPECT_TRUE(s_.IsOk());
  EXPECT_EQ(string_output, "simple_string");

  s_ = string_->LoadFromStream(string_stream_);
  ASSERT_TRUE(s_.IsOk());
  s_ = string_->GetStringValue(&string_output);
  EXPECT_TRUE(s_.IsOk());
  EXPECT_EQ(string_output, "'between quotations!'");
  AssertRemainder_(evil_string);
}

TEST_F(ValuesTest, SaveBoolToStream) {
  *bool_ = false;
  bool_->SaveToStream(&string_stream_);
  *bool_ = true;
  bool_->SaveToStream(&string_stream_);
  EXPECT_EQ(string_stream_.str(), "falsetrue");
}


TEST_F(ValuesTest, SaveStringToStream) {
  string_->SaveToStream(&string_stream_);
  EXPECT_EQ(string_stream_.str(), "\"standard_value\"");
  *string_ = "'between quotations!'";
  string_->SaveToStream(&string_stream_);
  EXPECT_EQ(string_stream_.str(), "\"standard_value\"\"'between quotations!'\"");
}

TEST_F(ValuesTest, SaveIntToStream) {
  *int_ = 53;
  int_->SaveToStream(&string_stream_);
  EXPECT_EQ(string_stream_.str(), "53");
  *int_ = -1;
  int_->SaveToStream(&string_stream_);
  EXPECT_EQ(string_stream_.str(), "53-1");
}

