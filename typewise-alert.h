#pragma once

#define Number_Of_Cooling_Types     3
#define Temp_Limits                 2
#define NUM_ALERT_TYPES             2
#define NUM_BREACHTYPES             3
#define PASSIVE_COOLING_LOWER       0
#define PASSIVE_COOLING_UPPER      35
#define HI_ACTIVE_COOLING_LOWER     0
#define HI_ACTIVE_COOLING_UPPER    45
#define MED_ACTIVE_COOLING_LOWER    0 
#define MED_ACTIVE_COOLING_UPPER   40
#define Lower_ID                    0
#define Higher_ID                   1

extern int alert_ControllerID = 0;
extern int alert_EmailID = 0;

typedef enum 
{
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum 
{
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
extern void printOnConsole(const char* recepient, BreachType breachType);

typedef enum 
{
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct 
{
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
