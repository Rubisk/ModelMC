#include <gtest\gtest.h>

#include "element.h"
#include "json/json.h"

using namespace json;

class ElementTest : public testing::Test {
protected:
  virtual void SetUp() {
    Value* base_tag;
    s_ = LoadFromFile("./tests/testfiles/element.json", base_tag);
    if (!s_.IsOk()) {
      root_tag_ = NULL;
      ASSERT_TRUE(false) << s_;
    }
    root_tag_ = base_tag;
  }


  virtual void TearDown() {
    if (root_tag_ != NULL) delete root_tag_;
  }

  Value* root_tag_;
  Status s_;
};

TEST_F(ElementTest, LoadCompleteElement) {
  Element element;
  s_ = element.LoadElement(root_tag_);
  ASSERT_TRUE(s_.IsOk());
  EXPECT_EQ(element.from[1], 3);
  EXPECT_EQ(element.to[2], 16);
  EXPECT_EQ(element.shade, false);
  EXPECT_EQ(element.rotation_origin[1], 9);
  EXPECT_EQ(element.rotation_axis, kZ);
  EXPECT_EQ(element.rotation_angle, 45);
  EXPECT_EQ(element.rotation_rescale, true);
  EXPECT_EQ(element.faces[kDown].uv[3], 16);
  EXPECT_EQ(element.faces[kDown].texture, "#inside");
  EXPECT_EQ(element.faces[kDown].cull, true);
  EXPECT_EQ(element.faces[kDown].rotation, 5);
  EXPECT_EQ(element.faces[kDown].tint_index, 1);
}
