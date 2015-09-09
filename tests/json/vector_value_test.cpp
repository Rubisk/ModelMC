#include "vector_value_test.h"
#include "src/json/simple_values.h"
#include "src/json/vector_value.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(VectorValueTest);

VectorValueTest::VectorValueTest() {
}

VectorValueTest::~VectorValueTest() {
}

void VectorValueTest::setUp() {
}

void VectorValueTest::tearDown() {
}

void VectorValueTest::testGet() {
  Value** valueptr;
  Value* value = new VectorValue();
  Status s = value->get(5, valueptr);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(*valueptr == NULL);

  *valueptr = new IntValue(10);

  Value** new_value_pointer;
  s = value->get(5, new_value_pointer);
  CPPUNIT_ASSERT(s == kOk);
  int32_t output;
  s = (*new_value_pointer)->as_int(&output);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(output == 10);
  delete value;
}

void VectorValueTest::testLoadFrom() {
  std::stringstream ss;
  ss.str("[5,8]");
  Value* value = new VectorValue();
  Status s = value->loadFrom(ss);
  CPPUNIT_ASSERT(s == kOk);

  std::stringstream os;
  ss >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == "");

  Value** output;

  int int_value;
  s = value->get(0, output);
  CPPUNIT_ASSERT(s == kOk);
  s = (*output)->as_int(&int_value);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(int_value == 5);
  s = value->get(1, output);
  CPPUNIT_ASSERT(s == kOk);
  s = (*output)->as_int(&int_value);
  CPPUNIT_ASSERT(s == kOk);
  CPPUNIT_ASSERT(int_value == 8);
  delete value;
}

void VectorValueTest::testSave() {
  const std::string test_str = "[5,\"string\"]";
  std::stringstream input_stream;
  input_stream.str(test_str);
  Value* value = new VectorValue();
  Status s = value->loadFrom(input_stream);
  CPPUNIT_ASSERT(s == kOk);

  std::stringstream output_stream;
  value->save(&output_stream);
  CPPUNIT_ASSERT(output_stream.str() == test_str);
  delete value;
}

