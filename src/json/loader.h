#ifndef MODELMAKER_JSON_LOADER_H_
#define	MODELMAKER_JSON_LOADER_H_

#include <iostream>

#include "json/value.h"

namespace json {

class Loader {
public:
  Loader(const std::string &path);

  Loader(const char *path);

  Loader(std::shared_ptr<std::istream> stream);

  Value Load();

private:
  Value LoadArrayValue_();

  Value LoadObjectValue_();

  Value LoadIntValue_();

  Value LoadStringValue_();

  Value LoadBoolValue_();

  std::string LoadString_();

  std::shared_ptr<std::istream> stream_;
};

} //namespace json

#endif	// MODELMAKER_JSON_LOADER_H_
