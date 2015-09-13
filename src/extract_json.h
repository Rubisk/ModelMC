//Provides utility functions to convert extract data
//from Value objects and store it as general objects.

#ifndef EXTRACT_JSON_H
#define	EXTRACT_JSON_H

#include "json/json.h"

//Finds a value by starting iterating over path,
//and looking for the key in path in root_tag and it's corresponding childs.
//Elements of path should point to a string or an int.
Status FindValueForPath(json::Value* root_tag, std::vector<void*> path,
        json::Value* &output_tag);

#endif	// EXTRACT_JSON_H

