#include <cstdlib>
#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/simple_values.h"
#include "util.h"

namespace json {
    
IntValue::IntValue(int32_t value)
{
    value_ = value;
}

Value& IntValue::operator= (const std::string &value)
{
    value_ = atoi(value.c_str());
    return *this;
}

Value& IntValue::operator= (const int32_t &value)
{
    value_ = value;
    return *this;
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

void IntValue::loadFrom(std::iostream &stream)
{
    stream >> value_;
}

StringValue::StringValue(const std::string &value)
{
    value_ = value;
}

Value& StringValue::operator= (const std::string &value)
{
    value_ = value;
    return *this;
}

std::string StringValue::as_string()
{
    return value_;
}

void StringValue::loadFrom(std::iostream &stream)
{
    value_ = loadName(stream);
}

} // namespace json
