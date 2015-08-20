#include <sstream>
#include <cstdlib>

#include "src/json/json_values.h"


namespace json
{
    
    int32_t Value::as_int() 
    { 
        throw json_exception("Can't convert to integer");
    }

    Value* &Value::operator[] (const std::string &key)
    {
        throw json_exception("Can't lookup by string");
    }

    Value* &Value::operator[] (const size_t &index)
    {
        throw json_exception("Can't lookup by index");
    }
    
    Value* Value::operator= (const std::string &value)
    {
        throw json_exception("Can't assign a string");
    }
    
    Value* Value::operator= (const int32_t &value)
    {
        throw json_exception("Can't assign an integer");
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
    
    Value* &VectorValue::operator [](const size_t& index)
    {
        return (*vector_)[index];
    }
    
    Value* VectorValue::operator= (const std::string &value)
    {
        // TODO do this
        throw json_exception("Can't assign a string");
    }
    
    VectorValue::~VectorValue()
    {
        vector_->erase(vector_->begin(), vector_->end());
    }

    
    ObjectValue::ObjectValue()
    {
        values_ = new ValueMap();
    }
    
    ObjectValue::ObjectValue(ValueMap* values)
    {
        values_ = values;
    }
    
    Value* &ObjectValue::operator[](const std::string &key)
    {
        return (*values_)[key];
    }
    
    Value* ObjectValue::operator= (const std::string &value)
    {
        // TODO do this
        throw json_exception("Can't assign a string");
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
        for(ValueMap::iterator it = values_->begin(); it != values_->end(); it++)
        {
            delete it->second;
        }
        delete values_;
    }
    
    IntValue::IntValue(int32_t value)
    {
        value_ = value;
    }
    
    Value* IntValue::operator= (const std::string &value)
    {
        value_ = atoi(value.c_str());
        return this;
    }
    
    Value* IntValue::operator= (const int32_t &value)
    {
        value_ = value;
        return this;
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
    
    StringValue::StringValue(const std::string &value)
    {
        value_ = value;
    }
    
    Value* StringValue::operator= (const std::string &value)
    {
        value_ = value;
        return this;
    }
    
    std::string StringValue::as_string()
    {
        return value_;
    }
}

