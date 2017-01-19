#include <MadgwickAHRS.h>

#include <PID_v1.h>

#include <BMI160.h>
#include <CurieIMU.h>
#include <CurieBLE.h>

#include "Config.h"
#include <MPULib.h>
#include <Wire.h>
#include <PIDCont.h>
#include <avr/pgmspace.h>
#include <Servo.h>

Madgwick filter;
Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;
unsigned long microsPerReading, microsPrevious;
unsigned long microsFirst;
unsigned int throttle_value = 900;
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
BLEPeripheral blePeripheral; // create peripheral instance
BLEService throttleService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service
BLEUnsignedIntCharacteristic throttleCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
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

  Serial.println("Starting Acceleration calibration and enabling offset compensation...");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);

  blePeripheral.setLocalName("Throttle");
  // set the UUID for the service this peripheral advertises:
  blePeripheral.setAdvertisedServiceUuid(throttleService.uuid());

  // add service and characteristics
  blePeripheral.addAttribute(throttleService);
  blePeripheral.addAttribute(throttleCharacteristic);

  throttleCharacteristic.setValue(0);

  // advertise the service
  blePeripheral.begin();
  Serial.println("begun service");
}



void loop() {
  blePeripheral.poll();
  // Serial.println("in main loop");
  if (throttleCharacteristic.written()) {
    int val = throttleCharacteristic.value();
    // update LED, either central has written to characteristic or button state has changed
    throttle_value = val;
    Serial.println("lol");
  }
  imu_update();
  FlightControl();
  prev_time = micros();
}
