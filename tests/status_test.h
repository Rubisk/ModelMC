#ifndef STATUSTEST_H
#define	STATUSTEST_H

#include "status.h"
#include <cppunit/extensions/HelperMacros.h>

class StatusTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(StatusTest);

  CPPUNIT_TEST(testError);
  CPPUNIT_TEST(testGood);

  CPPUNIT_TEST_SUITE_END();

public:
  StatusTest();
  virtual ~StatusTest();
  void setUp();
  void tearDown();

private:
  void testError();
  void testGood();
  Status ReturnJsonException_();
  Status ReturnGoodStatus_();

};

#endif	// STATUSTEST_H

