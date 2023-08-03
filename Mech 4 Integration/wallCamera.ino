#include <Wire.h>
#include <Servo.h>
Servo servo;
int prev=90;
int input;
bool start=false;
bool isCatch=false;

void setup() {
  Serial.begin(9600);
  
  //servo
  servo.attach(2);
  servo.write(180);

  //under ultrasonic
  pinMode(12, OUTPUT); //trigPin
  pinMode(13, INPUT); //echoPin

  //forwardLeft ultrasonic
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  

  //forwardRight ultrasonic
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  
  //forward ultrasonic
  pinMode(14, OUTPUT);
  pinMode(15, INPUT);
  
  //I2C
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);////////////////////////////////////////////////////
  

  //left ultrasonic
  /*pinMode(9, OUTPUT);
  pinMode(10, INPUT);*/
  //Car
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);//left
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);//right
  
  //ToRPI
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
}
void receiveEvent(int howMany){
  while(Wire.available()){
    input=Wire.read();
    input=input-128;
    start=true;
    
  }
}
void forward(){
    analogWrite(11,90);
    analogWrite(6,0);
    analogWrite(5,90);
    analogWrite(3,0);
  
}
void forwardslow(){
    analogWrite(11,70);
    analogWrite(6,0);
    analogWrite(5,70);
    analogWrite(3,0);
  
}
void left(int l){
  int t=80-l;
  if(t<40){
    t=40;
  }
  analogWrite(11,80); //right
  analogWrite(6,0);
  analogWrite(5,t); //left
  analogWrite(3,0);
  
} 
void leftenforce(int l){
  int t=120-l;
  if(t<0){
    t=0;
  }
  analogWrite(11,120); //right
  analogWrite(6,0);
  analogWrite(5,t); //left
  analogWrite(3,60);
  
} 
void right(int r){
  int t=80+r;
  if(t<40){
    t=40;
  }
  analogWrite(11,t); //right
  analogWrite(6,0);
  analogWrite(5,80); //left
  analogWrite(3,0);
}
void rightenforce(int r){
  int t=120+r;
  if(t<0){
    t=0;
  }
  analogWrite(11,t); //right
  analogWrite(6,60);
  analogWrite(5,120); //left
  analogWrite(3,0);
}

void back(){
  analogWrite(11,0); //right
  analogWrite(6,110);
  analogWrite(5,0); //left
  analogWrite(3,110);
}
void halt(){
  analogWrite(11,0); //right
  analogWrite(6,0);
  analogWrite(5,0); //left
  analogWrite(3,0);
}
void ccw(){
  analogWrite(11,50+20);
  analogWrite(6,0);
  analogWrite(5,0);
  analogWrite(3,0);
}
void cw(){
  analogWrite(11,0);
  analogWrite(6,0);
  analogWrite(5,60+20);
  analogWrite(3,0);
}

float ultrasonic(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the response from the HC-SR04 Echo Pin
 
  long duration = pulseIn(echoPin, HIGH);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  
  float distance = (duration / 2) * 0.0343;
  return distance;
}

void loop() {
  float ForwardLeftDistance=ultrasonic(7,8);
  float ForwardRightDistance=ultrasonic(A2,A3);
  float ForwardDistance=ultrasonic(14,15);
  float UnderDistance=ultrasonic(12,13);
  
  if(start==true){
    
     if(!isCatch){
      if(input>5){
        if(input>120){
          ccw();
        }else{
          left((input));
        }
      }else if(input<-5){
        
        if(input<-120){
          cw();
        }else{
          right((input));
        }
        
      }else{
        forward();
      }
      //forward();
      if(UnderDistance<5||UnderDistance>20){
        servo.write(125);
        isCatch=true;
        digitalWrite(10,HIGH);
      }
    }else{
    
      if(input==127){
           halt();
           while(true){
              ForwardLeftDistance=ultrasonic(7,8);
              ForwardRightDistance=ultrasonic(A2,A3);
              ForwardDistance=ultrasonic(14,15);
              if(ForwardLeftDistance<10){
                  back();
                  delay(100);
                  rightenforce(-90);
                  delay(150);
                  forwardslow();
               }else if(ForwardRightDistance<10){
                  back();
                  delay(100);
                  leftenforce(90);
                  delay(150);
                  forwardslow();
                }else if(ForwardDistance<20){
                  halt();
                  servo.write(180);
                }else{
                  forward();
                }
                
           }
       }else if(ForwardLeftDistance<10||ForwardRightDistance<10||ForwardDistance<15){
         if(ForwardLeftDistance<15){
            back();
            delay(150);
            rightenforce(-100);
            delay(200);
            forwardslow();
         }else if(ForwardRightDistance<15){
            back();
            delay(150);
            leftenforce(100);
            delay(200);
            forwardslow();
          }else if(ForwardDistance<15){
            back();
            delay(200);
            //leftenforce(70);
            //delay(100);
            if(input==-128){
              rightenforce(-100);
            }else{
              leftenforce(100);
            }
            delay(200);
            forwardslow();
          }
       }else{
         Serial.println(input);
          if(input>125){
             ccw();
          }else if(input<-125){
             cw();
          }else if(input>5){
            left(input);
          }else if(input<-5){
            right(input);
          }else{
            forward();
          }
       }
    }
  }
    
 /*
  Serial.print("LeftDistance : "); 
  Serial.print(LeftDistance);
  Serial.println();
  Serial.print("ForwardLeftDistance : "); 
  Serial.print(ForwardLeftDistance);
  Serial.println();
  Serial.print("ForwardRightDistance : "); 
  Serial.print(ForwardRightDistance);
  Serial.println();
  */Serial.print("ForwardDistance : "); 
  Serial.print(ForwardDistance);
  Serial.println();
  /*Serial.print("UnderDistance : "); 
  Serial.print(UnderDistance);
  Serial.println();*/
  //delay(3000);

  }
