//Provides utility functions to convert extract data
//from Value objects and store it as general objects.

#ifndef EXTRACT_JSON_H
#define	EXTRACT_JSON_H

#include <vector>
#include "json/json.h"

typedef std::vector<std::string> StringVector;

//Finds a value by starting iterating over path,
//and looking for the key in path in root_tag and it's corresponding childs.
//Elements of path should point to a string or an int.
Status FindValueForPath(json::Value* root_tag, StringVector path,
        json::Value* &output_tag);

//Loads an int[] from a Value tag.
//Name should be the key to find the array at. Size is the size of the array.
//The values will be written to output. Make sure output is big enough
//to store (size) elements, otherwise a SIGSEGV will be send out.
Status LoadIntArray(json::Value* tag, std::string name,
        size_t size, int32_t* output);

#endif	// EXTRACT_JSON_H

