#include <sstream>
#include <cstdlib>

#include "src/json/json.h"


namespace json
{
    
    int32_t Value::as_int() 
    { 
        throw json_exception("Can't convert to integer");
    }
    
    bool Value::as_bool()
    {
        throw json_exception("Can't convert to boolean");
    }
    
    std::string Value::as_string()
    {
        throw json_exception("Can't convert to string");
    }

    Value* &Value::operator[] (const std::string &key)
    {
        throw json_exception("Can't lookup by string");
    }

    Value* &Value::operator[] (const size_t &index)
    {
        throw json_exception("Can't lookup by index");
    }
    
    Value& Value::operator= (const std::string &value)
    {
        throw json_exception("Can't assign a string");
    }
    
    Value& Value::operator= (const int32_t &value)
    {
        throw json_exception("Can't assign an integer");
    }
}

