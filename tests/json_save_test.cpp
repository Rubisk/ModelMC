#include <fstream>
#include <iostream>

#include "json_save_test.h"

#include "src/json/json.h"
#include "src/json/object_value.h"
#include "src/json/vector_value.h"
#include "src/json/simple_values.h"
#include "debug_new.h"
#include "src/json/util.h"


using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(JsonSaveTest);

JsonSaveTest::JsonSaveTest()
{
    
}

JsonSaveTest::~JsonSaveTest()
{
    
}

void JsonSaveTest::setUp()
{
    object_ = new ObjectValue();
    Value* string_ = new StringValue("StringText");
    Value* int_ = new IntValue(15);
    Value* bool_ = new BoolValue(true);
    
    ValueVector* vector_value_ = new ValueVector();
    
    vector_value_->push_back(new IntValue(1));
    vector_value_->push_back(new IntValue(2));
    vector_value_->push_back(new IntValue(3));
    
    Value* vector_ = new VectorValue(vector_value_);
    
    (*object_)["string"] = string_;
    (*object_)["int"] = int_;
    (*object_)["bool"] = bool_;
    (*object_)["vector"] = vector_;
}

void JsonSaveTest::tearDown()
{
    delete object_;
}

void JsonSaveTest::testSaveString()
{
    Value* value = (*object_)["string"];
    CPPUNIT_ASSERT(value->save() == "\"StringText\"");
}

void JsonSaveTest::testSaveInt()
{
    Value* value = (*object_)["int"];
    CPPUNIT_ASSERT(value->save() == "15");
}

void JsonSaveTest::testSaveBoolean()
{
    Value* value = (*object_)["bool"];
    CPPUNIT_ASSERT(value->save() == "true");
    *value = false;
    CPPUNIT_ASSERT(value->save() == "false");
}

void JsonSaveTest::testSaveVector()
{
    Value* value = (*object_)["vector"];
    CPPUNIT_ASSERT(value->save() == "[1,2,3]");
}

void JsonSaveTest::testSaveObject()
{
    
}