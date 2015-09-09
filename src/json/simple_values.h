#ifndef SIMPLE_VALUES_H
#define	SIMPLE_VALUES_H

#include "src/json/json.h"

namespace json {

class IntValue : public Value {
public:

  IntValue() {
  };

  IntValue(const int32_t &value);

  void SaveValue(std::ostream* output);

  Status GetIntValue(int32_t* output);

  Status operator=(const int32_t &value);

  Status LoadValue(std::istream &stream);
private:
  int32_t value_;
};

class StringValue : public Value {
public:

  StringValue() {
  };

  StringValue(const std::string &value);

  Status GetStringValue(std::string* output);

  void SaveValue(std::ostream* output);

  Status operator=(const std::string &value);

  Status LoadValue(std::istream &stream);
private:
  std::string value_;
};

class BoolValue : public Value {
public:

  BoolValue() {
  };

  BoolValue(const bool &value);

  Status GetBoolValue(bool* output);

  void SaveValue(std::ostream* output);

  Status operator=(const bool &value);

  Status LoadValue(std::istream &stream);
private:
  bool value_;
};

} // namespace json

#endif	// SIMPLE_VALUES_H

