#include <SoftwareSerial.h>

#define OUT0 10
#define OUT1 11
#define OUT2 12

#define SW0 5
#define SW1 6
#define SW3 7

String rx_data = "";
char character;
bool sw_status[] = {0,0,0};
String sw_values[8]={"000","001","010","011","100","101","110","111"};
int signal = 0;
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

void set_sw_pattern(){
  sw_status[0]=sw_values[code].substring(0,1).toInt();
  sw_status[1]=sw_values[code].substring(1,2).toInt();
  sw_status[2]=sw_values[code].substring(2).toInt();
}

void setup(){
  pinMode(OUT0, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  HC12.begin(1200);
  Serial.begin(9600);
}

char led;

void loop(){
  if(HC12.available()>0){
    rx_data = HC12.read();
    code = rx_data.toInt() - 48;
    set_sw_pattern();
    signal = 10;
    Serial.println(code);
  }else if(HC12.available()<1){
    if(signal < 5){
      code = 0;
      set_sw_pattern();
    }
    if (signal > 0){
      signal -= 1;
      delay(100);
    }
  }
  digitalWrite(OUT0,sw_status[0]);
  digitalWrite(OUT1,sw_status[1]);
  digitalWrite(OUT2,sw_status[2]);
}
