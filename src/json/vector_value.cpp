#include <sstream>

#include "json/json.h"
#include "json/vector_value.h"
#include "json/util.h"

namespace json {

ValueType VectorValue::GetValueType() {
  return kVectorValue;
}

VectorValue::VectorValue() {
  vector_ = new ValueVector();
}

VectorValue::VectorValue(ValueVector* vector) {
  vector_ = vector;
}

void VectorValue::SaveToStream(std::ostream* output) {
  *output << "[";

  ValueVector::iterator it = vector_->begin();
  (*it)->SaveToStream(output);
  it++;
  while (it != vector_->end()) {
    *output << ",";
    (*it)->SaveToStream(output);
    it++;
  }
  *output << "]";
}

Status VectorValue::GetChild(const size_t& index, Value** &valueptr) {
  Status s;
  while (index >= vector_->size()) {
    vector_->push_back(NULL);
  }
  valueptr = &(*vector_)[index];
  return s;
}

Status VectorValue::LoadFromStream(std::istream &stream) {
  char next_char;
  stream >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '[') {
    return Status(kJsonError,
                  "Parsing Error: Expected '[', found '" + next_char);
  }

  while (true) {
    Status s = LoadAndSaveValue_(stream);
    if (!s.IsOk()) {
      return s;
    }
    stream >> std::skipws >> next_char >> std::noskipws;
    if (!stream.good()) {
      return Status(kJsonError, "Parsing Error: Stream corrupted.");
    }
    switch (next_char) {
    case (','):
      continue;
    case (']'):
      return s;
    default:
      return Status(kJsonError,
                    "Parsing Error: Expected ']' or ',', found '" + next_char);
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
  if (!s.IsOk()) {
    return s;
  }
  vector_->push_back(value);
  return s;
}

} // namespace json