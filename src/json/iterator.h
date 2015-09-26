#ifndef MODELMAKER_JSON_ITERATOR_H_
#define MODELMAKER_JSON_ITERATOR_H_

#include "json/value.h"

namespace json {

class Value::Iterator {
public:
  Iterator(Value *target);

  // Returns false if the final element in the list 
  // has been surpassed. Once that happens, the object
  // becomes invalid and should be deleted.
  bool Valid();

  void Next();

  // Returns the key at the current position.
  // Throws if it's iterating over an Array.
  std::string GetKey() const;

  // Returns the Value at the current position.
  Value &Get() const;

  ~Iterator();
private:
  union {
    Value::Object::iterator* object_it;
    Value::Array::iterator* array_it;
  };

  Value *value_;
};

} // namespace json

#endif //MODELMAKER_JSON_ITERATOR_H_