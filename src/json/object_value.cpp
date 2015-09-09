#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/object_value.h"
#include "src/json/util.h"

namespace json {

ObjectValue::ObjectValue() {
  values_ = new ValueMap();
}

ObjectValue::ObjectValue(ValueMap* values) {
  values_ = values;
}

Status ObjectValue::GetChild(const std::string &key, Value** &valueptr) {
  valueptr = &(*values_)[key];
  return kOk;
}

void ObjectValue::SaveValue(std::ostream* output) {
  *output << "{";

  ValueMap::iterator it = values_->begin();
  *output << "\"" << it->first << "\":";
  it->second->SaveValue(output);
  it++;

  while (it != values_->end()) {
    *output << ",\"" << it->first << "\":";
    it->second->SaveValue(output);
    it++;
  }
  *output << "}";
}

Status ObjectValue::LoadValue(std::istream &stream) {
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '{') {
    return kParseError;
  }

  while (true) {
    Status s = LoadAndSaveValue_(stream);
    if (s != kOk) {
      return s;
    }
    stream >> std::skipws >> next_char >> std::noskipws;
    if (!stream.good()) {
      return kUnkwownError;
    }
    switch (next_char) {
      case (','):
        continue;
      case ('}'):
        return kOk;
      default:
        return kParseError;
    }
  }
}

ObjectValue::~ObjectValue() {
  for (ValueMap::iterator it = values_->begin(); it != values_->end(); it++) {
    delete it->second;
  }
  delete values_;
}

Status ObjectValue::LoadAndSaveValue_(std::istream& stream) {
  std::string name;
  Status s = LoadName(stream, &name);
  if (s != kOk) {
    return s;
  }

  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != ':') {
    return kParseError;
  }

  Value* value;
  s = LoadValue(stream, &value);
  if (s != kOk) {
    return s;
  }

  Value** to_get;
  s = this->GetChild(name, to_get); //TODO fix this
  if (s != kOk) {
    return s;
  }
  *to_get = value;
  return kOk;
}

} // namespace json