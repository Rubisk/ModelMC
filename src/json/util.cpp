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
  Status s;
  char a;
  auto old_pos = stream.tellg();
  stream >> std::skipws >> a >> std::noskipws;
  stream.seekg(old_pos);
  if (!stream.good()) {
    return Status(kJsonError, "Parsing Error: Stream corrupted.");
  }

  if (a == '\"') {
    *output = kStringValue;
    return s;
  } else if (a == '{') {
    *output = kObjectValue;
    return s;
  } else if (a == '[') {
    *output = kVectorValue;
    return s;
  } else if (a == 't' || a == 'f') {
    *output = kBoolValue;
    return s;
  } else {
    for (char c : "0123456789") {
      if (c == a) {
        *output = kIntValue;
        return s;
      }
    }
    return Status(kJsonError, "Parsing Error: Value started with: '" + a);
  }
}

Status LoadName(std::istream &stream, std::string* output) {
  char a;
  stream >> std::skipws >> a >> std::noskipws;

  if (!stream.good()) {
    return Status(kJsonError, "Parsing Error: Stream corrupted.");
  } else if (a != '"') {
    return Status(kJsonError, "Parsing Error: String didn't start with '\"'.");
  }

  std::string name = "";
  while (stream >> a && a != '"') {
    name += a;
    if (name.size() > 1000) {
      return Status(kJsonError, "Parsing Error: Name longer then 1000 chars.");
    }
  }

  if (!stream.good()) {
    return Status(kJsonError, "Parsing Error: Stream corrupted.");
  }
  *output = name;
  return Status();
}

Status LoadValue(std::istream &stream, Value** valueptr) {
  ValueType type;
  Value* value;
  Status s = FindType(stream, &type);
  if (!s.IsOk()) {
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

  if (!s.IsOk()) {
    return s;
  }
  *valueptr = value;
  return s;
}

Status FindValueForPath(Value* root_tag, std::vector<void*> path, Value* &output_tag) {
  Status s;

  for (void* next_key : path) {
    switch (root_tag->GetValueType()) {
      case kVectorValue:
      {
        int* i_key = (int*) next_key;
        Value** result;
        s = root_tag->GetChild(*i_key, result);
        if (!s.IsOk()) {
          return s;
        }
        root_tag = *result;
        continue;
      }
      case kObjectValue:
      {
        std::string* s_key = (std::string*) next_key;
        Value** result;
        s = root_tag->GetChild(*s_key, result);
        if (!s.IsOk()) {
          return s;
        }
        root_tag = *result;
        continue;
      }
      default:
      {
        return Status(kJsonError, "Value-type is not-indexable.");
      }
    }
  }
  output_tag = root_tag;
  return s;
}

} // namespace json
