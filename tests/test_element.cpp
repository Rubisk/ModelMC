#include <gtest\gtest.h>

#include "model.h"
#include "json/value.h"
#include "json/loader.h"

using namespace json;

// Extends from element, 
// exposes all it's protected functions, allowing
// tests to access them.
class TestElement : Element {
  friend class ElementTest;
  FRIEND_TEST(ElementTest, LoadCompleteElement);
  FRIEND_TEST(ElementTest, LoadEmptyElement);
  FRIEND_TEST(ElementTest, ValidateElement);
};

class ElementTest : public testing::Test {
public:
  void SetUp() {
    Loader loader = Loader("./tests/testfiles/test_element.json");
    ASSERT_NO_THROW(element_root = loader.Load());
  }

  Value element_root;
};

TEST_F(ElementTest, LoadCompleteElement) {
  TestElement element;
  element.FromJson_(element_root);
  EXPECT_EQ(element.from[1], 3);
  EXPECT_EQ(element.to[2], 16);
  EXPECT_EQ(element.shade, false);
  EXPECT_EQ(element.rotation_origin[1], 9);
  EXPECT_EQ(element.rotation_axis, Z);
  EXPECT_EQ(element.rotation_angle, -22.5);
  EXPECT_EQ(element.rotation_rescale, true);
  EXPECT_EQ(element.faces[Face::Down].uv[3], 16);
  EXPECT_EQ(element.faces[Face::Down].texture, "#inside");
  EXPECT_EQ(element.faces[Face::Down].cull, true);
  EXPECT_EQ(element.faces[Face::Down].rotation, 3);
  EXPECT_EQ(element.faces[Face::Down].tint_index, 1);
}

TEST_F(ElementTest, LoadEmptyElement) {
  TestElement element;
  element.FromJson_(Value::Null);
  EXPECT_EQ(element.from[2], 0);
  EXPECT_EQ(element.to[2], 0);
  EXPECT_EQ(element.shade, true);
  EXPECT_EQ(element.rotation_origin[2], 8);
  EXPECT_EQ(element.rotation_axis, X);
  EXPECT_EQ(element.rotation_angle, 0);
  EXPECT_EQ(element.rotation_rescale, false);
  EXPECT_EQ(element.faces[Face::Down].uv[0], 0);
  EXPECT_EQ(element.faces[Face::Down].uv[1], 0);
  EXPECT_EQ(element.faces[Face::Down].uv[2], 16);
  EXPECT_EQ(element.faces[Face::Down].uv[3], 16);
  EXPECT_EQ(element.faces[Face::Down].texture, "");
  EXPECT_EQ(element.faces[Face::Down].cull, true);
  EXPECT_EQ(element.faces[Face::Down].rotation, 0);
  EXPECT_EQ(element.faces[Face::Down].tint_index, 0);
}

TEST_F(ElementTest, ValidateElement) {
  element_root["from"][2] = 118;  // Should end up at 32.
  element_root["to"][(size_t) 0] = -50;  // Should end up at -16.
  element_root["rotation"]["angle"] = -23;  // Should end up at 0.
  element_root["faces"]["north"]["uv"][1] = -18; // Should end up at 0.
  element_root["faces"]["south"]["uv"][2] = 32300; // Should end up at 16.
  element_root["faces"]["north"].Add("rotation", 4); // Should end up at 3.
  element_root["faces"]["down"]["tintindex"] = -5; // Should end up at 0.

  TestElement element;
  element.FromJson_(element_root);
  EXPECT_EQ(element.from[2], 32);
  EXPECT_EQ(element.to[0], -16);
  EXPECT_EQ(element.rotation_angle, 0);
  EXPECT_EQ(element.faces[Face::North].uv[1], 0);
  EXPECT_EQ(element.faces[Face::South].uv[2], 16);
  EXPECT_EQ(element.faces[Face::North].rotation, 3);
  EXPECT_EQ(element.faces[Face::West].tint_index, 0);
}