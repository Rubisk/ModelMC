#include "json/iterator.h"

using namespace json;
using Iterator = Value::Iterator;

Iterator::Iterator(Value *target) : value_(target) {
  value_->AssertType_({kArrayValue, kObjectValue});
  switch (value_->type_) {
  case kArrayValue:
    array_it = new Array::iterator(value_->as_array->begin());
    break;
  case kObjectValue:
    object_it = new Object::iterator(value_->as_object->begin());
    break;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

bool Iterator::Valid() {
  switch (value_->type_) {
  case kArrayValue:
    return *array_it != value_->as_array->end();
  case kObjectValue:
    return *object_it != value_->as_object->end();
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

void Iterator::Next() {
  switch (value_->type_) {
  case kArrayValue:
    (*array_it)++;
    break;
  case kObjectValue:
    (*object_it)++;
    break;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

std::string Iterator::GetKey() const {
  value_->AssertType_(kObjectValue);
  return (**object_it).first;
}

Value &Iterator::Get() const {
  switch (value_->type_) {
  case kArrayValue:
    return *(**array_it);
  case kObjectValue:
    return *(**object_it).second;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

Iterator::~Iterator() {
  switch (value_->type_) {
  case kArrayValue:
    delete array_it;
    break;
  case kObjectValue:
    delete object_it;
    break;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}
