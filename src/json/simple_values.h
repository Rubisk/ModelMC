#ifndef SIMPLE_VALUES_H
#define	SIMPLE_VALUES_H

namespace json {
    
class IntValue : public Value
{
public:
    IntValue() { };
    
    IntValue(const int32_t &value);

    Status save(std::ostream* output);

    Status as_int(int32_t* output);

    Status operator= (const int32_t &value);
    
    Status loadFrom(std::istream &stream);
private:
    int32_t value_;
};


class StringValue : public Value
{
public:
    StringValue() { };
    
    StringValue(const std::string &value);

    Status as_string(std::string* output);
    
    Status save(std::ostream* output);

    Status operator= (const std::string &value);
    
    Status loadFrom(std::istream &stream);
private:
    std::string value_;
};


class BoolValue : public Value
{
public:
    BoolValue() { };
    
    BoolValue(const bool &value);
    
    Status as_bool(bool* output);
    
    Status save(std::ostream* output);
    
    Status operator= (const bool &value);
    
    Status loadFrom(std::istream &stream);
private:
    bool value_;
};

} // namespace json

#endif	// SIMPLE_VALUES_H

