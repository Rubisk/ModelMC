#include <iostream>
#include <sstream>

#include "json/json.h"
#include "json/object_value.h"
#include "json/util.h"

namespace json {

ValueType ObjectValue::GetValueType() {
  return kObjectValue;
}

ObjectValue::ObjectValue() {
  values_ = new ValueMap();
}

ObjectValue::ObjectValue(ValueMap* values) {
  values_ = values;
}

Status ObjectValue::GetChild(const std::string &key, Value** &valueptr) {
  Status s;
  valueptr = &(*values_)[key];
  return s;
}

void ObjectValue::SaveToStream(std::ostream* output) {
  *output << "{";

  ValueMap::iterator it = values_->begin();
  *output << "\"" << it->first << "\":";
  it->second->SaveToStream(output);
  it++;

  while (it != values_->end()) {
    *output << ",\"" << it->first << "\":";
    it->second->SaveToStream(output);
    it++;
  }
  *output << "}";
}

Status ObjectValue::LoadFromStream(std::istream &stream) {
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '{') {
    return Status(kJsonError,
                  "Parsing Error: Expected '{', found '" + next_char);
  }

  while (true) {
    Status s = LoadAndSaveValue_(stream);
    if (!s.IsOk()) {
      return s;
    }
    stream >> std::skipws >> next_char >> std::noskipws;
    if (!stream.good()) {
      return Status(kJsonError, "Parsing Error: Stream corrupted.");
    }
    switch (next_char) {
    case (','):
      continue;
    case ('}'):
      return Status();
    default:
      return Status(kJsonError,
                    "Parsing Error: Expected '}' or ',', found '" + next_char);
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
  if (!s.IsOk()) {
    return s;
  }

  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != ':') {
    return Status(kJsonError,
                  "Parsing Error: Expected ':', found '" + next_char);
  }

  Value* value;
  s = LoadValue(stream, &value);
  if (!s.IsOk()) {
    return s;
  }

  Value** to_get;
  s = this->GetChild(name, to_get); //TODO fix this
  if (!s.IsOk()) {
    return s;
  }
  *to_get = value;
  return s;
}

} // namespace json