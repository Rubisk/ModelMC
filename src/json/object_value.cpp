#include <sstream>

#include "src/json/json.h"
#include "src/json/object_value.h"


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

Value& ObjectValue::operator= (const std::string &value)
{
    // TODO do this
    throw json_exception("Can't assign a string");
    return *this;
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

} // namespace json