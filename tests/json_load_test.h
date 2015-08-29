#ifndef JSON_LOAD_TEST_H
#define	JSON_LOAD_TEST_H

#include <cppunit/extensions/HelperMacros.h>


class JsonLoadTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(JsonLoadTest);

    CPPUNIT_TEST(testLoadString);
    CPPUNIT_TEST(testLoadBool);
    CPPUNIT_TEST(testLoadInt);
    CPPUNIT_TEST(testLoadIntVector);
    CPPUNIT_TEST(testLoadSimpleObject);
    CPPUNIT_TEST(testFileObject);
    CPPUNIT_TEST(testLoadComplexObject);

    CPPUNIT_TEST_SUITE_END();

public:
    JsonLoadTest();
    virtual ~JsonLoadTest();
    void setUp();
    void tearDown();

private:
    void testLoadString();
    void testLoadBool();
    void testLoadInt();
    void testLoadIntVector();
    void testLoadSimpleObject();
    void testFileObject();
    void testLoadComplexObject();
};


#endif	// JSON_LOAD_TEST_H

