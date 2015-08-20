#ifndef VECTOR_VALUE_H
#define	VECTOR_VALUE_H

#include "src/json/value.h"


namespace json {

    
typedef std::vector<Value*> ValueVector;


class VectorValue : public Value
{
public:
    VectorValue();

    VectorValue(ValueVector* values);

    json::Value* &operator[] (const size_t &index);
    
    json::Value* operator= (const std::string &value);

    std::string as_string();

    ~VectorValue();
private:
    ValueVector* vector_;
};

} // namespace json


#endif	// VECTOR_VALUE_H

