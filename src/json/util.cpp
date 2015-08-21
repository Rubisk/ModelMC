#include <streambuf>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "src/json/json.h"
#include "src/json/util.h"
#include "src/json/object_value.h"
#include "src/json/vector_value.h"
#include "src/json/simple_values.h"

namespace json {
    
size_t findType(const std::iostream &stream)
{
    std::stringstream temp;
    temp << stream.rdbuf();
    char a;
    temp >> std::skipws >> a;

    if(a == '\"') return STRING_VALUE;
    if(a == '{') return OBJECT_VALUE;
    if(a == '[') return VECTOR_VALUE;
    return INT_VALUE;
}

std::string loadName(std::iostream &stream)
{
    char a;
    stream >> std::skipws >> a;
    assert(a == '\"');
    std::string name = "";
    while(stream >> std::skipws >> a && a != '\"') name += a;
    return name;
}

Value* loadValue(std::iostream &stream)
{
    size_t type = findType(stream);
    Value* value;
    if(type == OBJECT_VALUE) value = new ObjectValue();
    if(type == INT_VALUE) value = new IntValue();
    if(type == STRING_VALUE) value = new StringValue();
    if(type == VECTOR_VALUE) value = new VectorValue();
    value->loadFrom(stream);
}

} // namespace json

