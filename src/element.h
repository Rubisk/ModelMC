#ifndef MODEL_H
#define	MODEL_H

#include "json/json.h"

enum Axis {
  kX, kY, kZ,
};
const size_t kNumberOfAxi = 3;

enum {
  kDown,
  kUp,
  kNorth,
  kSouth,
  kWest,
  kEast,
};
const size_t kNumberOfFaces = 6;

enum {
  kX1, kY1, kX2, kY2,
};
const size_t kNumberOfUVCoords = 4;

//Represents one of the six faces an element contains.

struct Face {
  //Defines the area of the textures for faces 1-6 according to the scheme
  //[x1, y1, x2, y2].
  //If unset, defaults to values equal to xyz pos of the element.
  //Must be between 0 to 16
  int32_t uv[kNumberOfUVCoords];

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
};

class Element {
public:
  //Start point of a cube according to the scheme [x, y, z]
  //Must be between -16 to 32
  int32_t from[kNumberOfAxi];

  //Stop point of a cube according to the scheme [x, y, z]
  //Must be between -16 to 32
  int32_t to[kNumberOfAxi];

  //Sets the center of the rotation according to the scheme [x, y, z]
  //Defaults to [8, 8, 8] in Minecraft.
  int32_t rotation_origin[kNumberOfAxi];

  //Specifies the direction of the rotation.
  //One of X, Y or Z.
  Axis rotation_axis;

  //Specifies the angle of the rotation.
  //Valid values are -45, -22.5, 0, 22.5 and 45.
  int32_t rotation_angle;

  //True if faces scale across the whole block. Defaults to false.
  bool rotation_rescale;

  //Defines if shadows should be rendered. Defaults to true.
  bool shade;

  //All faces the element contains.
  Face faces[kNumberOfFaces];

  //Loads an element from a json Object.
  //Does not create a new element, instead overrides target.
  Status LoadElement(json::Value* root_tag);

  //Saves an element to json.
  //Overrides whatever is set in target.
  Status SaveElement(Element &element);

private:
  Status LoadFace_(json::Value* root_tag, Face &face);
};

#endif	// MODEL_H

