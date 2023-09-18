#include <MsTimer2.h>

#define RAD2DEG(x)   (x*180.0/3.14159)
#define DEG2RAD(x)   (x/180.0*3.14159)
#define wheel_track 0.068 //양쪽 바뀌       // m 단위로 구할 것 0.1 -> 10cm

/////////////////// L298 ////////////////////
#define ENA 8
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
#define ENB 13

struct Pose2D
{
  double x;
  double y;
  double theta; //theta = radian
} my_odom;

const byte outPin = 13; // Output pin: digital pin 13(D13)
const byte interruptPin1 = 20; // Interrupt pin: D2
const byte interruptPin2 = 21; // Interrupt pin: D2
const byte encoder1_A = 2; // Interrupt pin: D2
const byte encoder1_B = 3; // Interrupt pin: D2
const byte encoder2_A = 20; // Interrupt pin: D2
const byte encoder2_B = 21; // Interrupt pin: D2
const byte resetPin = 5;
volatile byte state = 0;
//unsigned long cnt1 = 0; // 추가
//unsigned long cnt2 = 0; // 추가
long cnt1 = 0; // 추가
long cnt2 = 0; // 추가

long cnt1_old = 0; // 추가
long cnt2_old = 0; // 추가

double pulst_to_distance_left = 0.2 / 974.6;
double pulst_to_distance_right = 0.2 / 974.5;

const double odom_left = 0;
const double odom_right = 0;

double yaw = 0.0;
double yaw_degree = 0.0;

double heading(double x, double y)
{
  double head = atan2(y, x); // Slope Y, Slope X  x = wheel_track
  return head;
}

void MsTimer2_ISR()
{
  char msg[100] = {0x00,};
  double odom_left_delta = 0.0;
  double odom_right_delta = 0.0;
  double odom_center_delta = 0.0;
  long delta_encoder_left = 0;
  long delta_encoder_right = 0;
  double theta_delta = 0.0;
  double theta_delta_degree = 0.0;

  delta_encoder_left = cnt1 - cnt1_old;
  delta_encoder_right = cnt2 - cnt2_old;

  //   delta_encoder_left = 100;
  //delta_encoder_right = -100;
  /*
    sprintf(msg, "encoder delta : %3d %3d", delta_encoder_left, delta_encoder_right);
    Serial.print(msg);
    Serial.print("    ");
  */
  odom_left_delta = delta_encoder_left * pulst_to_distance_left;
  odom_right_delta = delta_encoder_right * pulst_to_distance_right;
  odom_center_delta = (odom_left_delta + odom_right_delta) * 0.5; // 안전성 나누기 지원 안하는 것도 있고 속도도 조금 더 빠르기 때문

  Serial.print("delta_encoder_left = ");  Serial.print( delta_encoder_left);  Serial.print("    ");
  Serial.print("delta_encoder_right = "); Serial.print( delta_encoder_right); Serial.println("    ");

  Serial.print("odom_left_delta = ");  Serial.print(odom_left_delta);  Serial.print("    ");
  Serial.print("odom_right_delta = "); Serial.print(odom_right_delta); Serial.println("    ");

  theta_delta = heading(wheel_track, (odom_right_delta - odom_left_delta));
  Serial.print("delta theta radian: ");  Serial.print(theta_delta); Serial.println("    ");
  yaw += theta_delta;
  theta_delta_degree = RAD2DEG(theta_delta);
  Serial.print("yaw radian: ");  Serial.print(yaw); Serial.println("    ");
  Serial.print("delta theta degree: ");  Serial.print(theta_delta_degree); Serial.println("    ");
  yaw_degree += theta_delta_degree;
  Serial.print("yaw degree: ");  Serial.print(yaw_degree); Serial.println("    ");

  /*


      Serial.print("wheel_track = ");  Serial.print(wheel_track); Serial.print("    ");

      Serial.print("theta_delta = "); Serial.print(theta_delta); Serial.print("    ");

      theta_delta_degree = DEG2RAD(theta_delta);
      Serial.print("theta_delta_degree = "); Serial.print(theta_delta_degree); Serial.print("    ");
  */
  my_odom.x += odom_center_delta * sin(theta_delta);
  my_odom.y += odom_center_delta * cos(theta_delta);
  my_odom.theta += theta_delta;

  Serial.print("odom : ");
  Serial.print(my_odom.x); Serial.print("    ");
  Serial.print(my_odom.y); Serial.print("    ");
  Serial.println(my_odom.theta); Serial.println("    ");

  cnt1_old = cnt1;
  cnt2_old = cnt2;
}

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(outPin, OUTPUT); // Output mode
  //  pinMode(interruptPin1, INPUT_PULLUP); // Input mode, pull-up
  //  pinMode(interruptPin2, INPUT_PULLUP); // Input mode, pull-up
  pinMode(encoder1_A, INPUT_PULLUP);
  pinMode(encoder1_B, INPUT_PULLUP);
  pinMode(encoder2_A, INPUT_PULLUP);
  pinMode(encoder2_B, INPUT_PULLUP);
  pinMode(resetPin, INPUT);
  //  attachInterrupt(digitalPinToInterrupt(interruptPin1), intfunc1, RISING); // Enable interrupt
  //  attachInterrupt(digitalPinToInterrupt(interruptPin2), intfunc2, RISING); // Enable interrupt
  attachInterrupt(digitalPinToInterrupt(encoder1_A), intfunc1, RISING); // Enable interrupt
  attachInterrupt(digitalPinToInterrupt(encoder2_A), intfunc2, RISING); // Enable interrupt

  my_odom.x = 0;   my_odom.y = 0;   my_odom.theta = 0;

  Serial.begin(115200);

  MsTimer2::set(100, MsTimer2_ISR); // 0.1초마다 작동
  MsTimer2::start();
}

