#include <sstream>

#include "src/json/json.h"
#include "src/json/vector_value.h"
#include "src/json/util.h"

namespace json {

VectorValue::VectorValue() {
  vector_ = new ValueVector();
}

VectorValue::VectorValue(ValueVector* vector) {
  vector_ = vector;
}

void VectorValue::SaveValue(std::ostream* output) {
  *output << "[";

  ValueVector::iterator it = vector_->begin();
  (*it)->SaveValue(output);
  it++;
  while (it != vector_->end()) {
    *output << ",";
    (*it)->SaveValue(output);
    it++;
  }
  *output << "]";
}

Status VectorValue::GetChild(const size_t& index, Value** &valueptr) {
  while (index >= vector_->size()) {
    vector_->push_back(NULL);
  }
  valueptr = &(*vector_)[index];
  return kOk;
}

Status VectorValue::LoadValue(std::istream &stream) {
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '[') {
    return kParseError;
  }

  while (true) {
    Status s = LoadAndSaveValue_(stream);
    if (s != kOk) {
      return s;
    }
    stream >> std::skipws >> next_char >> std::noskipws;
    if (!stream.good()) {
      return kUnkwownError;
    }
    switch (next_char) {
      case (','):
        continue;
      case (']'):
        return kOk;
      default:
        return kParseError;
    }
  }
}

VectorValue::~VectorValue() {
  for (ValueVector::iterator it = vector_->begin(); it != vector_->end(); it++) {
    delete *it;
  }
  delete vector_;
}

Status VectorValue::LoadAndSaveValue_(std::istream& stream) {
  Value* value;
  Status s = LoadValue(stream, &value);
  if (s != kOk) {
    return s;
  }
  vector_->push_back(value);
  return kOk;
}

} // namespace json