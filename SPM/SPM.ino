#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Center point coordinates
const int centerX = 90; // Adjust according to your setup
const int centerY = 90; // Adjust according to your setup

void setup()
{
  pwm.begin();
  pwm.setPWMFreq(50); // Set the PWM frequency to 50Hz

  // Initialize the servos to their neutral position
  setServoAngle(0, 90);
  setServoAngle(1, 90);
  setServoAngle(2, 90);
}

void loop()
{
  sphericalMovement();
}

// Function to set the angle of a servo
void setServoAngle(int servoNum, int angle)
{
  int pwmValue = map(angle, 0, 180, 150, 600); // Adjust the values according to your servo's range

  pwm.setPWM(servoNum, 0, pwmValue);

  // Log servo position
  Serial.print("Servo ");
  Serial.print(servoNum);
  Serial.print(" position: ");
  Serial.println(angle);
}

// Helper function to move servos in a spherical motion
void rotateStage()
{
  for (int j = 0; j < 3; j++)
  {
    for (int i = 90; i < 160; i += 1)
    {
      setServoAngle(0, i);
      setServoAngle(1, i);
      setServoAngle(2, i);
      delay(20);
    }

    for (int i = 160; i > 20; i -= 1)
    {
      setServoAngle(0, i);
      setServoAngle(1, i);
      setServoAngle(2, i);
      delay(20);
    }

    for (int i = 20; i < 90; i += 1)
    {
      setServoAngle(0, i);
      setServoAngle(1, i);
      setServoAngle(2, i);
      delay(20);
    }
  }
}

void sphericalMovement()
{
  const float tiltRange = 30.0; // Adjust the tilt range according to your requirements
  const float tiltSpeed = 0.5;  // Adjust the tilt speed according to your requirements

  for (float angle = 0; angle <= 360.0; angle += tiltSpeed)
  {
    float tiltAngleX = tiltRange * sin(angle * PI / 180.0); // Calculate the tilt angle for X-axis
    float tiltAngleY = tiltRange * cos(angle * PI / 180.0); // Calculate the tilt angle for Y-axis
    float tiltAngleZ = tiltRange * sin(angle * PI / 180.0 + PI / 4); // Calculate the tilt angle for Z-axis

    setServoAngle(0, centerX + tiltAngleX);
    setServoAngle(1, centerY - tiltAngleY);
    setServoAngle(2, 90 - tiltAngleZ);
  }
}