void motor_R_control(int motor_speed_R) // 모터 A의 속도(speed)제어
{
  if (motor_speed_R >= 0)
  {
    digitalWrite(IN1, LOW);         //모터의 방향 제어
    digitalWrite(IN2, HIGH);
    if (motor_speed_R >= 255) motor_speed_R = 255;
    analogWrite(ENA, motor_speed_R); //모터의 속도 제어
  }
  else
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    if (motor_speed_R <= -255) motor_speed_R = -255;
    analogWrite(ENA, -motor_speed_R);
  }
}

void motor_L_control(int motor_speed_L) // 모터 A의 속도(speed)제어
{
  if (motor_speed_L >= 0)
  {
    digitalWrite(IN3, HIGH);         //모터의 방향 제어
    digitalWrite(IN4, LOW);
    if (motor_speed_L >= 255) motor_speed_L = 255;
    analogWrite(ENB, motor_speed_L); //모터의 속도 제어
  }
  else
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    if (motor_speed_L <= -255) motor_speed_L = -255;
    analogWrite(ENB, -motor_speed_L);
  }
}

/*
  void intfunc1() // Interrupt function
  {
  cnt1++;
  if (state == 0) // If D4 output is low
  {
    digitalWrite(outPin, HIGH);
    state = 1;
  }
  else
  {
    digitalWrite(outPin, LOW);
    state = 0;
  }
  }

  void intfunc2() // Interrupt function
  {
  cnt2++;
  if (state == 0) // If D4 output is low
  {
    digitalWrite(outPin, HIGH);
    state = 1;
  }
  else
  {
    digitalWrite(outPin, LOW);
    state = 0;
  }
  }

*/
void intfunc1()
{
  if (digitalRead(encoder1_B) == HIGH)
  {
    cnt1--;
  }
  else
  {
    cnt1++;
  }
}

void intfunc2()
{
  if (digitalRead(encoder2_B) == LOW)
  {
    cnt2--;
  }
  else
  {
    cnt2++;
  }
}

void loop()
{
  /*
    Serial.print("cnt1: ");
    Serial.print(cnt1);
    if (digitalRead (resetPin) == HIGH)
    {
     cnt1 = 0;
    }

    Serial.print("   cnt2: ");
    Serial.println(cnt2);
    if (digitalRead (resetPin) == HIGH)
    {
     cnt2 = 0;
    }
    delay(1000);
  */

  /*
    Serial.print("cnt1_L: ");
    Serial.print(cnt1);
    Serial.print("   cnt2_R: ");
    Serial.println(cnt2);
    delay(100);
    //Serial.print(cnt1); Serial.print("   ");
    //Serial.println(cnt2);
  */

  //전진
  motor_R_control(120);
  motor_L_control(120);
  delay(1000);

  //회전
  motor_R_control(120);
  motor_L_control(-120);
  delay(1000);

  //전진
  motor_R_control(120);
  motor_L_control(120);
  delay(1000);



  /*
    Serial.print("odom_left: ");
    Serial.print(odom_left);
    Serial.print("   odom_right: ");
    Serial.println(odom_right);
  */
}
