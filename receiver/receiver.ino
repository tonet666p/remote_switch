#include <SoftwareSerial.h>

#define OUT0 10
#define OUT1 11
#define OUT2 12

#define SW0 5
#define SW1 6
#define SW3 7

String rx_data = "";
char character;
int sw_status[] = {0,0,0};
int signal = 0;

SoftwareSerial HC12(8,9);

void setup(){
  pinMode(OUT0, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  HC12.begin(1200);
  Serial.begin(9600);
}

char led;

void loop(){

  while(HC12.available()>0){
    character = HC12.read();
    if (character == ' ') {
      if (rx_data.length() == 7) {
        
        if ( rx_data[0] == '{' && rx_data[6]=='}' ){
          sw_status[0]=rx_data.substring(1,2).toInt();
          sw_status[1]=rx_data.substring(3,4).toInt();
          sw_status[2]=rx_data.substring(5,6).toInt();

          //Serial.println("Received str:("+String(sw_status[0])+"-"+String(sw_status[1])+"-"+String(sw_status[2])+")");
          //HC12.println("Received str:("+String(sw_status[0])+"-"+String(sw_status[1])+"-"+String(sw_status[2])+")");
          
          signal = 10;
        }
      }
      rx_data = "";
    }else{
      rx_data += character;
    }
  }
  if(HC12.available()<1){
    if(signal < 5){
      //Serial.println("Received str:("+String(sw_status[0])+"-"+String(sw_status[1])+"-"+String(sw_status[2])+")");
      sw_status[0]=0;
      sw_status[1]=0;
      sw_status[2]=0;
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
