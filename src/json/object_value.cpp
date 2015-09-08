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

Status ObjectValue::get(const std::string &key, Value** valueptr) {
  *valueptr = (*values_)[key];
  return kOk;
}

void ObjectValue::save(std::ostream* output) {
  *output << "{";
  
  ValueMap::iterator it = values_->begin();
  *output << "\"" << it->first << "\":";
  it->second->save(output);
  it++;
  
  while (it != values_->end()) {
    *output << ",\"" << it->first << "\":";
    it->second->save(output);
    it++;
  }
  *output << "}";
}

Status ObjectValue::loadFrom(std::istream &stream) {
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '{') {
    return kParseError;
  }
  
  while (true) {
    Status s = loadAndSaveValue_(stream);
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

Status ObjectValue::loadAndSaveValue_(std::istream& stream) {
  std::string name;
  Status s = loadName(stream, &name);
  if (s != kOk) {
    return s;
  }
  
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != ':') {
    return kParseError;
  }
  
  Value* value;
  s = loadValue(stream, &value);
  if (s != kOk) {
    return s;
  }
  
  s = this->get(name, &value); //TODO fix this
  if (s != kOk) {
    return s;
  }
  return kOk;
}

} // namespace json