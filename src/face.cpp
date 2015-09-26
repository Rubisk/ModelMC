#include "helper_macros.h"
#include "face.h"
#include "json/value.h"

using namespace json;

void Face::FromJson_(const json::Value &tree) {
  for (UVCoord i : {X1, X2, Y1, Y2}) {
    int32_t default_uv = (i >= 2) ? 16 : 0;
    ASSIGN_OR_DEFAULT(tree["uv"][i], uv[i], default_uv);
  }
  ASSIGN_OR_DEFAULT(tree["texture"], texture, "");
  ASSIGN_OR_DEFAULT(tree["cull"], cull, true);
  ASSIGN_OR_DEFAULT(tree["rotation"], rotation, 0);
  ASSIGN_OR_DEFAULT(tree["tintindex"], tint_index, 0);
}

void Face::Validate_() {
  for (UVCoord x : {X1, X2, Y1, Y2}) {
    SET_BETWEEN(0, 16, uv[x]);
  }
  SET_BETWEEN(0, 3, rotation);
  SET_BETWEEN(0, INT32_MAX, tint_index);
}