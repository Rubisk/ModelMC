#include <sstream>
#include "src/json/json_values.h"


namespace json
{
    
    int32_t Value::as_int() 
    { 
        throw convert_exception("Can't convert to int");
    }

    Value* Value::operator[] (const std::string &key)
    {
        throw convert_exception("Can't lookup by string");
    }

    Value* Value::operator[] (const size_t &index)
    {
        throw convert_exception("Can't lookup by index");
    }
    
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
    
    Value* VectorValue::operator [](const size_t& index)
    {
        return (*vector_)[index];
    }
    
    
    ObjectValue::ObjectValue()
    {
        values_ = new ValueMap();
    }
    
    ObjectValue::ObjectValue(ValueMap* values)
    {
        values_ = values;
    }
    
    Value* ObjectValue::operator[](const std::string &key)
    {
        return (*values_)[key];
    }
    
    std::string ObjectValue::as_string()
    {
        std::stringstream ss;
        ss << "{";
        for(ValueMap::iterator it = values_->begin(); it != values_->end(); it++)
        {
            ss << "\"" << it->first << "\":\"" << it->second->as_string() << "\",";
        }
        ss << "}";
        return ss.str();
    }
    
    ObjectValue::~ObjectValue()
    {
        values_->erase(values_->begin(), values_->end());
        delete values_;
    }
    
    IntValue::IntValue(int32_t value)
    {
        value_ = value;
    }
    
    int32_t IntValue::as_int()
    {
        return value_;
    }
    
    std::string IntValue::as_string()
    {
        std::stringstream ss;
        ss << value_;
        return ss.str();
    }
    
    StringValue::StringValue(std::string value)
    {
        value_ = value;
    }
    
    std::string StringValue::as_string()
    {
        return value_;
    }
}

