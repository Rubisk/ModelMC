#include <cstdlib>
#include <iostream>
#include <sstream>

#include "json/json.h"
#include "json/simple_values.h"
#include "util.h"

namespace json {

ValueType IntValue::GetValueType() {
  return kIntValue;
}

IntValue::IntValue(const int32_t &value) {
  value_ = value;
}

Status IntValue::operator=(const int32_t &value) {
  Status s;
  value_ = value;
  return s;
}

Status IntValue::GetIntValue(int32_t* output) {
  Status s;
  *output = value_;
  return s;
}

void IntValue::SaveToStream(std::ostream* stream) {
  *stream << value_;
}

Status IntValue::LoadFromStream(std::istream &stream) {
  Status s;
  stream >> std::skipws >> value_ >> std::noskipws;
  if (!stream.good()) {
    return Status(kJsonError, "Parsing Error: Stream corrupted.");
  }
  return s;
}

ValueType StringValue::GetValueType() {
  return kStringValue;
}

StringValue::StringValue(const std::string &value) {
  value_ = value;
}

Status StringValue::operator=(const std::string &value) {
  Status s;
  value_ = value;
  return s;
}

Status StringValue::operator=(const char* value) {
  Status s;
  value_ = value;
  return s;
}


void StringValue::SaveToStream(std::ostream* stream) {
  *stream << "\"" << value_ << "\"";
}

Status StringValue::GetStringValue(std::string* output) {
  Status s;
  *output = value_;
  return s;
}

Status StringValue::LoadFromStream(std::istream &stream) {
  std::string value;
  Status s = LoadName(stream, &value);
  if (!s.IsOk()) {
    return s;
  }
  value_ = value;
  return s;
}

ValueType BoolValue::GetValueType() {
  return kBoolValue;
}

BoolValue::BoolValue(const bool &value) {
  value_ = value;
}

Status BoolValue::operator=(const bool &value) {
  Status s;
  value_ = value;
  return s;
}

Status BoolValue::GetBoolValue(bool* output) {
  Status s;
  *output = value_;
  return s;
}

void BoolValue::SaveToStream(std::ostream* output) {
  *output << (value_ ? "true" : "false");
}

Status BoolValue::LoadFromStream(std::istream &stream) {
  Status s;
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (!stream.good()) {
    return Status(kJsonError, "Parsing Error: Stream corrupted.");
  }
  if (next_char == 'f') {
    for (char c : "alse") {
      stream >> next_char;
      if (!stream.good()) {
        return Status(kJsonError, "Parsing Error: Stream corrupted.");
      }
      if (next_char != c) {
        return Status(kJsonError,
                      "Unexpected char while loading bool: " + next_char);
      }
      if (c == 'e') {
        value_ = false;
        return s;
      }
    }
  }
  else if (next_char == 't') {
    for (char c : "rue") {
      stream >> next_char;
      if (!stream.good()) {
        return Status(kJsonError, "Parsing Error: Stream corrupted.");
      }
      if (next_char != c) {
        return Status(kJsonError,
                      "Unexpected char while loading bool: " + next_char);
      }
      if (c == 'e') {
        value_ = true;
        return s;
      };
    }
  }
  return Status(kJsonError,
                "Unexpected char while loading bool: " + next_char);
}

} // namespace json
