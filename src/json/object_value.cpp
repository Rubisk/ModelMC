#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/object_value.h"
#include "src/json/util.h"

namespace json {

    
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

void ObjectValue::loadFrom(std::istream &stream)
{
    char next_char;
    stream >> std::skipws >> next_char;
    if(next_char != '{') throw json_exception("Invalid json format.");
    while(true)
    {
        loadAndSaveValue_(stream);
        stream >> std::skipws >> next_char;
        if(next_char == ',') continue;
        if(next_char == '}') break;
        throw json_exception("Invalid json format.");
    }
}


ObjectValue::~ObjectValue()
{
    for(ValueMap::iterator it = values_->begin(); it != values_->end(); it++)
    {
        delete it->second;
    }
    delete values_;
}


void ObjectValue::loadAndSaveValue_(std::istream& stream)
{
    std::string name = loadName(stream);
    char next_char;
    stream >> std::skipws >> next_char;
    if(next_char != ':') throw json_exception("Invalid json format.");
    Value* value = loadValue(stream);
    (*this)[name] = value;
}

} // namespace json