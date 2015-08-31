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

std::string ObjectValue::save()
{
    std::stringstream ss;
    ss << "{";
    ValueMap::iterator it = values_->begin();
    ss << "\"" << it->first << "\":" << it->second->save();
    it++;
    while(it != values_->end())
    {
        ss << ",\"" << it->first << "\":" << it->second->save();
        it++;
    }
    ss << "}";
    return ss.str();
}

void ObjectValue::loadFrom(std::istream &stream)
{
    char next_char;
    stream >> std::skipws >> next_char >> std::noskipws;
    if(next_char != '{') throw json_exception("Object didn't start with {.");
    while(true)
    {
        loadAndSaveValue_(stream);
        stream >> std::skipws >> next_char >> std::noskipws;
        if(next_char == ',') continue;
        if(next_char == '}') break;
        throw json_exception("Next value in object is not , or }");
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
    stream >> std::skipws >> next_char >> std::noskipws;
    if(next_char != ':') throw json_exception("Key/value in object not seperated by \":\".");
    Value* value = loadValue(stream);
    (*this)[name] = value;
}

} // namespace json