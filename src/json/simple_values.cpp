#include <cstdlib>
#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/simple_values.h"
#include "util.h"

namespace json {

IntValue::IntValue(const int32_t &value) {
  value_ = value;
}

Status IntValue::operator=(const int32_t &value) {
  value_ = value;
  return kOk;
}

Status IntValue::as_int(int32_t* output) {
  *output = value_;
  return kOk;
}

void IntValue::save(std::ostream* stream) {
  *stream << value_;
}

Status IntValue::loadFrom(std::istream &stream) {
  stream >> std::skipws >> value_ >> std::noskipws;
  if (!stream.good()) {
    return kUnkwownError;
  }
  return kOk;
}

StringValue::StringValue(const std::string &value) {
  value_ = value;
}

Status StringValue::operator=(const std::string &value) {
  value_ = value;
  return kOk;
}

void StringValue::save(std::ostream* stream) {
  *stream << "\"" << value_ << "\"";
}

Status StringValue::as_string(std::string* output) {
  *output = value_;
  return kOk;
}

Status StringValue::loadFrom(std::istream &stream) {
  std::string value;
  Status s = loadName(stream, &value);
  if (s != kOk) {
    return s;
  }
  value_ = value;
  return kOk;
}

BoolValue::BoolValue(const bool &value) {
  value_ = value;
}

Status BoolValue::operator=(const bool &value) {
  value_ = value;
  return kOk;
}

Status BoolValue::as_bool(bool* output) {
  *output = value_;
  return kOk;
}

void BoolValue::save(std::ostream* output) {
  *output << value_ ? "true" : "false";
}

Status BoolValue::loadFrom(std::istream &stream) {
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
