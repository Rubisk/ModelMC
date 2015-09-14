#include "simple_values_test.h"

using namespace json;

CPPUNIT_TEST_SUITE_REGISTRATION(SimpleValuesTest);

SimpleValuesTest::SimpleValuesTest() { }

SimpleValuesTest::~SimpleValuesTest() { }

void SimpleValuesTest::setUp() {
  int_ = new IntValue(-1);
  string_ = new StringValue("standard_value");
  bool_ = new BoolValue(true);
  string_stream_.clear();
}

void SimpleValuesTest::tearDown() {
  delete int_;
  delete string_;
  delete bool_;
}

void SimpleValuesTest::AssertRemainder_(std::string remainder) {
  std::stringstream os;
  string_stream_ >> os.rdbuf();
  CPPUNIT_ASSERT(os.str() == remainder);
}

void SimpleValuesTest::TestGetBool() {
  bool output;
  CPPUNIT_ASSERT(bool_->GetValueType() == kBoolValue);
  s_ = bool_->GetBoolValue(&output);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(output = true);
}

void SimpleValuesTest::TestLoadFromStreamBool() {
  string_stream_.str("true||}}|}|<><><><");
  s_ = bool_->LoadFromStream(string_stream_);
  CPPUNIT_ASSERT(s_.IsOk());
  AssertRemainder_("||}}|}|<><><><");
  bool output;
  s_ = bool_->GetBoolValue(&output);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(output);
}

void SimpleValuesTest::TestSaveToStreamBool() {
  std::stringstream output;
  *bool_ = false;
  bool_->SaveToStream(&output);
  *bool_ = true;
  bool_->SaveToStream(&output);
  CPPUNIT_ASSERT(output.str() == "falsetrue");
}

void SimpleValuesTest::TestGetString() {
  std::string output;
  CPPUNIT_ASSERT(string_->GetValueType() == kStringValue);
  s_ = string_->GetStringValue(&output);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(output == "standard_value");
}

void SimpleValuesTest::TestLoadFromStreamString() {
  string_stream_.str("\"some_string\"||}}|}|<><><><");
  s_ = string_->LoadFromStream(string_stream_);
  CPPUNIT_ASSERT(s_.IsOk());
  AssertRemainder_("||}}|}|<><><><");

  std::string output;
  s_ = string_->GetStringValue(&output);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(output == "some_string");
}

void SimpleValuesTest::TestSaveToStreamString() {
  std::stringstream output;
  string_->SaveToStream(&output);
  CPPUNIT_ASSERT(output.str() == "\"standard_value\"");
}

void SimpleValuesTest::TestGetInt() {
  int32_t output;
  CPPUNIT_ASSERT(int_->GetValueType() == kIntValue);
  s_ = int_->GetIntValue(&output);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(output == -1);
}

void SimpleValuesTest::TestLoadFromStreamInt() {
  string_stream_.str("-52||}}|}|<><><><");
  s_ = int_->LoadFromStream(string_stream_);
  CPPUNIT_ASSERT(s_.IsOk());
  AssertRemainder_("||}}|}|<><><><");

  int32_t output;
  s_ = int_->GetIntValue(&output);
  CPPUNIT_ASSERT(s_.IsOk());
  CPPUNIT_ASSERT(output == -52);
}

void SimpleValuesTest::TestSaveToStreamInt() {
  std::stringstream output;
  int_->SaveToStream(&output);
  CPPUNIT_ASSERT(output.str() == "-1");
}

