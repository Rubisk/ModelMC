#include <sstream>
#include <cstdlib>
#include <fstream>

#include "json/json.h"
#include "json/util.h"

namespace json {

Status Value::GetIntValue(int32_t* output) {
  return kValueError;
}

Status Value::GetBoolValue(bool* output) {
  return kValueError;
}

Status Value::GetStringValue(std::string* output) {
  return kValueError;
}

Status Value::GetChild(const std::string &key, Value** &valueptr) {
  return kValueError;
}

Status Value::GetChild(const size_t &index, Value** &valueptr) {
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

Status LoadFromFile(const std::string &file, Value* &valueptr) {
  std::ifstream stream;
  stream.open(file, std::ios::binary);

  Value* result;
  Status s = LoadValue(stream, &result);
  if (s == kOk) {
    valueptr = result;
  }

  stream.close();
  return s;
}

void SaveToFile(const std::string &file, Value* value) {
  std::ofstream stream;
  stream.open(file);

  value->SaveToStream(&stream);

  stream.close();
}

}

