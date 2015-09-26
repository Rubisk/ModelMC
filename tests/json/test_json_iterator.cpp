#include <gtest/gtest.h>

#include "json/value.h"
#include "json/iterator.h"

using namespace json;

TEST(JsonIteratorTest, Array) {
  Value array_value(kArrayValue);

  array_value.Append(5);
  array_value.Append(5.25);
  array_value.Append("some_string");
  array_value.Append(false);

  Value::Iterator it = array_value.GetIterator();
  size_t position = 0;
  while (it.Valid()) {
    Value &current = it.Get();
    switch (position) {
    case 0:
      EXPECT_EQ(current, 5);
      break;
    case 1:
      EXPECT_EQ(current, 5.25);
      break;
    case 2:
      EXPECT_EQ(current, "some_string");
      current = 105;
      break;
    case 3:
      EXPECT_EQ(current, false);
      current = true;
      break;
    }
    it.Next();
    ++position;
  }
  EXPECT_EQ(position, 4);
  EXPECT_EQ(array_value[2], 105);
  EXPECT_EQ(array_value[3], true);
}

TEST(JsonIteratorTest, Object) {
  Value object_value(kObjectValue);

  object_value.Add("1", 5);
  object_value.Add("2", 5.25);
  object_value.Add("3", "some_string");
  object_value.Add("4", false);

  Value::Iterator it = object_value.GetIterator();
  while (it.Valid()) {
    Value &current = it.Get();
    // Converting string to char allows for using switch.
    char key = *it.GetKey().c_str();
    switch (key) {
    case '1':
      EXPECT_EQ(current, 5);
      break;
    case '2':
      EXPECT_EQ(current, 5.25);
      break;
    case '3':
      EXPECT_EQ(current, "some_string");
      current = 105;
      break;
    case '4':
      EXPECT_EQ(current, false);
      current = true;
      break;
    }
    it.Next();
  }
  EXPECT_EQ(object_value["3"], 105);
  EXPECT_EQ(object_value["4"], true);
}