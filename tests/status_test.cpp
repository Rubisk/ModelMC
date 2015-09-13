#include "status_test.h"
#include "status.h"

std::string kJsonErrorText = "Found semicolon while parsing, expected comma";

CPPUNIT_TEST_SUITE_REGISTRATION(StatusTest);

StatusTest::StatusTest() { }

StatusTest::~StatusTest() { }

void StatusTest::setUp() { }

void StatusTest::tearDown() { }

void StatusTest::testError() {
  Status s = ReturnJsonException_();
  CPPUNIT_ASSERT(!s.IsOk());
  CPPUNIT_ASSERT(s.GetError() == kJsonError);
  CPPUNIT_ASSERT(*s.GetErrorMessage() == kJsonErrorText);

  std::stringstream ss;
  ss << s;
  CPPUNIT_ASSERT(ss.str() == "Json Exception: " + kJsonErrorText);
}

void StatusTest::testGood() {
  Status s = ReturnGoodStatus_();
  CPPUNIT_ASSERT(s.IsOk());
  CPPUNIT_ASSERT(s.GetError() == kOk);
  CPPUNIT_ASSERT(*s.GetErrorMessage() == "");

  std::stringstream ss;
  ss << s;
  CPPUNIT_ASSERT(ss.str() == "");
}

Status StatusTest::ReturnGoodStatus_() {
  return Status(kOk);
}

Status StatusTest::ReturnJsonException_() {
  return Status(kJsonError, kJsonErrorText);
}

