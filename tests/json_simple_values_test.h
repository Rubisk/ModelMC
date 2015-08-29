#ifndef JSON_VALUES_TEST_H
#define	JSON_VALUES_TEST_H

#include <cppunit/extensions/HelperMacros.h>


class JsonValueTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(JsonValueTest);

    CPPUNIT_TEST(testIntValue);
    CPPUNIT_TEST(testStringValue);
    CPPUNIT_TEST(testBoolValue);

    CPPUNIT_TEST_SUITE_END();

public:
    JsonValueTest();
    virtual ~JsonValueTest();
    void setUp();
    void tearDown();

private:
    void testIntValue();
    void testStringValue();
    void testBoolValue();
};

#endif	// JSON_VALUES_TEST_H

