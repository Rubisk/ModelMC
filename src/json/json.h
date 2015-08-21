#ifndef JSON_H
#define	JSON_H

namespace json {
   
enum Types { OBJECT_VALUE, VECTOR_VALUE, INT_VALUE, STRING_VALUE };


ObjectValue* load(std::iostream &stream);


ObjectValue* load(const std::string &file);


void save(std::iostream &stream, const ObjectValue* value);


void save(const std::string &file, const ObjectValue* value);


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
    virtual size_t getType();
    
    virtual std::string as_string();

    virtual int32_t as_int();

    virtual Value* &operator[] (const std::string &key);

    virtual Value* &operator[] (const size_t &index);

    virtual Value& operator= (const int32_t &value);

    virtual Value& operator= (const std::string &value);

    virtual ~Value() { };

};


}


#endif	// JSON_H

