#ifndef JSON_H
#define JSON_H

#include <stdexcept>
#include <iostream>

namespace json {

enum ValueType {
  kObjectValue, kVectorValue, kIntValue, kStringValue, kBoolValue
};

enum Status {
  kOk,
  kParseError,
  kValueError,
  kUnkwownError,
};

class Value {
public:
  //Saves the value as valid json formatting.
  //
  //Paramater output should specify the stream to write the saved value to.
  //
  //Should only be called on ObjectValues, otherwise this will return
  //only part of a valid Json string. Calling this on an ArrayValue,
  //for example, will return something like:
  //      [1, 2, 3, 4, 5]
  //instead of
  //      {"key": [1, 2, 3, 4, 5]}
  //
  //Returns kOk if all is well, kUnkwownError otherwise.
  virtual void save(std::ostream* output) = 0;

  //Access the underlaying std::string object of a StringValue.
  //Returns kValueError if the value is not a StringValue.
  virtual Status as_string(std::string* output);

  //Access the underlaying int value of an IntValue.
  //Returns kValueError if the value is not an IntValue.
  virtual Status as_int(int32_t* output);

  //Access the underalaying bool value of a BoolValue.
  //Returns kValueError if the value is not a BoolValue.
  virtual Status as_bool(bool* output);

  //Access a given key in an object.
  //valueptr can be used to access the new element.
  //Example:
  //    //Load some_object_value from a file.
  //    Value** output;
  //    (*some_object_value)->get("key", &output);
  virtual Status get(const std::string &key, Value** &valueptr);

  //Access a given index in an object.
  //valueptr can bve used to access the element afterwards.
  //Example:
  //    //Load some_object_value from a file.
  //    Value* output;
  //    (*some_object_value)->get(5, &output);
  virtual Status get(const size_t &index, Value** &valueptr);

  //Only defined for IntValue, returns kValueError otherwise.
  //Sets the underlaying value of an IntValue to value.
  virtual Status operator=(const int32_t &value);

  //Only defined for StringValue, returns kValueError otherwise.
  //Sets the underlaying value of an StringValue to value.
  virtual Status operator=(const std::string &value);

  //Only defined for BoolValue, returns kValueError otherwise.
  //Sets the underlaying value of a BoolValue to value.
  virtual Status operator=(const bool &value);

  //Loads the underlaying value from a stream.
  //For example, imagine a stream like "1234,\"asdf\":def}"
  //Then:
  //    Value* value = new IntValue();
  //    value->loadFrom(&stream);
  //Now value has a value of 1234, and the stream is reduced to
  //",\"asdf\":def}"
  virtual Status loadFrom(std::istream &stream) = 0;

  virtual ~Value() {
  };

};

Status load(const std::string &file, Value* &valueptr);

void save(const std::string &file, Value* value);

} // namespace json

#endif	// JSON_H

