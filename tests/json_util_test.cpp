#include <sstream>
#include <iostream>

#include "json_util_test.h"

#include "src/json/json.h"
#include "src/json/object_value.h"
#include "src/json/simple_values.h"
#include "debug_new.h"
#include "src/json/util.h"


using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(JsonUtilTest);

JsonUtilTest::JsonUtilTest()
{
    
}

JsonUtilTest::~JsonUtilTest()
{
    
}

void JsonUtilTest::setUp()
{
    
}

void JsonUtilTest::tearDown()
{
    
}

void JsonUtilTest::testFindType()
{
    std::string _obj, _vec, _str, _int;
    _obj = "   {";
    _str = "\n      \"";
    _int = "      5  some_other_chars";
    _vec = "\r\n [";
    std::stringstream ss;
   
    ss.str(_obj);
    CPPUNIT_ASSERT(findType(ss) == OBJECT_VALUE);
    
    ss.str(_vec);
    CPPUNIT_ASSERT(findType(ss) == VECTOR_VALUE);
    
    ss.str(_str);
    CPPUNIT_ASSERT(findType(ss) == STRING_VALUE);
    
    ss.str(_int);
    CPPUNIT_ASSERT(findType(ss) == INT_VALUE);
    
    std::string leftover;
    std::ostringstream os;
    ss>>os.rdbuf();
    leftover=os.str();
    
    CPPUNIT_ASSERT(leftover == _int);
}

void JsonUtilTest::testLoadName()
{
    std::stringstream ss;
    ss.str("  \"abc\",");
    
    CPPUNIT_ASSERT(loadName(ss) == "abc");
    std::string leftover_string;
    ss >> leftover_string;
    CPPUNIT_ASSERT(leftover_string == ",");
}

