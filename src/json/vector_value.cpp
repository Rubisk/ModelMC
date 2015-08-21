#include <sstream>

#include "src/json/json.h"
#include "src/json/vector_value.h"


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

Value& VectorValue::operator= (const std::string &value)
{
    // TODO do this
    throw json_exception("Can't assign a string");
    return *this;
}

VectorValue::~VectorValue()
{
    vector_->erase(vector_->begin(), vector_->end());
}

} // namespace json