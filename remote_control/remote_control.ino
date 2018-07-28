#include <SoftwareSerial.h>
#define LED0 10
#define LED1 11
#define LED2 12

#define SW0 A0
#define SW1 A1
#define SW2 A2

int last_status[3] = {1,1,1};
int sw_status[3]={0,0,0};

SoftwareSerial HC12(8,9);

void setup() {
  pinMode(SW0, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  HC12.begin(1200);
  Serial.begin(9600);
}

void loop() {

  sw_status[0] = digitalRead(SW0);
  if (sw_status[0] == HIGH && last_status[0] == LOW) {
     digitalWrite(LED0, !digitalRead(LED0));
  }
  last_status[0] = sw_status[0];

  sw_status[1] = digitalRead(SW1);
  if (sw_status[1] == HIGH && last_status[1] == LOW) {
     digitalWrite(LED1, !digitalRead(LED1));
  }
  last_status[1] = sw_status[1];

  sw_status[2] = digitalRead(SW2);
  if (sw_status[2] == HIGH && last_status[2] == LOW) {
     digitalWrite(LED2, !digitalRead(LED2));
  }
  last_status[2] = sw_status[2];
  delay(50);
  
  //Serial.println("Transmitting str:("+String(digitalRead(LED0))+"-"+String(digitalRead(LED1))+"-"+String(digitalRead(LED2))+")");
  HC12.print("{"+String(digitalRead(LED0))+","+String(digitalRead(LED1))+","+String(digitalRead(LED2))+"} ");
}
