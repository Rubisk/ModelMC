#include <sstream>

#include "simple_values_test.h"
#include "src/json/simple_values.h"
#include "src/json/json.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(SimpleValuesTest);

SimpleValuesTest::SimpleValuesTest() {
}

SimpleValuesTest::~SimpleValuesTest() {
}

void SimpleValuesTest::setUp() {
}

void SimpleValuesTest::tearDown() {
}

void SimpleValuesTest::testAs_bool() {
  bool output;
  Value* value = new BoolValue(true);
  Status s = value->as_bool(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output = true);
  delete value;
}

void SimpleValuesTest::testLoadFromBool() {
  std::stringstream ss;
  ss.str("true||}}|}|<><><><");
  Value* value = new BoolValue();
  Status s = value->loadFrom(ss);
  CPPUNIT_ASSERT(s == kOk);
  
  std::stringstream os;
  ss >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == "||}}|}|<><><><");
  
  bool output;
  s = value->as_bool(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output);

  delete value;
}

void SimpleValuesTest::testSaveBool() {
  std::stringstream output;
  Value* value = new BoolValue(false);
  value->save(&output);
  CPPUNIT_ASSERT(output.str() == "false");
  *value = true;
  value->save(&output);
  CPPUNIT_ASSERT(output.str() == "falsetrue");
  delete value;
}

void SimpleValuesTest::testAs_string() {
  std::string output;
  Value* value = new StringValue("some_string");
  Status s = value->as_string(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == "some_string");
  delete value;
}

void SimpleValuesTest::testLoadFromString() {
  std::stringstream ss;
  ss.str("\"some_string\"||}}|}|<><><><");
  Value* value = new StringValue();
  Status s = value->loadFrom(ss);
  CPPUNIT_ASSERT(s == kOk);
  
  std::stringstream os;
  ss >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == "||}}|}|<><><><");
  
  std::string output;
  s = value->as_string(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == "some_string");

  delete value;
}

void SimpleValuesTest::testSaveString() {
  std::stringstream output;
  Value* value = new StringValue("some_string");
  value->save(&output);
  CPPUNIT_ASSERT(output.str() == "\"some_string\"");
  delete value;
}

void SimpleValuesTest::testAs_int() {
  int32_t output;
  Value* value = new IntValue(5);
  Status s = value->as_int(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == 5);
  delete value;
}

void SimpleValuesTest::testLoadFromInt() {
  std::stringstream ss;
  ss.str("52||}}|}|<><><><");
  Value* value = new IntValue();
  Status s = value->loadFrom(ss);
  CPPUNIT_ASSERT(s == kOk);
  
  std::stringstream os;
  ss >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == "||}}|}|<><><><");
  
  int32_t output;
  s = value->as_int(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == 52);

  delete value;
}

void SimpleValuesTest::testSaveInt() {
  std::stringstream output;
  Value* value = new IntValue(55555);
  value->save(&output);
  CPPUNIT_ASSERT(output.str() == "55555");
  delete value;
}

