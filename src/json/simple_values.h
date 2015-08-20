#ifndef SIMPLE_VALUES_H
#define	SIMPLE_VALUES_H

namespace json {
    
    
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

#endif	// SIMPLE_VALUES_H

