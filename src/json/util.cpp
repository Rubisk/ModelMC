#include <streambuf>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "src/json/util.h"

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

} // namespace json

