#include "typewise-alert.h"
#include <stdio.h>

int classifyTemperatureLimits[Number_Of_Cooling_Types][Temp_Limits] = {{PASSIVE_COOLING_LOWER,PASSIVE_COOLING_UPPER},
                                                                       {HI_ACTIVE_COOLING_LOWER,HI_ACTIVE_COOLING_UPPER},
                                                                       {MED_ACTIVE_COOLING_LOWER,MED_ACTIVE_COOLING_UPPER}};
void (*alertTargetTypesfp[NUM_ALERT_TYPES])(breachType) = {sendToController, sendToEmail};
char alertMsgEmail[NUM_BREACHTYPES][100] = {{"Hi, the temperature is too low\n"},
                                       {"Hi, the temperature is too high\n"},
                                       {"Hi, the temperature is Normal\n"} };

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) 
  {
    return TOO_LOW;
  }
  if(value > upperLimit) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  int lowerLimit = classifyTemperatureLimits[coolingType][Lower_ID];
  int upperLimit = classifyTemperatureLimits[coolingType][Higher_ID];  
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}


void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  printOnConsole(recepient, breachType);
}

void printOnConsole(const char* recepient, BreachType breachType)
{
  printf("To: %s\n", recepient);
  printf("%s", alertMsgEmail[breachType]);
}

/*Main code under test*/
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  alertTargetTypesfp[alertTarget](breachType);
}


