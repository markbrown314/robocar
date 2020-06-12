#define OFF  0
#define BOTH  1
#define LEFT  2
#define RIGHT 3
#define FORWARD 4
#define REVERSE 5

// connect motor controller pins to Arduino digital pins
// motor one
const int enA = 10;
const int in1 = 9;
const int in2 = 8;
// motor two
const int enB = 5;
const int in3 = 7;
const int in4 = 6;


void robocar_motor_speed(int motor, int speed)
{
  switch(motor) {
    case BOTH:
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
    case LEFT:
      analogWrite(enA, speed);
      break;
    case RIGHT:
      analogWrite(enB, speed);
      break;
    default:
      Serial.println("Error: invalid motor specified!");
      return;
  }
}

void robocar_motor_control(int motor, int state)
{
  int pin1;
  int pin2;
  int pin3;
  int pin4;

  int seta;
  int setb;
  
  switch(motor) {
    case BOTH:
      pin1 = in1;
      pin2 = in2;
      pin3 = in3;
      pin4 = in4;
      break;
    case LEFT:
      pin1 = pin3 = in1;
      pin2 = pin4 = in2;
      break;
    case RIGHT:
      pin1 = pin3 = in4;
      pin2 = pin4 = in3;
      break;
    default:
      Serial.println("Error: invalid motor specified!");
      return;   
  }

  switch(state) {
    /* all motors shut off regardless of direction */
    case OFF:
      seta = LOW;
      setb = LOW;
      break;
    case FORWARD:
      seta = LOW;
      setb = HIGH;
      break;
    case REVERSE:
      seta = HIGH;
      setb = LOW;
      break;
  }

  digitalWrite(pin1, seta);
  digitalWrite(pin2, setb);
  
  digitalWrite(pin3, seta);
  digitalWrite(pin4, setb); 
}
  
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  robocar_motor_speed(BOTH, OFF);
  robocar_motor_control(BOTH, OFF);
  delay(2000);
  /* clockwise */
  robocar_motor_speed(BOTH, 200);
  robocar_motor_control(LEFT, FORWARD);
  robocar_motor_control(RIGHT, REVERSE);
  delay(5000);
  /* counter clockwise */
  robocar_motor_speed(BOTH, 200);
  robocar_motor_control(LEFT, REVERSE);
  robocar_motor_control(RIGHT, FORWARD);
  delay(5000);

  /* forward */
  robocar_motor_speed(BOTH, 200);
  robocar_motor_control(LEFT, FORWARD);
  robocar_motor_control(RIGHT, FORWARD);
  delay(3000);

  /* forward */
  robocar_motor_speed(BOTH, 200);
  robocar_motor_control(LEFT, REVERSE);
  robocar_motor_control(RIGHT, REVERSE);
  delay(3000);
}