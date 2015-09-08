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

Status Value::get(const std::string &key, Value** valueptr) {
  return kValueError;
}

Status Value::get(const size_t &index, Value** valueptr) {
  return kValueError;
}

Status Value::operator=(const std::string &value) {
  return kValueError;
}

Status Value::operator=(const int32_t &value) {
  return kValueError;
}

Status Value::operator=(const bool &value) {
  return kValueError;
}

Status load(std::istream &stream, Value** valueptr) {
  Value* result;
  Status s = loadValue(stream, &result);
  if (s == kOk) {
    *valueptr = result;
  }
  return s;
};

Status load(const std::string &file, Value** valueptr) {
  std::ifstream stream;
  stream.open(file, std::ios::binary);
  Value* result;

  Status s = load(stream, &result);
  if (s == kOk) {
    *valueptr = result;
  }

  stream.close();
  return s;
}

void save(std::ostream &stream, Value* value) {
  return value->save(&stream);
}

void save(const std::string &file, Value* value) {
  std::ofstream stream;
  stream.open(file);

  save(stream, value);

  stream.close();
}

}

