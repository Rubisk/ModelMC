#include <gtest/gtest.h>
#include <fstream>

#include "json/loader.h"

using namespace json;

class JsonLoaderTest : public testing::Test {
protected:
  void TearDown() {
    ss->clear();
  }

  std::shared_ptr<std::stringstream> ss =
    std::make_shared<std::stringstream>();
  Loader loader = Loader(ss);
};

TEST_F(JsonLoaderTest, LoadPositiveInt) {
  Value output;
  ss->str("63890");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((int32_t) output, 63890);
}

TEST_F(JsonLoaderTest, LoadNegativeInt) {
  Value output;
  ss->str("-5555");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((int32_t) output, -5555);
}

TEST_F(JsonLoaderTest, LoadString) {
  Value output;
  ss->str("\"some_string\"");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((std::string) output, "some_string");
}

TEST_F(JsonLoaderTest, LoadTrueBool) {
  Value output;
  ss->str("true");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((bool) output, true);
}

TEST_F(JsonLoaderTest, LoadFalseBool) {
  Value output;
  ss->str("false");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((bool) output, false);
}

TEST_F(JsonLoaderTest, LoadArray) {
  Value output;
  ss->str("[1,\"some_string\",3  , 444]");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((int32_t) output[3], 444);
}

TEST_F(JsonLoaderTest, LoadObject) {
  Value output;
  ss->str("{\"some_key\":1,\"some_other_key\":true}");
  ASSERT_NO_THROW(output = loader.Load());
  EXPECT_EQ((bool) output["some_other_key"], true);
}

TEST_F(JsonLoaderTest, LoadFromFile) {
  Value output;
  Loader file_loader("./tests/testfiles/test_json.json");
  ASSERT_NO_THROW(output = file_loader.Load());
  EXPECT_EQ((std::string) output["textures"]["particle"], "blocks/cauldron_side");
}

TEST_F(JsonLoaderTest, LoadFromFileWithNewlines) {
  Value output;
  Loader file_loader("./tests/testfiles/test_json.json");
  ASSERT_NO_THROW(output = file_loader.Load());
}
