#ifndef JSON_OBJECT_TEST_H
#define	JSON_OBJECT_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "src/json/json.h"
#include "src/json/object_value.h"


class JsonObjectTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(JsonObjectTest);

    CPPUNIT_TEST(testFromString);
    CPPUNIT_TEST(testToString);
    
    CPPUNIT_TEST(testAccessAnExistingMember);
    CPPUNIT_TEST(testAddAMember);

    CPPUNIT_TEST_SUITE_END();

public:
    JsonObjectTest();
    virtual ~JsonObjectTest();
    void setUp();
    void tearDown();

private:
    void testAccessAnExistingMember();
    void testAddAMember();
    
    json::ObjectValue* object_;
};


#endif	// JSON_OBJECT_TEST_H

