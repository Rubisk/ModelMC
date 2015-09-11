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
  value_ = value;
  return kOk;
}

Status IntValue::GetIntValue(int32_t* output) {
  *output = value_;
  return kOk;
}

void IntValue::SaveToStream(std::ostream* stream) {
  *stream << value_;
}

Status IntValue::LoadFromStream(std::istream &stream) {
  stream >> std::skipws >> value_ >> std::noskipws;
  if (!stream.good()) {
    return kUnkwownError;
  }
  return kOk;
}

ValueType StringValue::GetValueType() {
  return kStringValue;
}

StringValue::StringValue(const std::string &value) {
  value_ = value;
}

Status StringValue::operator=(const std::string &value) {
  value_ = value;
  return kOk;
}

void StringValue::SaveToStream(std::ostream* stream) {
  *stream << "\"" << value_ << "\"";
}

Status StringValue::GetStringValue(std::string* output) {
  *output = value_;
  return kOk;
}

Status StringValue::LoadFromStream(std::istream &stream) {
  std::string value;
  Status s = LoadName(stream, &value);
  if (s != kOk) {
    return s;
  }
  value_ = value;
  return kOk;
}

ValueType BoolValue::GetValueType() {
  return kBoolValue;
}

BoolValue::BoolValue(const bool &value) {
  value_ = value;
}

Status BoolValue::operator=(const bool &value) {
  value_ = value;
  return kOk;
}

Status BoolValue::GetBoolValue(bool* output) {
  *output = value_;
  return kOk;
}

void BoolValue::SaveToStream(std::ostream* output) {
  *output << (value_ ? "true" : "false");
}

Status BoolValue::LoadFromStream(std::istream &stream) {
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (!stream.good()) {
    return kUnkwownError;
  }
  if (next_char == 'f') {
    for (char c : "alse") {
      stream >> next_char;
      if (!stream.good()) {
        return kUnkwownError;
      }
      if (next_char != c) {
        return kParseError;
      }
      if (c == 'e') {
        value_ = false;
        return kOk;
      }
    }
  } else if (next_char == 't') {
    for (char c : "rue") {
      stream >> next_char;
      if (!stream.good()) {
        return kUnkwownError;
      }
      if (next_char != c) {
        return kParseError;
      }
      if (c == 'e') {
        value_ = true;
        return kOk;
      };
    }
  }
  return kParseError;
}

} // namespace json
