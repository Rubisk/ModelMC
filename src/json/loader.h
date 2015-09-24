#ifndef MODELMAKER_JSON_LOADER_H_
#define	MODELMAKER_JSON_LOADER_H_

#include <iostream>

#include "json/value.h"

namespace json {

class Loader {
public:
  using InputStream = std::shared_ptr<std::istream>;

  Loader(const std::string &path);

  Loader(const char *path);

  Loader(InputStream stream);

  Value Load();

private:
  Value LoadArrayValue_();

  Value LoadObjectValue_();

  Value LoadNumericValue_();

  Value LoadStringValue_();

  Value LoadBoolValue_();

  std::string LoadString_();

  InputStream stream_;

  // Loads an int32_t of the stream.
  // Should never be called directly, call LoadNumericValue_() instead, 
  // to check for possible double values.
  int32_t LoadInt_();
};

} //namespace json

#endif	// MODELMAKER_JSON_LOADER_H_
