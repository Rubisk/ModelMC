#include <streambuf>
#include <iostream>
#include <sstream>

#include "json/json.h"
#include "json/util.h"
#include "json/object_value.h"
#include "json/vector_value.h"
#include "json/simple_values.h"

namespace json {

Status FindType(std::istream &stream, ValueType* output) {
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

Status LoadName(std::istream &stream, std::string* output) {
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

Status LoadValue(std::istream &stream, Value** valueptr) {
  ValueType type;
  Value* value;
  Status s = FindType(stream, &type);
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
      value = new BoolValue;
  }
  s = value->LoadFromStream(stream);

  if (s != kOk) {
    return s;
  }
  *valueptr = value;
  return s;
}

} // namespace json
