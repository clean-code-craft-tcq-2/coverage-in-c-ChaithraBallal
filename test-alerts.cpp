#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") 
{
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(45, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(26, 20, 30) == NORMAL);
}

TEST_CASE("infers the breach according to cooling types") 
{
  
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -4) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 89) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 26) == NORMAL);
}
