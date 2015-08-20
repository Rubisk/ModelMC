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


} // namespace json


#endif	// JSON_VALUES_H

