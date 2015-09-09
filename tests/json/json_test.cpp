#include "json_test.h"
#include "src/json/json.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(JsonTest);

JsonTest::JsonTest() {
}

JsonTest::~JsonTest() {
}

void JsonTest::setUp() {
}

void JsonTest::tearDown() {
}

void JsonTest::testAs_bool() {
  bool output;
  Value* value = new TestValue();
  Status s = value->as_bool(&output);
  CPPUNIT_ASSERT(s == kValueError);
}

void JsonTest::testAs_int() {
  int32_t output;
  Value* value = new TestValue();
  Status s = value->as_int(&output);
  CPPUNIT_ASSERT(s == kValueError);
}

void JsonTest::testAs_string() {
  std::string output;
  Value* value = new TestValue();
  Status s = value->as_string(&output);
  CPPUNIT_ASSERT(s == kValueError);
}

void JsonTest::testGet() {
  Value** output;
  Value* value = new TestValue();
  Status s = value->get(1, output);
  CPPUNIT_ASSERT(s == kValueError);
  s = value->get("some_key", output);
  CPPUNIT_ASSERT(s == kValueError);
}

void JsonTest::testSaveFromFile() {
  Value* value;
  Status s = load("./tests/testfiles/test_json.json", value);
  CPPUNIT_ASSERT(s == kOk);

  save("./tests/testfiles/test_output.json", value);

  std::ifstream original, copy;

  original.open("./tests/testfiles/test_json_without_whitespace");
  copy.open("./tests/testfiles/test_output.json");

  CPPUNIT_ASSERT(std::equal(std::istreambuf_iterator<char>(original),
          std::istreambuf_iterator<char>(),
          std::istreambuf_iterator<char>(copy)));

  original.close();
  copy.close();

  delete value;
}

void JsonTest::testLoadFromFile() {
  Value* output;
  Status s = load("./tests/testfiles/test_json.json", output);
  CPPUNIT_ASSERT(s == kOk);
  delete output;
}

