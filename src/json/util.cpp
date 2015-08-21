#include <streambuf>
#include <sstream>
#include <assert.h>

#include "src/json/util.h"

namespace json {
    
size_t findType(const std::stringstream &ss)
{
    std::stringstream temp;
    temp << ss.rdbuf();
    char a;
    temp >> std::skipws >> a;

    if(a == '\"') return STRING_VALUE;
    if(a == '{') return OBJECT_VALUE;
    if(a == '[') return VECTOR_VALUE;
    return INT_VALUE;
}

std::string readName(std::stringstream &ss)
{
    char a;
    ss >> std::skipws >> a;
    assert(a == '\"');
    std::string name = "";
    while(ss >> std::skipws >> a && a != '\"') name += a;
    return name;
}

} // namespace json

