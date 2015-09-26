#include <stdexcept>
#include <sstream>
#include <vector>

#include "json/value.h"
#include "json/iterator.h"
#include "element.h"
#include "helper_macros.h"

using namespace json;

namespace {

inline Face::Direction StringToFaceDir(const std::string &face_name) {
  if (face_name == "down") {
    return Face::Down;
  } else if (face_name == "up") {
    return Face::Up;
  } else if (face_name == "north") {
    return Face::North;
  } else if (face_name == "south") {
    return Face::South;
  } else if (face_name == "west") {
    return Face::East;
  } else if (face_name == "east") {
    return Face::West;
  } else throw std::runtime_error("Invalid face name: \"" + face_name + "\".");
}

inline std::string FaceDirToString(Face::Direction face) {
  switch (face) {
  case Face::Down:
    return "down";
  case Face::Up:
    return "up";
  case Face::North:
    return "north";
  case Face::South:
    return "south";
  case Face::West:
    return "west";
  case Face::East:
    return "east";
  }
  throw json_exception("Invalid FaceDirection value.");
}

inline Axis StringToAxis(const std::string &string) {
  char char_ = *string.c_str();
  switch (char_) {
  case 'X':
  case 'x':
    return X;
  case 'Y':
  case 'y':
    return Y;
  case 'Z':
  case 'z':
    return Z;
  default:
    std::stringstream ss;
    ss << "Unkwown axis char: '" << char_ << "'.";
    throw std::runtime_error(ss.str());
  }
}

inline char AxisToString(Axis axis) {
  switch (axis) {
  case X:
    return 'x';
  case Y:
    return 'y';
  case Z:
    return 'z';
  }
}

} // anonymous namespace

void Element::FromJson_(const json::Value &tree) {
  for (Axis axis : {X, Y, Z}) {
    ASSIGN_OR_DEFAULT(tree["from"][axis], from[axis], 0);
    ASSIGN_OR_DEFAULT(tree["to"][axis], to[axis], 0);
    ASSIGN_OR_DEFAULT(tree["rotation"]["origin"][axis], rotation_origin[axis], 8);
  }

  ASSIGN_OR_DEFAULT(tree["shade"], shade, true);
  ASSIGN_OR_DEFAULT(StringToAxis(tree["rotation"]["axis"]),
                    rotation_axis, X);
  ASSIGN_OR_DEFAULT(tree["rotation"]["angle"], rotation_angle, 0);
  ASSIGN_OR_DEFAULT(tree["rotation"]["rescale"], rotation_rescale, false);

  try {
    // Buffer holding all 6 face values.
    // Note that if they're not found in the tree,
    // the face gets loaded from an empty value
    // - thus assigning default values.
    Value face_trees[6];
    Value::Iterator it = tree["faces"].GetIterator();

    while (it.Valid()) {
      Face::Direction dir = StringToFaceDir(it.GetKey());
      face_trees[dir] = it.Get();
    }
    for (size_t pos = 0; pos < 6; ++pos) {
      faces[pos].FromJson_(face_trees[pos]);
    }
  } catch (json_exception) {
    // TODO write logger for not finding face tag.
  }

  Validate_();
}

void Element::Validate_() {
  // TODO write all made changes to some sort of logger.
  for (Axis i : {X, Y, Z}) {
    SET_BETWEEN(-16, 32, from[i]);
    SET_BETWEEN(-16, 32, to[i]);
  }

  // Enforce rotation_angle is one of:
  // -45, -22.5, 0, 22.5, 45.
  if (fmod(rotation_angle, 22.5) != 0
      || rotation_angle < -45
      || rotation_angle > 45) {
    rotation_angle = 0;
  }

  for (Face face : faces) {
    face.Validate_();
  }
}