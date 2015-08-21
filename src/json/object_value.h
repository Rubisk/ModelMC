#ifndef OBJECT_VALUE_H
#define	OBJECT_VALUE_H

#include <map>
#include "src/json/json.h"


namespace json {
    
typedef std::map<std::string, Value*> ValueMap;

    class ObjectValue : public Value
    {
    public:
        ObjectValue();
        
        ObjectValue(ValueMap* values);
        
        Value* &operator[] (const std::string &key);
        
        Value& operator= (const std::string &value);
        
        std::string as_string();
        
        ~ObjectValue();
    private:
        ValueMap* values_;
    };
    
} // namespace json

#endif	// OBJECT_VALUE_H

