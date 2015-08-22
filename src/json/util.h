#ifndef UTIL_H
#define	UTIL_H

#include <iostream>

#include "src/json/json.h"


namespace json {
    

size_t findType(std::istream &stream);

std::string loadName(std::istream &stream);

Value* loadValue(std::istream &stream);

void saveValue(std::iostream &stream, const Value* value);

} //namespace json

#endif	// UTIL_H

