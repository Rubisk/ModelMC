#ifndef UTIL_H
#define	UTIL_H

namespace json {
    
enum Types { OBJECT_VALUE, VECTOR_VALUE, INT_VALUE, STRING_VALUE };

size_t findType(const std::stringstream &ss);

std::string loadName(std::stringstream &ss);

} //namespace json

#endif	// UTIL_H

