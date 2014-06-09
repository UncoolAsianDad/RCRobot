/* 
 * File:   RCCar.h
 * Author: Brian Ho
 *
 * Created on June 9, 2014, 12:00 PM
 */

#ifndef RCCAR_H
#define	RCCAR_H


#include <Arduino.h>



const int accelSPEED = 3;
const int accelA = 2;
const int accelB = 4;

// steering pins
const int steerSPEED = 5;
const int steerA = 6;
const int steerB = 7;
const int posA = 10;
const int posB = 12;

const int ping = 9;



#define LEFT   B01
#define RIGHT  B10
#define CENTER B00

#define FORWARD  B10
#define BACKWARD B01

#define THROTTLE_STOP 0
#define THROTTLE_LOW  1
#define THROTTLE_MID  2
#define THROTTLE_HIGH 3
#define THROTTLE_MAX  3


// bit wise register
#define STATE_NOOP     B00000000
#define STATE_MOVE     B00000001
#define STATE_STEER    B00000010

class RCCar {
public:
    RCCar();
    virtual ~RCCar();
    void setup();
    
    void getDistance();
    
    void driveNeutral();
    void driveBreak(int delays = 0);
    void driveForward();
    void driveBackward();
    
    void turnRight(int delays = 0);
    void turnLeft(int delays = 0);
    void turnLock();
    void turnRelease();
    void center();
    
    void throttle(int i);
    
    
    void report();
private:
    long microsecondsToCentimeters(long microseconds);
    //Variables
    long lDuration;
    int a, b;
    int iThrottle;

};

#endif	/* RCCAR_H */

