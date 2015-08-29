#include <fstream>
#include <iostream>

#include "json_load_test.h"

#include "src/json/json.h"
#include "src/json/object_value.h"
#include "src/json/simple_values.h"
#include "debug_new.h"
#include "src/json/util.h"


using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(JsonLoadTest);

JsonLoadTest::JsonLoadTest()
{
    
}

JsonLoadTest::~JsonLoadTest()
{
    
}

void JsonLoadTest::setUp()
{
    
}

void JsonLoadTest::tearDown()
{
    
}

void JsonLoadTest::testLoadString()
{
    std::stringstream ss;
    ss.str("\"this is a string\"    ,]{]}}'");
    Value* value = loadValue(ss);
    CPPUNIT_ASSERT(value->as_string() == "this is a string");
    
    std::string leftover;
    std::ostringstream os;
    ss >> os.rdbuf();
    leftover = os.str();
    
    CPPUNIT_ASSERT(leftover == "    ,]{]}}'");
    delete value;
}

void JsonLoadTest::testLoadInt()
{
    std::stringstream ss;
    ss.str("5\"\n");
    Value* value = loadValue(ss);
    CPPUNIT_ASSERT(value->as_string() == "5");
    CPPUNIT_ASSERT(value->as_int() == 5);
    
    std::string leftover;
    std::ostringstream os;
    ss >> os.rdbuf();
    leftover = os.str();
    
    CPPUNIT_ASSERT(leftover == "\"\n");
    delete value;
  
}

void JsonLoadTest::testInvalidValue()
{   
    std::stringstream ss;
    ss.str("some_other_string");
    CPPUNIT_ASSERT_THROW(loadValue(ss), json_exception);
}

void JsonLoadTest::testLoadBool()
{
    std::stringstream ss;
    
    ss.str("false");
    Value* value = loadValue(ss);
    CPPUNIT_ASSERT(value->as_string() == "false");
    CPPUNIT_ASSERT(!value->as_bool());
    
    delete value;
    
    ss.str("true123123");
    value = loadValue(ss);
    CPPUNIT_ASSERT(value->as_bool());
    CPPUNIT_ASSERT(value->as_string() == "true");
    
    std::string leftover;
    std::ostringstream os;
    ss >> os.rdbuf();
    leftover = os.str();
    CPPUNIT_ASSERT(leftover == "123123");
    
    delete value;

}

void JsonLoadTest::testLoadIntVector()
{
    std::stringstream ss;
    ss.str("[5, 7, 9, 12, 15, 4, 2]{[[asdfa]");
    Value* value = loadValue(ss);
    CPPUNIT_ASSERT((*value)[0]->as_int() == 5);
    CPPUNIT_ASSERT((*value)[6]->as_int() == 2);
    
    std::string leftover;
    std::ostringstream os;
    ss >> os.rdbuf();
    leftover = os.str();
    
    CPPUNIT_ASSERT(leftover == "{[[asdfa]");
    delete value;
}

void JsonLoadTest::testLoadSimpleObject()
{
    std::stringstream ss;
    ss.str("{\"some_string\": 35, \"some_other_string\": \"abcd\"}[][][");
    Value* value = loadValue(ss);
    CPPUNIT_ASSERT((*value)["some_string"]->as_int() == 35);
    CPPUNIT_ASSERT((*value)["some_other_string"]->as_string() == "abcd");
    
    std::string leftover;
    std::ostringstream os;
    ss >> os.rdbuf();
    leftover = os.str();
    
    CPPUNIT_ASSERT(leftover == "[][][");
    delete value;
}

void JsonLoadTest::testFileObject()
{
    std::ifstream file;
    file.open("./tests/testfiles/test_file_object.json", std::ios::binary);
    Value* value = loadValue(file);
    file.close();
    CPPUNIT_ASSERT((*value)["some_string"]->as_string() == "some_value");
    delete value;
}

// Purpose of this test if to see if it all works, not to find
// individual bugs.
void JsonLoadTest::testLoadComplexObject()
{
    std::ifstream file;
    file.open("./tests/testfiles/test_json.json", std::ios::binary);
    Value* value = loadValue(file);
    file.close();
    delete value;
}
