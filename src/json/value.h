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
  kDoubleValue,
  kStringValue,
  kBoolValue,
  kObjectValue,
  kArrayValue,
};

const static ValueType null = kNullValue;

class Value {
public:
  using Object = std::map<std::string, std::shared_ptr<Value>>;

  using Array = std::vector<std::shared_ptr<Value>>;

  Value();

  Value(ValueType type);

  Value(const int32_t &init);

  Value(const double_t &init);

  Value(const std::string &init);

  Value(const char *init);

  Value(const bool &init);

  Value(const Object &init);

  Value(const Array &init);

  Value(const Value &init);

  Value(Value &&that);

  Value &operator=(const Value &that);

  Value &operator=(Value &&that);

  // Add value to an ObjectValue. Throws if value is not an ObjectValue.
  // Note that if there's a value at key already, it will be overridden.
  void Add(const std::string &key, const Value &value);

  // Appends an ArrayValue with the value. Throws if value is not an ArrayValue.
  void Append(const Value &value);

  // Removes a value from an ObjectValue. Throws if value is not an ObjectValue.
  // Note that if there's no value at the key, no action will be taken.
  void Remove(const std::string &key);

  // Removes a value from an ArrayValue. Throws if the value is not an ArrayValue.
  // Note that if the size_t is bigger then the size of the array, no action will be taken.
  void Remove(const size_t &position);

  Value &operator[](const std::string &key) const;

  Value &operator[](const char *key) const;

  Value &operator[](const size_t &position) const;

  operator int32_t() const;

  operator double_t() const;

  operator std::string() const;

  operator bool() const;

  // This overrides every possible operator, and avoids
  // any issues with casting them on assignment.
  // Casting is done on calling equals instead.
  template <typename T>
  inline bool operator==(const T &value) const {
    return Equals_(value);
  };

  template <typename T>
  inline bool operator!=(const T &value) const {
    return !Equals_(value);
  };

  ~Value();

private:
  void Cleanup_();

  inline void AssertType_(ValueType type) const;

  inline void AssertType_(std::vector<ValueType> types) const;

  inline static std::string GetTypeString_(ValueType type);

  bool Equals_(const Value &that) const;

  void Copy_(const Value &that);

  void Move_(Value &&that);

  ValueType type_;

  union {
    int32_t as_int;
    double_t as_double;
    bool as_bool;
    std::string *as_string;
    Object *as_object;
    Array *as_array;
  };
};

} // namespace json

#endif	// MODELMAKER_JSON_VALUE_H_

