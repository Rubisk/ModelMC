#ifndef JSON_H
#define	JSON_H

#include <stdexcept>
#include <iostream>

namespace json {
   
enum Types { OBJECT_VALUE, VECTOR_VALUE, INT_VALUE, STRING_VALUE };


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

    virtual Value& operator= (const int32_t &value);

    virtual Value& operator= (const std::string &value);
    
    virtual void loadFrom(std::istream &stream) = 0;

    virtual ~Value() { };

};

Value* load(std::istream &stream);


Value* load(const std::string &file);


void save(std::ostream &stream, const Value* value);


void save(const std::string &file, const Value* value);


}


#endif	// JSON_H

