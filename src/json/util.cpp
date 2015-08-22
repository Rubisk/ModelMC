#include <streambuf>
#include <iostream>
#include <sstream>

#include "src/json/json.h"
#include "src/json/util.h"
#include "src/json/object_value.h"
#include "src/json/vector_value.h"
#include "src/json/simple_values.h"

namespace json {
    
size_t findType(std::istream &stream)
{
    char a;
    auto old_pos = stream.tellg();
    stream >> std::skipws >> a >> std::noskipws;
    stream.seekg(old_pos);

    if(a == '\"') return STRING_VALUE;
    if(a == '{') return OBJECT_VALUE;
    if(a == '[') return VECTOR_VALUE;
    return INT_VALUE;
}

std::string loadName(std::istream &stream)
{
    char a;
    stream >> std::skipws >> a >> std::noskipws;
    if(a != '"') throw json_exception("Invalid json format.");
    std::string name = "";
    while(stream >> a && a != '"') name += a;
    return name;
}

Value* loadValue(std::istream &stream)
{
    size_t type = findType(stream);
    Value* value;
    if(type == OBJECT_VALUE) value = new ObjectValue();
    if(type == INT_VALUE) value = new IntValue();
    if(type == STRING_VALUE) value = new StringValue();
    if(type == VECTOR_VALUE) value = new VectorValue();
    value->loadFrom(stream);
    return value;
}

} // namespace json

