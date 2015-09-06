#ifndef VECTOR_VALUE_H
#define	VECTOR_VALUE_H

#include <vector>
#include <iostream>

#include "src/json/json.h"


namespace json {


typedef std::vector<Value*> ValueVector;

class VectorValue : public Value {
public:
  VectorValue();

  VectorValue(ValueVector* values);

  Status get(const size_t &index, Value** valueptr);

  void save(std::ostream* output);

  Status loadFrom(std::istream &stream);

  ~VectorValue();
private:
  ValueVector* vector_;

  Status loadAndSaveValue_(std::istream &stream);
};

} // namespace json


#endif	// VECTOR_VALUE_H

