#ifndef SIMPLE_VALUES_H
#define	SIMPLE_VALUES_H

namespace json {
    
    
class IntValue : public Value
{
public:
    IntValue() { };
    
    IntValue(const int32_t &value);

    std::string save();

    int32_t as_int();

    Value& operator= (const int32_t &value);

    Value& operator= (const std::string &value);
    
    void loadFrom(std::istream &stream);
private:
    int32_t value_;
};


class StringValue : public Value
{
public:
    StringValue() { };
    
    StringValue(const std::string &value);

    std::string as_string();
    
    std::string save();

    Value& operator= (const std::string &value);
    
    void loadFrom(std::istream &stream);
private:
    std::string value_;
};


class BoolValue : public Value
{
public:
    BoolValue() { };
    
    BoolValue(const bool &value);
    
    bool as_bool();
    
    std::string save();
    
    Value& operator= (const std::string &value);
    
    Value& operator= (const int &value);
    
    void loadFrom(std::istream &stream);
private:
    bool value_;
};


} // namespace json

#endif	// SIMPLE_VALUES_H

