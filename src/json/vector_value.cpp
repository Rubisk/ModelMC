#include <sstream>

#include "src/json/json.h"
#include "src/json/vector_value.h"
#include "src/json/util.h"

namespace json {

VectorValue::VectorValue()
{
    vector_ = new ValueVector();
}

VectorValue::VectorValue(ValueVector* vector){
    vector_ = vector;
}

std::string VectorValue::save()
{
    std::stringstream ss;
    ss << "[";
    
    ValueVector::iterator it = vector_->begin();
    ss << (*it)->save();
    it++;
    while(it != vector_->end())
    {
        ss << ",";
        ss << (*it)->save();
        it++;
    }
    ss << "]";
    std::string a = ss.str();
    return ss.str();
}

Value* &VectorValue::operator [](const size_t& index)
{
    return (*vector_)[index];
}

void VectorValue::loadFrom(std::istream &stream)
{
    char first_char;
    stream >> std::skipws >> first_char >> std::noskipws;
    if(first_char != '[') throw json_exception("Vector didn't start with [.");
    while(true)
    {
        char next_char;
        loadAndSaveValue_(stream);
        stream >> std::skipws >> next_char >> std::noskipws;
        
        if(next_char == ',') continue;
        if(next_char == ']') break;
        throw json_exception("Next value in vector is not , or ]");
    }
}


VectorValue::~VectorValue()
{
    for(ValueVector::iterator it = vector_->begin(); it != vector_->end(); it++)
    {
        delete *it;
    }
    delete vector_;
}


void VectorValue::loadAndSaveValue_(std::istream& stream)
{
    Value* value = loadValue(stream);
    vector_->push_back(value);
}

} // namespace json