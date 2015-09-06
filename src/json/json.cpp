#include <sstream>
#include <cstdlib>
#include <fstream>

#include "src/json/json.h"
#include "src/json/util.h"


namespace json {

Status Value::as_int(int32_t* output) {
  return kValueError;
}

Status Value::as_bool(bool* output) {
  return kValueError;
}

Status Value::as_string(std::string* output) {
  return kValueError;
}

Status Value::operator[](const std::string &key, Value** valueptr) {
  return kValueError;
}

Status Value::operator[](const size_t &index, Value** valueptr) {
  return kValueError;
}

Status Value::operator=(const std::string &value) {
  return kValueError;
}

Status Value::operator=(const int32_t &value) {
  return kValueError;
}

Value* load(std::istream &stream) {
  return loadValue(stream);
}

Value* load(const std::string &file) {
  std::ifstream stream;
  stream.open(file, std::ios::binary);
  Value* to_return = load(stream);
  stream.close();
  return to_return;
}

void save(std::ostream &stream, Value* value) {
  std::string output = value->save();
  stream << output;
}

void save(const std::string &file, Value* value) {
  std::ofstream stream;
  stream.open(file);
  save(stream, value);
  stream.close();
}

}

