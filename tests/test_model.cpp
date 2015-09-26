#include <gtest\gtest.h>

#include "model.h"
#include "json/value.h"
#include "json/loader.h"

using namespace json;
using Face = Model::Element::Face;

TEST(ElementTest, LoadCompleteElement) {
  Value root;
  Loader loader = Loader("./tests/testfiles/test_element.json");
  ASSERT_NO_THROW(root = loader.Load());

  Model::Element element(root);
  EXPECT_EQ(element.from[1], 3);
  EXPECT_EQ(element.to[2], 16);
  EXPECT_EQ(element.shade, false);
  EXPECT_EQ(element.rotation_origin[1], 9);
  EXPECT_EQ(element.rotation_axis, Model::Z);
  EXPECT_EQ(element.rotation_angle, -22.5);
  EXPECT_EQ(element.rotation_rescale, true);
  EXPECT_EQ(element.faces[Face::Down].uv[3], 16);
  EXPECT_EQ(element.faces[Face::Down].texture, "#inside");
  EXPECT_EQ(element.faces[Face::Down].cull, true);
  EXPECT_EQ(element.faces[Face::Down].rotation, 3);
  EXPECT_EQ(element.faces[Face::Down].tint_index, 1);
}

TEST(ElementTest, LoadEmptyElement) {
  Value empty_value;
  Element element = empty_value;
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
}

TEST(ElementTest, ValidateElement) {
  Value root;
  Loader loader = Loader("./tests/testfiles/test_element.json");
  ASSERT_NO_THROW(root = loader.Load());

  root["from"][2] = 118;  // Should end up at 32.
  root["to"][(size_t) 0] = -50;  // Should end up at -16.
  root["rotation"]["angle"] = -23;  // Should end up at 0.
  root["faces"]["north"]["uv"][1] = -18; // Should end up at 0.
  root["faces"]["south"]["uv"][2] = 32300; // Should end up at 16.
  root["faces"]["north"].Add("rotation", 4); // Should end up at 3.
  root["faces"]["down"]["tintindex"] = -5; // Should end up at 0.

  Element element(root);
  EXPECT_EQ(element.from[2], 32);
  EXPECT_EQ(element.to[0], -16);
  EXPECT_EQ(element.rotation_angle, 0);
  EXPECT_EQ(element.faces[kNorth].uv[1], 0);
  EXPECT_EQ(element.faces[kSouth].uv[2], 16);
  EXPECT_EQ(element.faces[kNorth].rotation, 3);
  EXPECT_EQ(element.faces[kWest].tint_index, 0);
}
