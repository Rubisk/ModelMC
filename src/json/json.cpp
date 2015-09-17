#include <sstream>
#include <cstdlib>
#include <fstream>

#include "json/json.h"
#include "json/util.h"

namespace json {

Status Value::GetIntValue(int32_t* output) {
  return Status(kJsonError, "Value has no 'int' attribute.");
}

Status Value::GetBoolValue(bool* output) {
  return Status(kJsonError, "Value has no 'bool' attribute.");
}

Status Value::GetStringValue(std::string* output) {
  return Status(kJsonError, "Value has no 'string' attribute.");
}

Status Value::GetChild(const std::string &key, Value** &valueptr) {
  return Status(kJsonError, "Value can't lookup by string.");
}

Status Value::GetChild(const size_t &index, Value** &valueptr) {
  return Status(kJsonError, "Value can't lookup by int.");
}

Status Value::operator=(const std::string &value) {
  return Status(kJsonError, "Value can't assign a string.");
}

Status Value::operator=(const char* value) {
  return Status(kJsonError, "Value can't assign a string.");
}

Status Value::operator=(const int32_t &value) {
  return Status(kJsonError, "Value can't assign an int.");
}

Status Value::operator=(const bool &value) {
  return Status(kJsonError, "Value can't assign a bool.");
}

Status LoadFromFile(const std::string &file, Value* &valueptr) {
  std::ifstream stream;
  stream.open(file, std::ios::binary);

  Value* result;
  Status s = LoadValue(stream, result);
  if (s.IsOk()) {
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

