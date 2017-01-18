#include <MadgwickAHRS.h>

#include <PID_v1.h>

#include <BMI160.h>
#include <CurieIMU.h>

/*
  BlueCopter - Quadcopter firmware
  
  Created by Basel Al-Rudainy, 6 april 2013.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  Change log:
  V1.02 - Implemented a proper receiver expo for smooth response.
          Commenting the line "#define RX_EXPO" will disable the RX-expo.
  V1.01 - Made the sketch run more efficiently and reduced code size. 
          With this change I managed to find better PID values and thus
          get better/faster stabilization 
  V1.00 - BlueCopter firmware created!
*/

#include "Config.h"
#include <MPULib.h>
#include <Wire.h>
#include <PIDCont.h>
#include <avr/pgmspace.h>
#include <Servo.h>

Madgwick filter;
PIDCont PIDroll,PIDpitch,PIDyaw,PIDangleX,PIDangleY;
MPULib MPU;
Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;
unsigned long microsPerReading, microsPrevious;
unsigned long microsFirst;
float angleX,angleY,angleZ = 0.0;

// RX Signals
int throttle=THROTTLE_RMIN;
volatile int rx_values[4]; // ROLL, PITCH, THROTTLE, YAW

// PID variables
double pid_roll_in,   pid_roll_out,   pid_roll_setpoint = 0;
double pid_pitch_in,  pid_pitch_out,  pid_pitch_setpoint = 0;
double pid_yaw_in,    pid_yaw_out,    pid_yaw_setpoint = 0;
  
// Motors
int m0, m1, m2, m3; // Front, Right, Back, Left

// Track loop time.
unsigned long prev_time = 0;


void setup() {
  Serial.begin(9600);
  while(!Serial);
#ifdef DEBUG  
#endif
  MPU.init();
  Serial.println("mpuinit");
  motorInit();
  Serial.println("motorinit");

  motorArm();
  Serial.println("motorarm");

  pid_initialize();
  Serial.println("pidinit");
  CurieIMU.begin();
  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  filter.begin(25);
  CurieIMU.setAccelerometerRange(2);
  CurieIMU.setGyroRange(250); 
  microsPerReading = 1000000 / 25;
  microsPrevious = micros();
  microsFirst = micros();
  Serial.print("Starting Gyroscope calibration and enabling offset compensation...");
  CurieIMU.autoCalibrateGyroOffset();
  Serial.println(" Done");

  Serial.print("Starting Acceleration calibration and enabling offset compensation...");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
}

void loop() {
  // Serial.println("in main loop");
  if(micros() - microsFirst < 10000000) {
    motor0.write(0);
    motor1.write(0);
    motor2.write(0);
    motor3.write(0);
  } else {
    imu_update();
    FlightControl();
  }
  prev_time = micros();
}
