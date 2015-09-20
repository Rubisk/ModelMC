#ifndef JSON_H
#define JSON_H

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

  Value &operator[](const std::string &key) const;

  Value &operator[](const char *key) const;

  Value &operator[](const size_t &key) const;

  operator int32_t&();

  operator std::string&();

  operator bool&();

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

#endif	// JSON_H

