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
    std::string s = value->as_string();
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
    
}

void JsonLoadTest::testLoadIntVector()
{

}

void JsonLoadTest::testLoadSimpleObject()
{
    
}

// Purpose of this test if to see if it all works, not to find
// individual bugs.
void JsonLoadTest::testLoadComplexObject()
{
    
}
