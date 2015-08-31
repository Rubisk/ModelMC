#include <sstream>
#include <cstdlib>
#include <fstream>

#include "src/json/json.h"
#include "src/json/util.h"


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
    
    
    Value* load(std::istream &stream)
    {
        return loadValue(stream);
    }


    Value* load(const std::string &file)
    {
        std::ifstream stream;
        stream.open(file, std::ios::binary);
        Value* to_return = load(stream);
        stream.close();
        return to_return;
    }


    void save(std::ostream &stream, Value* value)
    {
        std::string output = value->save();
        stream << output;
    }


    void save(const std::string &file, Value* value)
    {
        std::ofstream stream;
        stream.open(file);
        save(stream, value);
        stream.close();
    }
}

