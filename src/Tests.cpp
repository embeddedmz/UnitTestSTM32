extern "C"
{
// include C header files here
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FirstTestGroup)
{
  void setup()
  {

  }
  void teardown()
  {

  }
};

TEST(FirstTestGroup, FirstTest)
{
  //FAIL("Fail me!");
   CHECK_TRUE(true);
}

TEST(FirstTestGroup, SecondTest)
{
   STRCMP_NOCASE_EQUAL("hello", "HELLO");
}


