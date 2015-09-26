#include "json/iterator.h"

using namespace json;
using Iterator = Value::Iterator;

Iterator::Iterator(Value *target) : value_(target) {
  value_->AssertType_({ArrayVal, ObjectVal});
  switch (value_->type_) {
  case ArrayVal:
    array_it = new Array::iterator(value_->as_array->begin());
    break;
  case ObjectVal:
    object_it = new Object::iterator(value_->as_object->begin());
    break;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

bool Iterator::Valid() {
  switch (value_->type_) {
  case ArrayVal:
    return *array_it != value_->as_array->end();
  case ObjectVal:
    return *object_it != value_->as_object->end();
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

void Iterator::Next() {
  switch (value_->type_) {
  case ArrayVal:
    (*array_it)++;
    break;
  case ObjectVal:
    (*object_it)++;
    break;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

std::string Iterator::GetKey() const {
  value_->AssertType_(ObjectVal);
  return (**object_it).first;
}

Value &Iterator::Get() const {
  switch (value_->type_) {
  case ArrayVal:
    return *(**array_it);
  case ObjectVal:
    return *(**object_it).second;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}

Iterator::~Iterator() {
  switch (value_->type_) {
  case ArrayVal:
    delete array_it;
    break;
  case ObjectVal:
    delete object_it;
    break;
  default:
    throw json_exception("Value changed to non-iterable type.");
  }
}
