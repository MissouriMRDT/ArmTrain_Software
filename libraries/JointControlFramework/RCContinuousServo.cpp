#include "RCContinuousServo.h"
#include "pwmWriter.h"

RCContinuousServo::RCContinuousServo(const int pwmPin, bool upsideDown) : OutputDevice()
{ 
  PWM_PIN = pwmPin;
  inType = spd;
  invert = upsideDown;
}

void RCContinuousServo::move(const long movement)
{
  if(!enabled) return;

  int mov = invert ? -movement : movement;

  // adjust the mov value to fit the range.
  // mov is a scale from -1000 to 0 to 1000. the PWM range is 500 to 1500 to 2500
  // thus, the two can directly add up since both use a range of 2000. Just adjust for the
  // offset of where the two values use a 'o' value. 0 for speed, 1500 for pwm_stop.
  int pwm = mov+PWM_STOP;
  PwmWrite(PWM_PIN, pwm, PWM_PERIOD);
}

void RCContinuousServo::setPower(bool powerOn)
{
  enabled = powerOn;
  
  if(!enabled)
  {
    move(0);
  }
}
