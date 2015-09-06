#ifndef UTIL_H
#define	UTIL_H

#include <iostream>

#include "src/json/json.h"

namespace json {

Status findType(std::istream &stream, ValueType* output);

Status loadName(std::istream &stream, std::string* output);

Status loadValue(std::istream &stream, Value** valueptr);

} //namespace json

#endif	// UTIL_H

