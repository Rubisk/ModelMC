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

std::string VectorValue::as_string()
{
    std::stringstream ss;
    ss << "[";
    for(ValueVector::iterator it = vector_->begin(); it != vector_->end(); it++)
    {
        ss << "\"" << (*it)->as_string() << "\",";
    }
    ss << "}";
}

Value* &VectorValue::operator [](const size_t& index)
{
    return (*vector_)[index];
}

void VectorValue::loadFrom(std::istream &stream)
{
    char first_char;
    stream >> std::skipws >> first_char >> std::noskipws;
    if(first_char != '[') throw json_exception("Invalid json format.");
    while(true)
    {
        char next_char;
        loadAndSaveValue_(stream);
        stream >> std::skipws >> next_char >> std::noskipws;
        
        std::cout << stream.tellg();
        if(next_char == ',') continue;
        if(next_char == ']') break;
        throw json_exception("Invalid json format.");
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