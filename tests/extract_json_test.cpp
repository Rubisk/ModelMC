#include "extract_json_test.h"
#include "extract_json.h"
#include "json/object_value.h"
#include "json/vector_value.h"
#include "json/simple_values.h"
#include "json/util.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(ExtractJsonTest);

ExtractJsonTest::ExtractJsonTest() { }

ExtractJsonTest::~ExtractJsonTest() { }

void ExtractJsonTest::setUp() { }

void ExtractJsonTest::tearDown() { }

void ExtractJsonTest::TestFindValueForPath() {
  Status s;
  Value** output;

  const std::string sample =
          "{\"first_key\":[0,{\"third_key\":{\"fourth_key\":"
          "[0,1,2,3,4,{\"final_key\":\"Find me please!\"}]}}]}";
  std::stringstream ss;
  ss.str(sample);
  Value* value;
  s = json::LoadValue(ss, value);

  StringVector path = {"first_key", "1", "third_key",
    "fourth_key", "5", "final_key"};
  s = FindValueForPath(value, path, *output);
  CPPUNIT_ASSERT(s.IsOk());
  std::string string_output;
  s = (*output)->GetStringValue(&string_output);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(string_output == "Find me please!");
  delete value;
}

void ExtractJsonTest::TestFindValueForInvalidPath() {
  Status s;
  Value** output;

  std::string cant_find = "Can't find me, hah!";
  StringVector path = {cant_find};
  Value* value = new ObjectValue();
  s = FindValueForPath(value, path, *output);
  CPPUNIT_ASSERT(!s.IsOk());
  CPPUNIT_ASSERT(s.GetError() == kIOException);
  CPPUNIT_ASSERT(*s.GetErrorMessage() == "Invalid key: " + cant_find);
  delete value;
}

void ExtractJsonTest::TestLoadIntArray() {
  Status s;
  int32_t output_array[7];
  const std::string sample =
          "{\"int_array_key\":[1,2,3,4,5,6,7]}";
  std::stringstream ss;
  ss.str(sample);
  Value* value;
  s = json::LoadValue(ss, value);

  s = LoadIntArray(value, "int_array_key", 7, output_array);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output_array[6] = 7);
  delete value;
}

void ExtractJsonTest::TestLoadStringValue() {
  Status s;
  std::string output_string;
  const std::string sample =
          "{\"int_array_key\":[\"load_me\"]}";
  std::stringstream ss;
  ss.str(sample);
  Value* value;
  s = json::LoadValue(ss, value);

  StringVector v = {"int_array_key", "0"};
  s = LoadStringValue(value, v, output_string);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output_string == "load_me");
  delete value;
}