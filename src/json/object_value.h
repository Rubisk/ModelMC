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
        
        Status operator[] (const std::string &key, Value** valueptr);
        
        Status save(std::ostream* output);
        
        Status loadFrom(std::istream &stream);
        
        ~ObjectValue();
    private:
        ValueMap* values_;
        
        Status loadAndSaveValue_ (std::istream &stream);
    };
    
} // namespace json

#endif	// OBJECT_VALUE_H

