#include <Arduino.h>

#include "RCCar.h"
extern HardwareSerial Serial;

RCCar car;
// Constants

void setup() {
    Serial.begin(9600);

}

void loop() {
    
    car.throttle(THROTTLE_LOW);
    car.driveForward();
    
    car.turnLeft(1000);
    car.center();
    
    car.turnRight(1000);
    car.center();
    
    car.throttle(THROTTLE_STOP);
    
    delay(5000);
}
