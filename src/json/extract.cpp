#include <vector>
#include <cstdlib>
#include "json/extract.h"

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
      }
      else if (*result == NULL) {
        return Status(kIOException, "Invalid key: " + key);
      }
      else {
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
      }
      else if (*result == NULL) {
        return Status(kIOException, "Invalid key: " + key);
      }
      else {
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

Status LoadIntArray(Value* tag, StringVector path,
                    size_t size, int32_t* output) {
  int32_t output_int[size];
  Status s;

  s = FindValueForPath(tag, path, tag);
  if (!s.IsOk()) {
    return s;
  }

  for (int i = 0; i < size; ++i) {
    Value** int_tag;
    tag->GetChild(i, int_tag);
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
  return s;
}

Status LoadStringValue(Value* tag, StringVector path,
                       std::string &output) {
  Status s;
  s = FindValueForPath(tag, path, tag);
  if (!s.IsOk()) {
    return s;
  }

  std::string found_value;
  s = tag->GetStringValue(&found_value);
  if (!s.IsOk()) {
    return s;
  }

  output = found_value;
  return s;
}

Status LoadBoolValue(Value* tag, StringVector path,
                     bool &output) {
  Status s;
  s = FindValueForPath(tag, path, tag);
  if (!s.IsOk()) {
    return s;
  }

  bool found_value;
  s = tag->GetBoolValue(&found_value);
  if (!s.IsOk()) {
    return s;
  }

  output = found_value;
  return s;
}

Status LoadIntValue(Value* tag, StringVector path,
                    int32_t &output) {
  Status s;
  s = FindValueForPath(tag, path, tag);
  if (!s.IsOk()) {
    return s;
  }

  int32_t found_value;
  s = tag->GetIntValue(&found_value);
  if (!s.IsOk()) {
    return s;
  }

  output = found_value;
  return s;
}

Status LoadIntArray(Value* tag, std::string path,
                    size_t size, int32_t* output) {
  StringVector v = {path};
  return LoadIntArray(tag, v, size, output);
}

Status LoadStringValue(Value* tag, std::string path,
                       std::string &output) {
  StringVector v = {path};
  return LoadStringValue(tag, v, output);
}

Status LoadBoolValue(Value* tag, std::string path,
                     bool &output) {
  StringVector v = {path};
  return LoadBoolValue(tag, v, output);
}

Status LoadIntValue(Value* tag, std::string path,
                    int32_t &output) {
  StringVector v = {path};
  return LoadIntValue(tag, v, output);
}