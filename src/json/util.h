#ifndef UTIL_H
#define	UTIL_H

#include <iostream>

#include "src/json/json.h"


namespace json {
    

Status findType(std::istream &stream, size_t* output);

Status loadName(std::istream &stream, std::string* output);

Status loadValue(std::istream &stream, Value** valueptr);

Status saveValue(std::iostream &stream, const Value* value);

} //namespace json

#endif	// UTIL_H

