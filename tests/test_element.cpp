#include <gtest\gtest.h>

#include "element.h"
#include "json/json.h"
#include "json/object_value.h"

using namespace json;

class ElementTest : public testing::Test {
protected:
  virtual void SetUp() {
    Value* base_tag;
    s_ = LoadFromFile("./tests/testfiles/test_element.json", base_tag);
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

TEST_F(ElementTest, LoadEmptyElement) {
  Element element;
  Value* value = new ObjectValue();
  s_ = element.LoadElement(value);
  EXPECT_EQ(element.from[2], 0);
  EXPECT_EQ(element.to[2], 0);
  EXPECT_EQ(element.shade, true);
  EXPECT_EQ(element.rotation_origin[2], 8);
  EXPECT_EQ(element.rotation_axis, kX);
  EXPECT_EQ(element.rotation_angle, 0);
  EXPECT_EQ(element.rotation_rescale, false);
  EXPECT_EQ(element.faces[kDown].uv[0], 0);
  EXPECT_EQ(element.faces[kDown].uv[1], 0);
  EXPECT_EQ(element.faces[kDown].uv[2], 16);
  EXPECT_EQ(element.faces[kDown].uv[3], 16);
  EXPECT_EQ(element.faces[kDown].texture, "");
  EXPECT_EQ(element.faces[kDown].cull, true);
  EXPECT_EQ(element.faces[kDown].rotation, 0);
  EXPECT_EQ(element.faces[kDown].tint_index, 0);
  delete value;
}
