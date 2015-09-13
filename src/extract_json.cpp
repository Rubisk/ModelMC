#include <vector>
#include <cstdlib>
#include "extract_json.h"

using namespace json;

Status FindValueForPath(Value* root_tag, StringVector path,
        Value* &output_tag) {
  Status s;

  for (std::string key : path) {
    switch (root_tag->GetValueType()) {
      case kVectorValue:
      {
        Value** result;
        s = root_tag->GetChild(atoi(key.c_str()), result);
        if (!s.IsOk()) {
          return s;
        } else if (*result == NULL) {
          return Status(kIOException, "Invalid key: " + key);
        } else {
          root_tag = *result;
          continue;
        }
      }
      case kObjectValue:
      {
        Value** result;
        s = root_tag->GetChild(key, result);
        if (!s.IsOk()) {
          return s;
        } else if (*result == NULL) {
          return Status(kIOException, "Invalid key: " + key);
        } else {
          root_tag = *result;
          continue;
        }
      }
      default:
      {
        return Status(kIOException, "Path led to unindexable type.");
      }
    }
  }
  output_tag = root_tag;
  return s;
}

Status LoadIntArray(Value* tag, std::string name, size_t size, int32_t* output) {
  Value** output_tag;
  int32_t output_int[size];
  Status s;

  s = tag->GetChild(name, output_tag);
  if (!s.IsOk()) {
    return s;
  }

  for (int i = 0; i < size; ++i) {
    Value** int_tag;
    (*output_tag)->GetChild(i, int_tag);
    if (!s.IsOk()) {
      return s;
    }
    s = (*int_tag)->GetIntValue(&output_int[i]);
    if (!s.IsOk()) {
      return s;
    }
  }
  for (int i = 0; i < size; ++i) {
    *output = output_int[i];
    ++output;
  }
}
