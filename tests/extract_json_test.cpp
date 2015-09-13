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
  s = json::LoadValue(ss, output);
  Value* value = *output;

  std::string s_keys[] = {"first_key", "third_key", "fourth_key", "final_key"};
  int i_keys[] = {1, 5};
  std::vector<void*> path = {&s_keys[0], &i_keys[0], &s_keys[1], &s_keys[2], &i_keys[1], &s_keys[3]};
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

  std::string invalid_key = "Can't find me, hah!";
  std::vector<void*> path = {&invalid_key};
  Value* value = new ObjectValue();
  s = FindValueForPath(value, path, *output);
  CPPUNIT_ASSERT(!s.IsOk());
  CPPUNIT_ASSERT(s.GetError() == kIOException);
  CPPUNIT_ASSERT(*s.GetErrorMessage() == "Invalid key: " + invalid_key);
  delete value;
}

void ExtractJsonTest::TestLoadIntArray() {
  Status s;
  Value** output;
  int32_t output_array[7];
  const std::string sample =
          "{\"int_array_key\":[1,2,3,4,5,6,7]}";
  std::stringstream ss;
  ss.str(sample);
  s = json::LoadValue(ss, output);
  Value* value = *output;

  s = LoadIntArray(value, "int_array_key", 7, output_array);
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(output_array[6] = 7);
}