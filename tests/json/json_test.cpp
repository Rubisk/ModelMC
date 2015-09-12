#include "json_test.h"
#include "json/json.h"

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
  Status s = value->GetBoolValue(&output);
  CPPUNIT_ASSERT(!s.IsOk());
  delete value;
}

void JsonTest::testAs_int() {
  int32_t output;
  Value* value = new TestValue();
  Status s = value->GetIntValue(&output);
  CPPUNIT_ASSERT(!s.IsOk());
  delete value;
}

void JsonTest::testAs_string() {
  std::string output;
  Value* value = new TestValue();
  Status s = value->GetStringValue(&output);
  CPPUNIT_ASSERT(!s.IsOk());
  delete value;
}

void JsonTest::testGet() {
  Value** output;
  Value* value = new TestValue();
  Status s = value->GetChild(1, output);
  CPPUNIT_ASSERT(!s.IsOk());
  s = value->GetChild("some_key", output);
  CPPUNIT_ASSERT(!s.IsOk());
  delete value;
}

void JsonTest::testSaveFromFile() {
  Value* value;
  Status s = LoadFromFile("./tests/testfiles/test_json.json", value);
  CPPUNIT_ASSERT(s.IsOk());

  SaveToFile("./tests/testfiles/test_output.json", value);

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
  Status s = LoadFromFile("./tests/testfiles/test_json.json", output);
  CPPUNIT_ASSERT(s.IsOk());
  delete output;
}

