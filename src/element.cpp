#include <stdexcept>
#include <csignal>

#include "json/json.h"
#include "json/object_value.h"
#include "element.h"
#include "json/util.h"
#include "json/extract.h"

using namespace json;

namespace {

const StringVector face_strings
= {"down", "up", "north", "south", "west", "east"};

} // anonymous namespace

Status StringToAxis(const char* first_char, Axis &output) {
  Status s;
  switch (*first_char) {
  case 'X':
  case 'x':
    output = kX;
    break;
  case 'Y':
  case 'y':
    output = kY;
    break;
  case 'Z':
  case 'z':
    output = kZ;
    break;
  default:
    return Status(kIOException, "Invalid axis.");
  }
  return s;
}

void Element::InitializeToDefaults_() {
  for (int i = 0; i < kNumberOfAxi; ++i) {
    from[i] = 0;
    to[i] = 0;
    rotation_origin[i] = 8;
  }
  shade = true;
  rotation_axis = kX;
  rotation_angle = 0;
  rotation_rescale = false;
  for (int i = 0; i < kNumberOfFaces; ++i) {
    faces[i].uv[0] = 0;
    faces[i].uv[1] = 0;
    faces[i].uv[2] = 16;
    faces[i].uv[3] = 16;
    faces[i].texture = "";
    faces[i].cull = true;
    faces[i].rotation = 0;
    faces[i].tint_index = 0;
  }
}

Status Element::LoadFace_(Value* root_tag, Face &face) {
  Status s;
  std::string cullface_string;
  s = LoadIntArray(root_tag, "uv", kNumberOfUVCoords, face.uv);
  s = LoadStringValue(root_tag, "texture", face.texture);
  s = LoadStringValue(root_tag, "cullface", cullface_string);
  face.cull = (s.IsOk() && cullface_string != "");
  s = LoadIntValue(root_tag, "rotation", face.rotation);
  s = LoadIntValue(root_tag, "tintindex", face.tint_index);
  return s;
}

Status Element::LoadElement(Value* element_tag) {
  InitializeToDefaults_();

  //TODO setup a proper logging system.
  Status s;
  s = LoadIntArray(element_tag, "from", kNumberOfAxi, from);
  s = LoadIntArray(element_tag, "to", kNumberOfAxi, to);
  s = LoadBoolValue(element_tag, "shade", shade);

  StringVector vector = {"rotation", "origin"};
  s = LoadIntArray(element_tag, vector, kNumberOfAxi, rotation_origin);
  vector[1] = "angle";
  s = LoadIntValue(element_tag, vector, rotation_angle);
  std::string axis;
  vector[1] = "axis";
  s = LoadStringValue(element_tag, vector, axis);
  if (s.IsOk()) {
    s = StringToAxis(axis.c_str(), rotation_axis);
  }
  vector[1] = "rescale";
  s = LoadBoolValue(element_tag, vector, rotation_rescale);
  vector[0] = "faces";
  for (int i = 0; i < kNumberOfFaces; ++i) {
    vector[1] = face_strings[i];
    Value* output_tag;
    s = FindValueForPath(element_tag, vector, output_tag);
    if (!s.IsOk()) {
      continue;
    }
    LoadFace_(output_tag, faces[i]);
  }
  return Status();
}
