#include "json_simple_values_test.h"
#include "src/json/json.h"
#include "src/json/simple_values.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(JsonValueTest);

JsonValueTest::JsonValueTest()
{
    
}

JsonValueTest::~JsonValueTest()
{
    
}

void JsonValueTest::setUp()
{
    
}

void JsonValueTest::tearDown()
{
    
}

void JsonValueTest::testIntValue()
{
    Value* value = new IntValue(5);
    CPPUNIT_ASSERT(value->as_int() == 5);
    CPPUNIT_ASSERT(value->as_string() == "5");
    *value = 6;
    
    CPPUNIT_ASSERT(value->as_int() == 6);
    CPPUNIT_ASSERT(value->as_string() == "6");
    
    *value = "-1";
    
    CPPUNIT_ASSERT(value->as_int() == -1);
    CPPUNIT_ASSERT(value->as_string() == "-1");
    
    delete value;
}

void JsonValueTest::testStringValue() {
    Value* value = new StringValue("A");
    CPPUNIT_ASSERT(value->as_string() == "A");
    *value = "B";
    
    CPPUNIT_ASSERT(value->as_string() == "B");
    
    delete value;
}

void JsonValueTest::testBoolValue()
{
    Value* value = new BoolValue(false);
    CPPUNIT_ASSERT(value->as_bool() == false);
    CPPUNIT_ASSERT(value->as_string() == "false");
    *value = true;
    
    CPPUNIT_ASSERT(value->as_bool() == true);
    CPPUNIT_ASSERT(value->as_string() == "true");
    
    *value = "false";
    
    CPPUNIT_ASSERT(value->as_bool() == false);
    CPPUNIT_ASSERT(value->as_string() == "false");
    
    delete value;
}


