#ifndef UTIL_H
#define	UTIL_H

#include <iostream>

#include "json/json.h"

namespace json {

Status FindType(std::istream &stream, ValueType* output);

Status LoadName(std::istream &stream, std::string* output);

Status LoadValue(std::istream &stream, Value* &valueptr);

} //namespace json

#endif	// UTIL_H

