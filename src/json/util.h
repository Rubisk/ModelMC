#ifndef UTIL_H
#define	UTIL_H

#include <iostream>
#include <vector>

#include "json/json.h"

namespace json {

Status FindType(std::istream &stream, ValueType* output);

Status LoadName(std::istream &stream, std::string* output);

Status LoadValue(std::istream &stream, Value** valueptr);

Status FindValueForPath(Value* root_tag, std::vector<void*> path, Value* &output_tag);

} //namespace json

#endif	// UTIL_H

