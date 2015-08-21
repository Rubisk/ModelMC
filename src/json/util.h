#ifndef UTIL_H
#define	UTIL_H

#include <iostream>

#include "src/json/json.h"


namespace json {
    

size_t findType(const std::iostream &stream);

std::string loadName(std::iostream &stream);

Value* loadValue(std::iostream &stream);

void saveValue(std::iostream &stream, const Value* value);

} //namespace json

#endif	// UTIL_H

