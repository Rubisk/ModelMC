#ifndef MODELMAKER_FACE_H_
#define MODELMAKER_FACE_H_

#include "json/value.h"

// Forward declaration for friend.
struct Element;

struct Face {
public:
  enum Direction : size_t {
    Down,
    Up,
    North,
    South,
    West,
    East,
  };

  enum UVCoord : size_t {
    X1,
    Y1,
    X2,
    Y2,
  };

  //Defines the area of the textures for faces 1-6 according to the scheme
  //[x1, y1, x2, y2].
  //If unset, defaults to values equal to xyz pos of the element.
  //Must be between 0 to 16
  int32_t uv[4];

  //Specifies the faces textures in form of a texture variable starting with #
  std::string texture;

  //Specifies whether non-visible elements should be rendered for the faces.
  bool cull;

  //Rotates the texture in increments of 90 degrees.
  //Must be between 0 to 3
  int32_t rotation;

  //Determens if the texture should be tinted by Minecrafts renderer.
  //Tinting is a hardcoded color adjustment.
  int32_t tint_index;
protected:
  friend Element;

  void FromJson_(const json::Value &tree);

  json::Value ToJson_() const;
private:
  void Validate_();
};

#endif // MODELMAKER_FACE_H_