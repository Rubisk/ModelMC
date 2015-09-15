#include "element_test.h"
#include "src/element.h"
#include "src/json/json.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(ElementTest);

ElementTest::ElementTest() { }

ElementTest::~ElementTest() { }

void ElementTest::setUp() {
  Value* base_tag;
  s_ = LoadFromFile("./tests/testfiles/element.json", base_tag);
  CPPUNIT_ASSERT(s_.IsOk());
  root_tag_ = base_tag;
}

void ElementTest::tearDown() {
  if (root_tag_ != NULL) delete root_tag_;
}

void ElementTest::TestLoadFullElement() {
  Element element;
  s_ = element.LoadElement(root_tag_);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(element.from[1] == 3);
  CPPUNIT_ASSERT(element.to[2] == 16);
  CPPUNIT_ASSERT(element.shade == false);
  CPPUNIT_ASSERT(element.rotation_origin[1] == 9);
  CPPUNIT_ASSERT(element.rotation_axis == kZ);
  CPPUNIT_ASSERT(element.rotation_angle == 45);
  CPPUNIT_ASSERT(element.rotation_rescale == true);
  CPPUNIT_ASSERT(element.faces[kDown].uv[3] == 16);
  CPPUNIT_ASSERT(element.faces[kDown].texture == "#inside");
  CPPUNIT_ASSERT(element.faces[kDown].cull == true);
  CPPUNIT_ASSERT(element.faces[kDown].rotation == 5);
  CPPUNIT_ASSERT(element.faces[kDown].tint_index == 1);
}
