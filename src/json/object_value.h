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
        
        std::string as_string();
        
        void loadFrom(std::iostream &stream);
        
        ~ObjectValue();
    private:
        ValueMap* values_;
        
        void loadAndSaveValue_ (std::iostream &stream);
    };
    
} // namespace json

#endif	// OBJECT_VALUE_H

