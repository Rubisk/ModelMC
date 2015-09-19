#include <sstream>

#include "json/json.h"
#include "json/util.h"

using namespace json;

json_exception::json_exception(const char *message)
  : std::runtime_error(message), message_(message) { };

const char *json_exception::what() const {
  return message_; 
}

ValueType Value::GetType() const {
  return type_;
}

Value::Value() {
  type_ = kNullValue;
}

Value::Value(const int32_t &value) {
  *this = value;
}

Value::Value(char* value) {
  *this = value;
}

Value::Value(const std::string &value) {
  *this = value;
}

Value::Value(const bool &value) {
  *this = value;
}

Value::Value(const Object &value) {
  *this = value;
}

Value::Value(const Array &value) {
  *this = value;
}

Value::Value(const Value &that) {
  *this = that;
}

Value &Value::operator=(const int32_t &value) {
  Cleanup_();
  as_int = value;
  type_ = kIntValue;
  return *this;
}

Value &Value::operator=(char* value) {
  Cleanup_();
  as_string = new std::string(value);
  type_ = kStringValue;
  return *this;
}

Value &Value::operator=(const std::string &value) {
  Cleanup_();
  as_string = new std::string(value);
  type_ = kStringValue;
  return *this;
}

Value &Value::operator=(const bool &value) {
  Cleanup_();
  as_bool = value;
  type_ = kBoolValue;
  return *this;
}

Value &Value::operator=(const Object &value) {
  Cleanup_();
  as_object = new Object(value);
  for (Object::iterator it = as_object->begin();
       it != as_object->end(); ++it) {
    if (it->second == NULL) {
      it->second = std::make_shared<Value>();
    }
  }
  type_ = kObjectValue;
  return *this;
}

Value &Value::operator=(const Array &value) {
  Cleanup_();
  as_array = new Array(value);
  for (std::shared_ptr<Value> &entry : *as_array) {
    if (entry.get() == NULL) {
      entry = std::make_shared<Value>();
    }
  }
  type_ = kArrayValue;
  return *this;
}

Value &Value::operator[](const std::string &key) const {
  AssertType_(kObjectValue);
  std::shared_ptr<Value> ptr = (*as_object)[key];
  if (ptr.get() == NULL) {
    throw json_exception("Key not found.");
  }
  return static_cast<Value&>(*ptr);
}

Value &Value::operator[](const char *key) const {
  std::string value_of(key);
  return operator[](value_of);
}

Value &Value::operator[](const size_t &key) const {
  AssertType_(kArrayValue);
  if (key > as_array->size()) {
    throw json_exception("Index out of bounds.");
  }
  std::shared_ptr<Value> ptr = (*as_array)[key];
  return static_cast<Value&>(*ptr);
}

Value &Value::operator=(const Value &that) {
  Cleanup_();

  // We have to make sure to copy the actual values of the 
  // pointees in the union, otherwise they will be invalid
  // once the "that" object will be deleted.
  switch (that.type_) {
  case kStringValue:
    as_string = new std::string(*that.as_string);
    break;
  case kObjectValue:
    as_object = new Object(*that.as_object);
    break;
  case kArrayValue:
    as_array = new Array(*that.as_array);
    break;
  case kIntValue:
    as_int = that.as_int;
    break;
  case kBoolValue:
    as_bool = that.as_bool;
  }
  type_ = that.type_;
  return *this;
}

Value::operator int32_t&() {
  AssertType_(kIntValue);
  return as_int;
}

Value::operator std::string&() {
  AssertType_(kStringValue);
  return *as_string;
}

Value::operator bool&() {
  AssertType_(kBoolValue);
  return as_bool;
}

Value::~Value() {
  Cleanup_();
}

inline void Value::AssertType_(ValueType type) const {
  if (type_ != type) {
    std::stringstream ss;
    ss << "Value is of invalid type. Expected '" << GetTypeString_(type)
      << "', got '" << GetTypeString_(type_) << "' instead.";
    throw json_exception(ss.str().c_str());
  }
}

inline std::string Value::GetTypeString_(ValueType type) {
  switch (type) {
  case kNullValue:
    return "null";
  case kIntValue:
    return "int";
  case kBoolValue:
    return "bool";
  case kObjectValue:
    return "object";
  case kArrayValue:
    return "array";
  case kStringValue:
    return "string";
  }
  return "unkwown type";
}

void Value::Cleanup_() {
  switch (type_) {
  case kObjectValue:
    delete as_object;
    break;
  case kArrayValue:
    delete as_array;
    break;
  case kStringValue:
    delete as_string;
    break;
  default:
    break;
  }
  type_ = kNullValue;
}
