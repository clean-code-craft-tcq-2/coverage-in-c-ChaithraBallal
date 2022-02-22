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
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 26) == NORMAL);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -6) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 90) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40) == NORMAL);
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -45) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 42) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39) == NORMAL);
}

TEST_CASE("infers the breach and send alerts") 
{
  BatteryCharacter BatteryNature;
  BatteryNature.CoolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER, BatteryNature, 20);
  assert(alert_ControllerID ==1);
  
  BatteryNature.CoolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER, BatteryNature, 20);
  assert(alert_EmailID  ==1);
}
