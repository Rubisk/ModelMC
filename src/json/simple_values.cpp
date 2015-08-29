#include <cstdlib>
#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/simple_values.h"
#include "util.h"

namespace json {
    
IntValue::IntValue(const int32_t &value)
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

void IntValue::loadFrom(std::istream &stream)
{
    stream >> std::skipws >> value_ >> std::noskipws;
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

void StringValue::loadFrom(std::istream &stream)
{
    value_ = loadName(stream);
}


BoolValue::BoolValue(const bool &value)
{
    value_ = value;
}

Value& BoolValue::operator= (const std::string &value)
{
    if(!(value == "true" || value == "false"))
        throw json_exception("No correct bool formatting");
    value_ = (value == "true");
    return *this;
}

Value& BoolValue::operator= (const int &value)
{
    value_ = (value != 0);
    return *this;
}

bool BoolValue::as_bool()
{
    return value_;
}

std::string BoolValue::as_string()
{
    return value_ ? "true" : "false";
}

void BoolValue::loadFrom(std::istream &stream)
{
    char next_char;
    stream >> std::skipws >> next_char >> std::noskipws;
    
    if(next_char == 'f')
    {
        for(char c : "alse")
        {
            stream >> next_char;
            if(next_char != c)
                throw json_exception("No correct bool formatting");
            if(c == 'e') break;
        }
        value_ = false;
    }
    else if (next_char == 't')
    {
        for(char c : "rue")
            {
                stream >> next_char;
                if(next_char != c)
                    throw json_exception("No correct bool formatting");
                if(c == 'e') break;
            }
        value_ = true;
    }
    else throw json_exception("Bool didn't start with f or r");
}
} // namespace json
