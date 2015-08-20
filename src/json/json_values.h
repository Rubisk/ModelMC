#ifndef JSON_VALUES_H
#define	JSON_VALUES_H

#include <exception>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>


namespace json
{
    
    class json_exception : public std::exception
    {
    public:
        json_exception(const char *msg) : err_msg(msg) {};
        ~json_exception() throw() {};
        const char *what() const throw() { return this->err_msg.c_str(); };
    private:
        std::string err_msg;
    };
    
    
    class Value
    {
    public:
        virtual std::string as_string() = 0;
        
        virtual int32_t as_int();
        
        virtual Value* &operator[] (const std::string &key);
        
        virtual Value* &operator[] (const size_t &index);
        
        virtual Value* operator= (const int32_t &value);
        
        virtual Value* operator= (const std::string &value);
        
        virtual ~Value() { };

    };
    
    
    typedef std::vector<Value*> ValueVector;
    typedef std::map<std::string, Value*> ValueMap;
    

    class VectorValue : public Value
    {
    public:
        VectorValue();
        
        VectorValue(ValueVector* values);
        
        json::Value* &operator[] (const size_t &index);
        
        std::string as_string();
        
        ~VectorValue();
        
        Value* operator= (const std::string &value);
    private:
        ValueVector* vector_;
    };
    

    class ObjectValue : public Value
    {
    public:
        ObjectValue();
        
        ObjectValue(ValueMap* values);
        
        Value* &operator[] (const std::string &key);
        
        Value* operator= (const std::string &value);
        
        std::string as_string();
        
        ~ObjectValue();
    private:
        ValueMap* values_;
    };
    
    
    class IntValue : public Value
    {
    public:
        IntValue(int32_t value);
        
        std::string as_string();
        
        int32_t as_int();
        
        Value* operator= (const int32_t &value);
        
        Value* operator= (const std::string &value);
    private:
        int32_t value_;
    };
    
    
    class StringValue : public Value
    {
    public:
        StringValue(const std::string &value);
        
        std::string as_string();
        
        Value* operator= (const std::string &value);
    private:
        std::string value_;
    };

} // namespace json


#endif	// JSON_VALUES_H

