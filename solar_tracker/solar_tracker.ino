#include <ESP32Servo.h> // include Servo library
// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 100; // 90; // stand horizontal servo
int servohLimitHigh = 175;
int servohLimitLow = 5;
// 65 degrees MAX
Servo vertical; // vertical servo
int servov = 45; // 90; // stand vertical servo
int servovLimitHigh = 60;
int servovLimitLow = 1;
// LDR pin connections
// name = analogpin;
int ldrlt = 35; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 25; //LDR top rigt - BOTTOM RIGHT
int ldrld = 27; //LDR down left - TOP LEFT
int ldrrd = 26; //ldr down rigt - TOP RIGHT
void setup(){
Serial.begin(9600);
horizontal.attach(21);
vertical.attach(19);
horizontal.write(100);
vertical.write(45);
delay(3000);
}
void loop() {
int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left
int rd = analogRead(ldrrd); // down right
int dtime = 10; int tol = 90; // dtime=diffirence time, tol=toleransi
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value down
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value right
int dvert = avt - avd; // check the diffirence of up and down
int dhoriz = avl - avr;// check the diffirence og left and rigt

Serial.print(avt);
Serial.print(" ");
Serial.print(avd);
Serial.print(" ");
Serial.print(avl);
Serial.print(" ");
Serial.print(avr);
Serial.print(" ");
Serial.print(dtime);
Serial.print(" ");
Serial.print(tol);
Serial.println(" ");

if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
 {
 if (avt > avd)
 {
 servov = ++servov;
 if (servov > servovLimitHigh)
 {
 servov = servovLimitHigh;
 }
 }
 else if (avt < avd)
 {
 servov= --servov;
 if (servov < servovLimitLow)
 {
 servov = servovLimitLow;
 }
 }
 vertical.write(servov);
 }
if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
 {
 if (avl > avr)
 {
 servoh = --servoh;
 if (servoh < servohLimitLow)
 {
 servoh = servohLimitLow;
 }
 }
 else if (avl < avr)
 {
 servoh = ++servoh;
 if (servoh > servohLimitHigh)
 {
 servoh = servohLimitHigh;
 }
 }
 else if (avl = avr)
 {
 delay(5000);
 }
 horizontal.write(servoh);
 }
 Serial.print(" ");
 Serial.print(servoh);
 Serial.print(" ");
 Serial.print(servov);
 Serial.print(" ");
 delay(dtime);
}