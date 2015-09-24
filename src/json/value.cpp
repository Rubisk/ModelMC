#include <sstream>
#include <hash_set>
#include "json/value.h"

using namespace json;

json_exception::json_exception(const char *message)
  : std::runtime_error(message), message_(message) { };

const char *json_exception::what() const {
  return message_;
}

Value::Value() {
  type_ = kNullValue;
}

Value::Value(ValueType type) {
  switch (type) {
  case kIntValue:
    as_int = 0;
    break;
  case kDoubleValue:
    as_double = 0.0;
    break;
  case kBoolValue:
    as_bool = false;
    break;
  case kStringValue:
    as_string = new std::string();
    break;
  case kArrayValue:
    as_array = new Array();
    break;
  case kObjectValue:
    as_object = new Object();
    break;
  }
  type_ = type;
}

Value::Value(const int32_t &value) {
  Cleanup_();
  as_int = value;
  type_ = kIntValue;
}

Value::Value(const double_t &value) {
  Cleanup_();
  as_double = value;
  type_ = kDoubleValue;
}

Value::Value(const std::string &value) {
  Cleanup_();
  as_string = new std::string(value);
  type_ = kStringValue;
}

Value::Value(const char *value) {
  Cleanup_();
  as_string = new std::string(value);
  type_ = kStringValue;
}

Value::Value(const bool &value) {
  Cleanup_();
  as_bool = value;
  type_ = kBoolValue;
}

Value::Value(const Object &value) {
  Cleanup_();
  as_object = new Object(value);
  for (Object::iterator it = as_object->begin();
       it != as_object->end(); ++it) {
    if (it->second == NULL) {
      it->second = std::make_shared<Value>();
    }
  }
  type_ = kObjectValue;
}

Value::Value(const Array &value) {
  Cleanup_();
  as_array = new Array(value);
  for (std::shared_ptr<Value> &entry : *as_array) {
    if (entry.get() == NULL) {
      entry = std::make_shared<Value>();
    }
  }
  type_ = kArrayValue;
}

Value::Value(const Value &that) {
  if (this != &that) Copy_(that);
}

Value::Value(Value &&that) {
  if (this != &that) Move_(std::move(that));
}

Value &Value::operator=(const Value &that) {
  if (this != &that) Copy_(that);
  return *this;
}

Value &Value::operator=(Value &&that) {
  if (this != &that) Move_(std::move(that));
  return *this;
}

void Value::Add(const std::string &key, const Value &value) {
  AssertType_(kObjectValue);
  (*as_object)[key] = std::make_shared<Value>(value);
}

void Value::Append(const Value &value) {
  AssertType_(kArrayValue);
  as_array->push_back(std::make_shared<Value>(value));
}

void Value::Remove(const std::string &key) {
  AssertType_(kObjectValue);
  Object::iterator it = as_object->find(key);
  if (it != as_object->end()) {
    as_object->erase(it);
  }
}

void Value::Remove(const size_t &position) {
  AssertType_(kArrayValue);
  if (position < as_array->size()) {
    as_array->erase(as_array->begin() + position);
  }
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
  AssertType_(kObjectValue);
  std::shared_ptr<Value> ptr = (*as_object)[key];
  if (ptr.get() == NULL) {
    throw json_exception("Key not found.");
  }
  return static_cast<Value&>(*ptr);
}

Value &Value::operator[](const size_t &key) const {
  AssertType_(kArrayValue);
  if (key >= as_array->size()) {
    throw json_exception("Index out of bounds.");
  }
  std::shared_ptr<Value> ptr = (*as_array)[key];
  return static_cast<Value&>(*ptr);
}

Value::operator int32_t() const {
  AssertType_({kIntValue, kDoubleValue});
  if (type_ == kDoubleValue) {
    return (int32_t) as_double;
  } else {
    return as_int;
  }
}

Value::operator double_t() const {
  AssertType_({kIntValue, kDoubleValue});
  if (type_ == kDoubleValue) {
    return as_double;
  } else {
    return (double_t) as_int;
  }
}

Value::operator std::string() const {
  AssertType_(kStringValue);
  return *as_string;
}

Value::operator bool() const {
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

inline void Value::AssertType_(std::vector<ValueType> types) const {
  for (ValueType type : types) {
    if (type_ == type) {
      return; // Type is one of types.
    }
  }
  // Only gets executed if type_ not in types.
  std::stringstream ss;
  ss << "Value is of invalid type. Expected";
  for (ValueType type : types) {
    ss << " '" << GetTypeString_(type) << "',";
  }
  ss << " got '" << GetTypeString_(type_) << "' instead.";
  throw json_exception(ss.str().c_str());
}

bool Value::Equals_(const Value &that) const {
  if (that.type_ != type_) {
    // Hard-coded int/double comparison.
    if (that.type_ == kDoubleValue && type_ == kIntValue) {
      return (double_t) as_int == that.as_double;
    } else if (that.type_ == kIntValue && type_ == kDoubleValue) {
      return as_double == (double_t) that.as_int;
    }
    // If types aren't equal, there's no point in converting.
    return false;
  }

  // Other comparisons.
  switch (type_) {
  case kNullValue:
    return true;
    break;
  case kIntValue:
    return that.as_int == as_int;
    break;
  case kBoolValue:
    return that.as_bool == as_bool;
    break;
  case kStringValue:
    return *as_string == *that.as_string;
    break;
  case kDoubleValue:
    return as_double == that.as_double;
    break;
  case kArrayValue:
    if (as_array->size() != that.as_array->size()) {
      return false;
    } else {

      return std::equal(as_array->begin(),
                        as_array->end(),
                        that.as_array->begin(),
                        [](const Array::iterator::value_type &first,
                        const Array::iterator::value_type &second) {return *first == *second; }
      );
    }
    break;
  case kObjectValue:
    if (as_object->size() != that.as_object->size()) {
      return false;
    } else {
      return std::equal(as_object->begin(),
                        as_object->end(),
                        that.as_object->begin(),
                        [](const Object::iterator::value_type &first,
                        const Object::iterator::value_type &second) {return *first.second == *second.second; });
    }
  }
  throw json_exception("CODE ERROR: Invalid type.");
}

void Value::Copy_(const Value &that) {
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
    for (Object::iterator it = as_object->begin();
         it != as_object->end(); ++it) {
      it->second = std::make_shared<Value>(*it->second);
    }
    break;
  case kArrayValue:
    as_array = new Array(*that.as_array);
    for (Array::iterator it = as_array->begin();
         it != as_array->end(); ++it) {
      (*it) = std::make_shared<Value>(**it);
    }
    break;
  case kIntValue:
    as_int = that.as_int;
    break;
  case kDoubleValue:
    as_double = that.as_double;
    break;
  case kBoolValue:
    as_bool = that.as_bool;
  }
  type_ = that.type_;
}

void Value::Move_(Value &&that) {
  Cleanup_();
  switch (that.type_) {
  case kStringValue:
    as_string = that.as_string;
    break;
  case kObjectValue:
    as_object = that.as_object;
    break;
  case kArrayValue:
    as_array = that.as_array;
    break;
  case kIntValue:
    as_int = that.as_int;
    break;
  case kDoubleValue:
    as_double = that.as_double;
    break;
  case kBoolValue:
    as_bool = that.as_bool;
  }
  type_ = that.type_;
  //Setting the type to nullvalue makes it "forget" to cleanup
  //and properly delete it's pointers on destruction.
  that.type_ = kNullValue;

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
  }
  type_ = kNullValue;
}
