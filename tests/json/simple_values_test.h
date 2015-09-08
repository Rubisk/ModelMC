/*
 * File:   SimpleValuesTest.h
 * Author: Wouter
 *
 * Created on 8-sep-2015, 19:28:08
 */

#ifndef SIMPLEVALUESTEST_H
#define	SIMPLEVALUESTEST_H

#include <cppunit/extensions/HelperMacros.h>

class SimpleValuesTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(SimpleValuesTest);

  CPPUNIT_TEST(testAs_bool);
  CPPUNIT_TEST(testLoadFromBool);
  CPPUNIT_TEST(testSaveBool);
  CPPUNIT_TEST(testAs_string);
  CPPUNIT_TEST(testLoadFromString);
  CPPUNIT_TEST(testSaveString);
  CPPUNIT_TEST(testAs_int);
  CPPUNIT_TEST(testLoadFromInt);
  CPPUNIT_TEST(testSaveInt);

  CPPUNIT_TEST_SUITE_END();

public:
  SimpleValuesTest();
  virtual ~SimpleValuesTest();
  void setUp();
  void tearDown();

private:
  void testAs_bool();
  void testLoadFromBool();
  void testSaveBool();
  void testAs_string();
  void testLoadFromString();
  void testSaveString();
  void testAs_int();
  void testLoadFromInt();
  void testSaveInt();

};

#endif	/* SIMPLEVALUESTEST_H */

