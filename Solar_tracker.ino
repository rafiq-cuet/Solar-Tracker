#include <Servo.h>
Servo horizontal;  // horizontal servo
int servoh = 90;
int servohLimitHigh = 85;
int servohLimitLow = 5;
// 65 degrees MAX
Servo vertical;  // vertical servo
int servov = 45;
int servovLimitHigh = 160;
int servovLimitLow = 80;
// LDR pin connections
// name = analogpin;
int ldrlt = A6;  //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = A4;  //LDR top rigt - BOTTOM RIGHT
int ldrld = A3;  //LDR down left - TOP LEFT
int ldrrd = A5;  //ldr down rigt - TOP RIGHT
void setup() {
  horizontal.attach(9);
  vertical.attach(3);
  horizontal.write(180);
  vertical.write(45);
  delay(2500);
}
void loop() {
  int lt = analogRead(ldrlt);  // top left
  int rt = analogRead(ldrrt);  // top right
  int ld = analogRead(ldrld);  // down left
  int rd = analogRead(ldrrd);  // down right
  int dtime = 10;
  int tol = 90;             // dtime=diffirence time, tol=toleransi
  int avt = (lt + rt) / 2;  // average value top
  int avd = (ld + rd) / 2;  // average value down
  int avl = (lt + ld) / 2;  // average value left
  int avr = (rt + rd) / 2;  // average value right
  int dvert = avt - avd;    // check the diffirence of up and down
  int dhoriz = avl - avr;   // check the diffirence og left and rigt
  if (-1 * tol > dvert || dvert > tol) {
    if (avt > avd) {
      servov = ++servov;
      if (servov > servovLimitHigh) { servov = servovLimitHigh; }
    } else if (avt < avd) {
      servov = --servov;
      if (servov < servovLimitLow) { servov = servovLimitLow; }
    }
    vertical.write(servov);
  }
  if (-1 * tol > dhoriz || dhoriz > tol)  // check if the diffirence is in the tolerance else change horizontal angle
  {
    if (avl > avr) {
      servoh = --servoh;
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    } else if (avl < avr) {
      servoh = ++servoh;
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    } else if (avl = avr) {
      delay(5000);
    }
    horizontal.write(servoh);
  }
  delay(dtime);
}