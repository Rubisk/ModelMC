#ifndef MODELMAKER_ELEMENT_H_
#define MODELMAKER_ELEMENT_H_

#include <vector>

#include "json/value.h"
#include "face.h"

// Forward declaration for friend.
class Model;

enum Axis : size_t {
  X,
  Y,
  Z,
};

// Represents one element of a model.
// Like a cube with 6 sides (faces).
struct Element {
public:
  // Start point of a cube according to the scheme [x, y, z]
  // Must be between -16 to 32
  int32_t from[3];

  // Stop point of a cube according to the scheme [x, y, z]
  // Must be between -16 to 32
  int32_t to[3];

  // Sets the center of the rotation according to the scheme [x, y, z]
  // Defaults to [8, 8, 8] in Minecraft.
  int32_t rotation_origin[3];

  // Specifies the direction of the rotation.
  // One of X, Y or Z.
  Axis rotation_axis;

  // Specifies the angle of the rotation.
  // Valid values are -45, -22.5, 0, 22.5 and 45.
  double_t rotation_angle;

  // True if faces scale across the whole block. Defaults to false.
  bool rotation_rescale;

  // Defines if shadows should be rendered. Defaults to true.
  bool shade;

  // All faces the element contains.
  Face faces[6];
protected:
  friend Model;

  void FromJson_(const json::Value &tree);

  json::Value ToJson_() const;
private:
  void Validate_();
};

#endif // MODELMAKER_ELEMENT_H_