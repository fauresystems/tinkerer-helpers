#include <Bridge.h>
#include <Props.h>

/*
  inbox topic: Room/My room/inbox
  outbox topic: Room/My room/outbox
*/

void actuator(String); // forward

Props("Demo Props", "192.168.0.10", "Room/My room");
Props.setMonitoredDataTick(3000);
Props.setCallback(actuator);

// GPIO
byte pinDoor = 4;

// Challenge
bool aligned(false);
bool door(true);
bool challenge_done(false);

Props.addMonitoredData(aligned); // default is "1", "0"
Props.addMonitoredData(door, "closed", "opened");
Props.addMonitoredData(challenge_done, "yes", "no");

void setup()
{
  Bridge.begin();
  Props.begin();

  pinMode(pinDoor, OUTPUT);
  digitalWrite(pinDoor, HIGH);

  // Publish data
  Props.publishAll();
}

void loop()
{
  // Process GPIO logic
  ...

  // Process challenge logic

  Props.check();
}

void actuator(String a)
{
  if (a == u8"game:begin")
  {
    aligned = false;
    door = false;
    challenge_done = false;
    Props.done(a);
  }
  else if (a == "door:close")
  {
    digitalWrite(pinDoor, HIGH);
    door = true;
    Props.done(a);
  }
  else if (a == "door:open")
  {
    digitalWrite(pinDoor, LOW);
    door = false;
    Props.done(a);
  }
  else if (a == "challenge:1")
  {
    challenge_done = true;
    Props.done(a);
  }
  else if (a == "challenge:0")
  {
    challenge_done = false;
    Props.done(a);
  }
  else
  {
    Props.omit(a);
  }
}

