#ifndef UTIL_H
#define	UTIL_H

#include <iostream>

namespace json {
    
enum Types { OBJECT_VALUE, VECTOR_VALUE, INT_VALUE, STRING_VALUE };

size_t findType(const std::iostream &stream);

std::string loadName(std::iostream &stream);

} //namespace json

#endif	// UTIL_H

