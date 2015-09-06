#ifndef JSON_UTIL_TEST_H
#define	JSON_UTIL_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class JsonUtilTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(JsonUtilTest);

  CPPUNIT_TEST(testFindType);
  CPPUNIT_TEST(testLoadName);

  CPPUNIT_TEST_SUITE_END();

public:
  JsonUtilTest();
  virtual ~JsonUtilTest();
  void setUp();
  void tearDown();

private:
  void testFindType();
  void testLoadName();
};



#endif	// JSON_UTIL_TEST_H

