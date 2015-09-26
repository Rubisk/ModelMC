#ifndef MODELMAKER_MODEL_H_
#define MODELMAKER_MODEL_H_

#include <vector>

#include "element.h"

// TODO: Forward declaration of texture,
// as it has to be implemented yet.
class Texture;

class Model {
public:
  void FromJson(const json::Value &tree);

  json::Value ToJson() const;

  std::vector<Element> elements;

  std::map<std::string, Texture> textures;

  ~Model();
private:
  void Validate_();
};

#endif // MODELMAKER_MODEL_H_
