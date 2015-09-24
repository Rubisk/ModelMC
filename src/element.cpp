#include <stdexcept>
#include <sstream>
#include <vector>

#include "json/value.h"
#include "element.h"

using namespace json;

namespace {

// json::Value objects (can) throw on evaluating member access
// operators. Because of that, something like value[key] can't be
// passed to a function to try catch the exception, as it will
// be evaluated before being passed. So we use a Macro instead.
//TODO write all errors to some logger.
#define ASSIGN_OR_DEFAULT(to_assign, assignee, default_) \
  try {                                                  \
    assignee = to_assign;                                \
  } catch (std::runtime_error) {                         \
    assignee = default_;                                 \
  }

#define SET_BETWEEN(min, max, value) \
  if (value < min) value = min;      \
  if (value > max) value = max;

inline Axis StringToAxis(const std::string &string) {
  char char_ = *string.c_str();
  switch (char_) {
  case 'X':
  case 'x':
    return kX;
  case 'Y':
  case 'y':
    return kY;
  case 'Z':
  case 'z':
    return kZ;
  default:
    std::stringstream ss;
    ss << "Unkwown axis char: '" << char_ << "'.";
    throw std::runtime_error(ss.str());
  }
}

inline char AxisToString(Axis axis) {
  switch (axis) {
  case kX:
    return 'x';
  case kY:
    return 'y';
  case kZ:
    return 'z';
  }
}

inline FaceDirection StringToFaceDir(const std::string &face_name) {
  if (face_name == "down") {
    return kDown;
  } else if (face_name == "up") {
    return kUp;
  } else if (face_name == "north") {
    return kNorth;
  } else if (face_name == "south") {
    return kSouth;
  } else if (face_name == "west") {
    return kEast;
  } else if (face_name == "east") {
    return kWest;
  } else throw std::runtime_error("Invalid face name: \"" + face_name + "\".");
}

inline std::string FaceDirToString(FaceDirection face) {
  switch (face) {
  case kDown:
    return "down";
  case kUp:
    return "up";
  case kNorth:
    return "north";
  case kSouth:
    return "south";
  case kWest:
    return "west";
  case kEast:
    return "east";
  }
  throw json_exception("Invalid FaceDirection value.");
}

} // anonymous namespace

Element::Element() {
  *this = null;
}

Element::Element(const Value &tree) {
  *this = tree;
}

Element &Element::operator=(const json::Value &tree) {
  for (Axis i : AllAxes) {
    ASSIGN_OR_DEFAULT(tree["from"][i], from[i], 0);
    ASSIGN_OR_DEFAULT(tree["to"][i], to[i], 0);
    ASSIGN_OR_DEFAULT(tree["rotation"]["origin"][i], rotation_origin[i], 8);
  }

  ASSIGN_OR_DEFAULT(tree["shade"], shade, true);
  ASSIGN_OR_DEFAULT(StringToAxis(tree["rotation"]["axis"]),
                    rotation_axis, kX);
  ASSIGN_OR_DEFAULT(tree["rotation"]["angle"], rotation_angle, 0);
  ASSIGN_OR_DEFAULT(tree["rotation"]["rescale"], rotation_rescale, false);

  for (FaceDirection direction : AllFaces) {
    Value face;
    ASSIGN_OR_DEFAULT(tree["faces"][FaceDirToString(direction)], face, face);
    LoadFace_(face, direction);
  }
  Validate_();
  return *this;
}

void Element::LoadFace_(const json::Value &tree, const FaceDirection &direction) {
  Face &face = faces[direction];
  for (UVCoord i : AllUVCoords) {
    ASSIGN_OR_DEFAULT(tree["uv"][i], face.uv[i], (i >= 2) ? 16 : 0);
  }
  ASSIGN_OR_DEFAULT(tree["texture"], face.texture, "");
  ASSIGN_OR_DEFAULT(tree["cull"], face.cull, true);
  ASSIGN_OR_DEFAULT(tree["rotation"], face.rotation, 0);
  ASSIGN_OR_DEFAULT(tree["tintindex"], face.tint_index, 0);
}

void Element::Validate_() {
  // TODO write all made changes to some sort of logger.
  for (Axis i : AllAxes) {
    SET_BETWEEN(-16, 32, from[i]);
    SET_BETWEEN(-16, 32, to[i]);
    // no min-max for rotation_origin (found on wiki);
  }

  // Enforce rotation_angle is one of:
  // -45, -22.5, 0, 22.5, 45.
  if (fmod(rotation_angle, 22.5) != 0 
      || rotation_angle < -45 
      || rotation_angle > 45) {
    rotation_angle = 0;
  }

  for (FaceDirection f : AllFaces) {
    Face &face = faces[f];
    for (UVCoord x : AllUVCoords) {
      SET_BETWEEN(0, 16, face.uv[x]);
    }
    SET_BETWEEN(0, 3, face.rotation);
    SET_BETWEEN(0, INT32_MAX, face.tint_index);
  }
}