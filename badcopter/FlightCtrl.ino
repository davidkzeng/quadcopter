void FlightControl(){
  throttle=throttle_value;
  
  pid_roll_setpoint = 0;
  pid_pitch_setpoint = 0;
  pid_yaw_setpoint = 0;
  pid_update();
  pid_compute();
  
  // yaw control disabled for stabilization testing...
  if (throttle >= 1000 && (shutOffTime == 0 || micros() < shutOffTime)) {
    m0=throttle + pid_roll_out + pid_pitch_out; //+pid_yaw_out
    m1=throttle - pid_roll_out + pid_pitch_out; //-pid_yaw_out
    m2=throttle + pid_roll_out - pid_pitch_out; //-pid_yaw_out
    m3=throttle - pid_roll_out - pid_pitch_out; //+pid_yaw_out
  } else {
    m0 = 1000;
    m1 = 1000;
    m2 = 1000;
    m3 = 1000;
  }
  /*
  Serial.print("pid: ");
  Serial.print(throttle);
  Serial.print(" ");
  Serial.print(pid_pitch_out);
  Serial.print(" ");
  Serial.println(pid_roll_out);
  */
  /*
  #ifdef SAFE
    if(throttle < THROTTLE_SAFE_SHUTOFF)
    {
      m0 = m1 = m2 = m3 = MOTOR_ZERO_LEVEL;
    }
  #endif
  */
  m0 = min(2000, max(1000, m0));
  m1 = min(2000, max(1000, m1));
  m2 = min(2000, max(1000, m2));
  m3 = min(2000, max(1000, m3));
  m0 = map(m0, 1000, 2000, 1, 180);
  m1 = map(m1, 1000, 2000, 1, 180);
  m2 = map(m2, 1000, 2000, 1, 180);
  m3 = map(m3, 1000, 2000, 1, 180);
  update_motors(m0, m1, m2, m3);
}
