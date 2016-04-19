#include<FileIO.h>
#include<stdio.h>
#include <Arduino.h>
#include "finalPath.h"


// -- Speed Limits --
#define SPEED_MAX  90
#define SPEED_MAX_ENTRY 90
#define SPEED_MAX_EXIT  100
#define SPEED_CALIBRATE 45
#define SPEED_TURN  70

//--Buttons
#define LEFT_BUTTON   19
#define RIGHT_BUTTON  45
#define FRONT_BUTTON  52

// Motor Driver
#define LEFT_MOTOR_A  9
#define LEFT_MOTOR_B  8
#define LEFT_MOTOR_PWM  10

#define RIGHT_MOTOR_A 5
#define RIGHT_MOTOR_B 6
#define RIGHT_MOTOR_PWM 3

#define MOTOR_STANDBY_PIN 7
#define DELAY_TURN 170

// -- Buttons --
#define LEFT_BUTTON_ON()  digitalRead(LEFT_BUTTON)
#define RIGHT_BUTTON_ON() digitalRead(RIGHT_BUTTON)
#define FRONT_BUTTON_ON()     digitalRead(FRONT_BUTTON)

// -- Motor Driver --
#define ENABLE_STANDBY  digitalWrite(MOTOR_STANDBY_PIN, HIGH)
#define DISABLE_STANDBY digitalWrite(MOTOR_STANDBY_PIN, LOW)

#define DELAY_TURN 170


class motor
{
  // private class members
private:
  unsigned char pinA, pinB, pinPWM;
  int speed;
  unsigned int maxSpeed;
  
public:
  motor();
  motor(unsigned char _pinA, unsigned char _pinB, unsigned char _pinPWM = 255, unsigned int _maxSpeed = 255);

  void setPins( unsigned char _pinA, unsigned char _pinB, unsigned char _pinPWM );
  void setMaxSpeed(unsigned int _maxSpeed);
  void initialise( );
  void setSpeed( int _speed );
  void write( int _speed );
  void write( );
  void stop( );
};


motor::motor()
{
  pinA = 255;
  pinB = 255;
  pinPWM = 255;
  speed = 0;
  maxSpeed = 255;
}

motor::motor(unsigned char _pinA, unsigned char _pinB, unsigned char _pinPWM, unsigned int _maxSpeed)
{
  pinA = _pinA;
  pinB = _pinB;
  pinPWM = _pinPWM;
  maxSpeed = _maxSpeed;
  speed = 0;
}

void motor::setPins(unsigned char _pinA, unsigned char _pinB, unsigned char _pinPWM)
{
  pinA = _pinA;
  pinB = _pinB;
  pinPWM = _pinPWM;
}

void motor::setMaxSpeed(unsigned int _maxSpeed)
{
  maxSpeed = _maxSpeed;
}

void motor::initialise()
{
  if ((pinA == 255) || (pinB == 255))
  {
    return;
  }
  
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  
  if (pinPWM != 255)
    pinMode(pinPWM, OUTPUT);
}

void motor::setSpeed(int _speed)
{
  speed = _speed;
}

void motor::stop()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  analogWrite(pinPWM, LOW);
}

void motor::write(int _speed)
{
  if (pinPWM == 255)
  {
    if (_speed >= 0)
    {
      analogWrite(pinA, _speed);
      digitalWrite(pinB, LOW);
    }

    else if (_speed < 0)
    {
      analogWrite(pinA, maxSpeed + _speed);
      digitalWrite(pinB, HIGH);
    }
  }
  
  else
  {
    if (_speed >= 0)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);

      analogWrite(pinPWM, _speed);
    }

    else if (_speed < 0)
    {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);

      analogWrite(pinPWM, -_speed);
    }
  }
}

void motor::write()
{
  if (pinPWM == 255)
  {
    if (speed >= 0)
    {
      analogWrite(pinA, speed);
      digitalWrite(pinB, LOW);
    }

    else if (speed < 0)
    {
      analogWrite(pinA, maxSpeed + speed);
      digitalWrite(pinB, HIGH);
    }
  }

  else
  {
    if (speed >= 0)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);

      analogWrite(pinPWM, speed);
    }

    else if (speed < 0)
    {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);

      analogWrite(pinPWM, -speed);
    }
  }
}

int addr=0;



motor motorLeft, motorRight;


void setup() 
{
  pinMode(MOTOR_STANDBY_PIN, OUTPUT);


  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
  pinMode(FRONT_BUTTON, INPUT);

  motorLeft.setPins(LEFT_MOTOR_A, LEFT_MOTOR_B, LEFT_MOTOR_PWM);
  motorRight.setPins(RIGHT_MOTOR_A, RIGHT_MOTOR_B, RIGHT_MOTOR_PWM);

  motorLeft.setMaxSpeed(SPEED_MAX);
  motorRight.setMaxSpeed(SPEED_MAX);

  motorLeft.initialise();
  motorRight.initialise();

  
  
  DISABLE_STANDBY;

  Serial.begin(9600);
  
}

void  turn(char _direction, unsigned int _speed, unsigned short _delayTime, unsigned char _automatic = 0)
{
  if (_automatic)
  {

  }

  else
  {
    switch (_direction)
    {
    case 'S':
      motorLeft.write(-_speed-2);
      motorRight.write(_speed);
      delay(970);
      motorLeft.write(0);
      motorRight.write(0);
      delay(1000);
      break;

    case 'R':

      motorLeft.write(-_speed);
      motorRight.write(-_speed);
      delay(_delayTime);
      motorLeft.write(0);
      motorRight.write(0);
      delay(500);
      motorLeft.write(-_speed-2);
      motorRight.write(_speed);
      delay(990);
      motorLeft.write(0);
      motorRight.write(0);
      delay(1000);
      break;

    case 'L':
      motorLeft.write(_speed);
      motorRight.write(_speed);
      delay(333);
      motorLeft.write(0);
      motorRight.write(0);
      delay(500);
      motorLeft.write(-_speed-2);
      motorRight.write(_speed);
      delay(990);
      motorLeft.write(0);
      motorRight.write(0);
      delay(1000);
      break;
    
    }
  }
}



void loop() 
{

  
  delay(1000);
  for(int i=0;i<strlen(path);i++)
  {

    turn(path[i], 50,312);  
  }

  
  
  while(!LEFT_BUTTON_ON());
  ENABLE_STANDBY;

}
