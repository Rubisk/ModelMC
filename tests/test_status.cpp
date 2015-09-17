#ifndef STATUSTEST_H
#define	STATUSTEST_H

#include "status.h"
#include "gtest\gtest.h"

namespace {

const std::string error_text = "Found semicolon while parsing, expected comma";

} // anonymouse namespace

TEST(StatusTest, TestError) {
  Status s = Status(kJsonError, error_text);
  EXPECT_FALSE(s.IsOk());
  EXPECT_EQ(s.GetError(), kJsonError);
  EXPECT_EQ(*s.GetErrorMessage(), error_text);

  std::stringstream ss;
  ss << s;
  EXPECT_EQ(ss.str(), "Json Exception: " + error_text);
}

TEST(StatusTest, TestGood) {
  Status s = Status(kGood);
  EXPECT_TRUE(s.IsOk());
  EXPECT_EQ(s.GetError(), kGood);
  EXPECT_EQ(*s.GetErrorMessage(), "");

  std::stringstream ss;
  ss << s;
  EXPECT_EQ(ss.str(), "") << "Failed to print out status";
}

#endif	// STATUSTEST_H
