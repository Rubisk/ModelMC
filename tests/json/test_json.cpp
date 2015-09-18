#include <fstream>
#include <gtest/gtest.h>

#include "json/json.h"

using namespace json;

class JsonTest : public testing::Test {
protected:
  //Only used to test Value's default behavior.
  class TestValue : public json::Value {

    json::ValueType GetValueType() {
      return json::kBoolValue;
    }

    void SaveToStream(std::ostream* output) { }

    Status LoadFromStream(std::istream &stream) {
      return kGood;
    }
  };

  virtual void SetUp() {
    test_value_ = new TestValue();
  }

  virtual void TearDown() {
    delete test_value_;
  }

  Value* test_value_;
};

TEST_F(JsonTest, DefaultBoolValue) {
  bool output;
  Status s = test_value_->GetBoolValue(&output);
  EXPECT_FALSE(s.IsOk());
}

TEST_F(JsonTest, DefaultStringValue) {
  std::string output;
  Status s = test_value_->GetStringValue(&output);
  EXPECT_FALSE(s.IsOk());
}

TEST_F(JsonTest, DefaultIntValue) {
  int output;
  Status s = test_value_->GetIntValue(&output);
  EXPECT_FALSE(s.IsOk());
}

TEST_F(JsonTest, GetChild) {
  Value** output;
  Status s = test_value_->GetChild(1, output);
  ASSERT_FALSE(s.IsOk());
  s = test_value_->GetChild("some_key", output);
  ASSERT_FALSE(s.IsOk());
}

TEST_F(JsonTest, LoadFromAndSaveToFile) {
  Value* value;
  Status s = LoadFromFile("./tests/testfiles/test_json.json", value);
  ASSERT_TRUE(s.IsOk());

  SaveToFile("./tests/testfiles/test_output.json", value);

  delete value;

  std::ifstream original, copy;

  original.open("./tests/testfiles/test_json");
  copy.open("./tests/testfiles/test_output.json");

  ASSERT_TRUE(std::equal(std::istreambuf_iterator<char>(original),
    std::istreambuf_iterator<char>(),
    std::istreambuf_iterator<char>(copy)));

  original.close();
  copy.close();

  ASSERT_EQ(remove("./tests/testfiles/test_output.json"), 0);
}

