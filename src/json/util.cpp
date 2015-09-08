#include <streambuf>
#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/util.h"
#include "src/json/object_value.h"
#include "src/json/vector_value.h"
#include "src/json/simple_values.h"

namespace json {

Status findType(std::istream &stream, ValueType* output) {
  char a;
  auto old_pos = stream.tellg();
  stream >> std::skipws >> a >> std::noskipws;
  stream.seekg(old_pos);
  if (!stream.good()) {
    return kUnkwownError;
  }

  if (a == '\"') {
    *output = kStringValue;
    return kOk;
  } else if (a == '{') {
    *output = kObjectValue;
    return kOk;
  } else if (a == '[') {
    *output = kVectorValue;
    return kOk;
  } else if (a == 't' || a == 'f') {
    *output = kBoolValue;
    return kOk;
  } else {
    for (char c : "0123456789") {
      if (c == a) {
        *output = kIntValue;
        return kOk;
      }
    }
    return kParseError;
  }
}

Status loadName(std::istream &stream, std::string* output) {
  char a;
  stream >> std::skipws >> a >> std::noskipws;

  if (!stream.good()) {
    return kUnkwownError;
  } else if (a != '"') {
    return kParseError;
  }

  std::string name = "";
  while (stream >> a && a != '"') {
    name += a;
    if (name.size() > 1000) {
      return kParseError;
    }
  }

  if (!stream.good()) {
    return kUnkwownError;
  }
  *output = name;
  return kOk;
}

Status loadValue(std::istream &stream, Value** valueptr) {
  ValueType type;
  Value* value;
  Status s = findType(stream, &type);
  if (s != kOk) {
    return s;
  }

  switch (type) {
    case (kObjectValue):
      value = new ObjectValue;
      break;
    case (kVectorValue):
      value = new VectorValue;
      break;
    case (kIntValue):
      value = new IntValue;
      break;
    case (kStringValue):
      value = new StringValue;
      break;
    case (kBoolValue):
      value = new StringValue;
  }
  s = value->loadFrom(stream);

  if (s != kOk) {
    return s;
  }
  *valueptr = value;
  return s;
}

} // namespace json
