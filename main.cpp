#include <Arduino.h>

#include "RCCar.h"
extern HardwareSerial Serial;

RCCar car;
// Constants

void setup() {
    Serial.begin(9600);
    
    car.setup();
}

void loop() {
    
    car.throttle(THROTTLE_MID);
    car.driveForward();
    
    car.turnLeft(1000);
    car.center();
    
    car.turnRight(1000);
    car.center();
    
    car.throttle(THROTTLE_STOP);
    car.driveBreak(1000);
    car.driveNeutral();
    
    
    delay(5000);
}
