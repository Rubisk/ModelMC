#ifndef MODELMAKER_JSON_VALUE_H_
#define MODELMAKER_JSON_VALUE_H_

#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <memory>
#include <map>
#include <vector>

#include "status.h"

namespace json {

class json_exception : public std::runtime_error {
public:
  json_exception(const char *message);

  const char *what() const;

  const char *message_;
};

enum ValueType {
  kNullValue,
  kIntValue,
  kStringValue,
  kBoolValue,
  kObjectValue,
  kArrayValue,
};

class Value {
public:
  using Object = std::map<std::string, std::shared_ptr<Value>>;

  using Array = std::vector<std::shared_ptr<Value>>;

  ValueType GetType() const;

  Value();

  Value(const int32_t &value);

  Value(char *value);

  Value(const std::string &value);

  Value(const bool &value);

  Value(const Object &value);

  Value(const Array &value);

  Value(const Value &that);

  Value(Value &&that);

  Value &operator=(const int32_t &value);

  Value &operator=(char *value);

  Value &operator=(const std::string &value);

  Value &operator=(const bool &value);

  Value &operator=(const Object &value);

  Value &operator=(const Array &value);

  Value &operator=(const Value &that);

  Value &operator=(Value &&that);

  // Add value to an ObjectValue. Throws if value is not an ObjectValue.
  // Note that if there's a value at key already, it will be overridden.
  void Add(const std::string &key, const Value &value);

  void Add(const char *key, const Value &value);

  // Appends an ArrayValue with the value. Throws if value is not an ArrayValue.
  void Append(const Value &value);

  // Removes a value from an ObjectValue. Throws if value is not an ObjectValue.
  // Note that if there's no value at the key, no action will be taken.
  void Remove(const std::string &key);

  void Remove(const char *key);

  // Removes a value from an ArrayValue. Throws if the value is not an ArrayValue.
  // Note that if the size_t is bigger then the size of the array, no action will be taken.
  void Remove(const size_t &position);

  Value &operator[](const std::string &key) const;

  Value &operator[](const char *key) const;

  Value &operator[](const size_t &position) const;

  operator int32_t&();

  operator std::string&();

  operator bool&();

  bool operator==(const Value& value) const;

  bool operator!=(const Value& value) const;

  ~Value();

private:
  void Cleanup_();

  inline void AssertType_(ValueType type) const;

  inline static std::string GetTypeString_(ValueType type);

  ValueType type_;

  union {
    int as_int;
    bool as_bool;
    std::string *as_string;
    Object *as_object;
    Array *as_array;
  };
};

} // namespace json

#endif	// MODELMAKER_JSON_VALUE_H_

