#include <stdexcept>
#include <csignal>

#include "json/json.h"
#include "element.h"
#include "json/util.h"
#include "json/extract.h"

using namespace json;

namespace { // anonymous namespace

const StringVector face_strings
        = {"down", "up", "north", "south", "west", "east"};

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

Status LoadFace(Value* root_tag, Face &face) {
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

}

Status LoadElement(Value* element_tag, Element &element) {
  //TODO setup a proper logging system.
  Status s;
  s = LoadIntArray(element_tag, "from", kNumberOfAxi, element.from);
  s = LoadIntArray(element_tag, "to", kNumberOfAxi, element.to);
  s = LoadBoolValue(element_tag, "shade", element.shade);

  StringVector vector = {"rotation", "origin"};
  s = LoadIntArray(element_tag, vector, kNumberOfAxi, element.rotation_origin);
  vector[1] = "angle";
  s = LoadIntValue(element_tag, vector, element.rotation_angle);
  std::string axis;
  vector[1] = "axis";
  s = LoadStringValue(element_tag, vector, axis);
  s = StringToAxis(axis.c_str(), element.rotation_axis);
  vector[1] = "rescale";
  s = LoadBoolValue(element_tag, vector, element.rotation_rescale);

  vector[0] = "faces";
  for (int i = 0; i < kNumberOfFaces; ++i) {
    vector[1] = face_strings[i];
    Value* output_tag;
    s = FindValueForPath(element_tag, vector, output_tag);
    if (!s.IsOk()) {
      continue;
    }
    LoadFace(output_tag, element.faces[i]);
  }
  return Status();
}
