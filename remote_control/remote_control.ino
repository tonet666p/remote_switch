#include <SoftwareSerial.h>
#define LED0 10
#define LED1 11
#define LED2 12

#define SW0 A0
#define SW1 A1
#define SW2 A2

bool sw_status[3]={0,0,0};
bool led_status[3]={false,false,false};
String sw_values[8]={"000","001","010","011","100","101","110","111"};
String pattern = "000";
int code = 0;

/*
 *   000 = 0
 *   001 = 1
 *   010 = 2
 *   011 = 3
 *   100 = 4
 *   101 = 5
 *   110 = 6
 *   111 = 7
 *   
 */

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


void switch_pattern(){
  if(sw_status[0] == 0){
    led_status[0] = !led_status[0];
  }
  if(sw_status[1] == 0){
    led_status[1] = !led_status[1];
  }
  if(sw_status[2] == 0){
    led_status[2] = !led_status[2];
  }
  delay(250);
}


void loop() {
  sw_status[0] = digitalRead(SW0);
  sw_status[1] = digitalRead(SW1);
  sw_status[2] = digitalRead(SW2);

  if(sw_status[0] == 0 || sw_status[1] == 0 || sw_status[2] == 0){
    switch_pattern();
  }
  digitalWrite(LED0,led_status[0]);
  digitalWrite(LED1,led_status[1]);
  digitalWrite(LED2,led_status[2]);

  pattern = String(led_status[0])+String(led_status[1])+String(led_status[2]);
  for(code=0; code<8 ; code++){
    if(sw_values[code] == pattern){
      break;
    }
  }

  Serial.print(String(sw_status[0])+String(sw_status[1])+String(sw_status[2]));
  Serial.print("-");
  Serial.println(code);
  HC12.print(code);
  
}
