/* 
 * File:   RCCar.cpp
 * Author: Brian Ho
 * 
 * Created on June 9, 2014, 12:00 PM
 */

#include "RCCar.h"

RCCar::RCCar() {
    
    iThrottle = 0;

    // setup servo read back pins
    pinMode(posA, INPUT);
    pinMode(posB, INPUT);

    // setup driving control pins
    pinMode(accelSPEED, OUTPUT);
    pinMode(accelA, OUTPUT);
    pinMode(accelB, OUTPUT);

    // setup steering control pins
    pinMode(steerSPEED, OUTPUT); // optional, we probably don't even need to hook this part up
    pinMode(steerA, OUTPUT);
    pinMode(steerB, OUTPUT);


}

RCCar::~RCCar() {
}

void RCCar::getDistance() {
    pinMode(ping, OUTPUT);
    digitalWrite(ping, LOW);
    delayMicroseconds(2);
    digitalWrite(ping, HIGH);
    delayMicroseconds(5);
    digitalWrite(ping, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose lDuration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(ping, INPUT);
    lDuration = pulseIn(ping, HIGH);

}

// in neutral
void RCCar::driveNeutral() {
    digitalWrite(accelA, HIGH);
    digitalWrite(accelB, HIGH);
}

// lock the wheels
void RCCar::driveBreak() {
    digitalWrite(accelA, LOW);
    digitalWrite(accelB, LOW);
}

void RCCar::driveForward() {
    digitalWrite(accelA, FORWARD >> 1);
    digitalWrite(accelB, FORWARD & 1);
}

void RCCar::driveBackward() {
    digitalWrite(accelA, BACKWARD >> 1);
    digitalWrite(accelB, BACKWARD & 1);
}

void RCCar::turnLock() {
    digitalWrite(steerA, LOW);
    digitalWrite(steerB, LOW);
}

void RCCar::turnRelease() {
    digitalWrite(steerA, HIGH);
    digitalWrite(steerB, HIGH);

}

void RCCar::turnRight(int delays) {
    digitalWrite(steerA, RIGHT >> 1);
    digitalWrite(steerB, RIGHT & 1);

    delay(delays);
}

void RCCar::turnLeft(int delays) {
    digitalWrite(steerA, LEFT >> 1);
    digitalWrite(steerB, LEFT & 1);

    delay(delays);
}

void RCCar::center() {
    a = digitalRead(posA);
    b = digitalRead(posB);

    while (1) {

        if (a != b) {
            if (b)
                turnRight();
            else
                turnLeft();
        }

        if (a == b) {
            // just right!! Stop (ちょうどいいです、止る！）
            turnRelease();
            break;
        }
        report();
    }
}

long RCCar::microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}

void RCCar::report() {

    a = digitalRead(posA);
    b = digitalRead(posB);

    Serial.print("a: ");
    Serial.print(a);
    Serial.print(" b: ");
    Serial.print(b);
    Serial.print(" d: ");
    Serial.print(microsecondsToCentimeters(lDuration));
    Serial.print(" t: ");
    Serial.print(iThrottle);
    Serial.println();
}

void RCCar::throttle(int i) {
    analogWrite(accelSPEED, map(i, 0, THROTTLE_MAX, 0, 255));
}
