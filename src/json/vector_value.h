#ifndef VECTOR_VALUE_H
#define	VECTOR_VALUE_H

#include <vector>
#include <iostream>

#include "src/json/json.h"


namespace json {

    
typedef std::vector<Value*> ValueVector;


class VectorValue : public Value
{
public:
    VectorValue();

    VectorValue(ValueVector* values);

    json::Value* &operator[] (const size_t &index);
    
    void loadFrom(std::istream &stream);

    std::string as_string();

    ~VectorValue();
private:
    ValueVector* vector_;
    
    void loadAndSaveValue_(std::istream &stream);
};

} // namespace json


#endif	// VECTOR_VALUE_H

