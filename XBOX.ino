#include <XBOXUSB.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXUSB Xbox(&Usb);

int pwm1=11;
int dir1=12;
int pwm2=5;
int dir2=3;
int pwm3=8;
int dir3=7;
int val1, val2;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.println(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.println(F("\r\nXBOX USB Library Started"));

  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT); 
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT); 
  pinMode(pwm3, OUTPUT);
  pinMode(dir3, OUTPUT); 
}



void loop() {
  Usb.Task();
  if (Xbox.Xbox360Connected) {
    if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
      Serial.println("L2: ");
      Serial.println(Xbox.getButtonPress(L2));
      Serial.println("\tR2: ");
      Serial.println(Xbox.getButtonPress(R2));
      Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
    } else
      Xbox.setRumbleOn(0, 0);


       val1 = map(val1, -33000, 33000, 0, 80);
       val2 = map(val2, -33000, 33000, 0, 80);

    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        if(Xbox.getAnalogHat(LeftHatY) > 7500||pwm1>30||pwm2>30)
            {
            Serial.println(F("Forward: ")); 
            Serial.println(Xbox.getAnalogHat(LeftHatY));
            Serial.println("\t");
            
             if (Xbox.getAnalogHat(LeftHatY) > 26000||val1>0||val2>0)
               forward();}
         else
           motors_stop();}

         if (Xbox.getAnalogHat(LeftHatY) < -7500||pwm1>30||pwm2>30)
          {
          Serial.println(F("Reverse: ")); 
          Serial.println(Xbox.getAnalogHat(LeftHatY));
          Serial.println("\t");
          
          if (Xbox.getAnalogHat(LeftHatY) < -26000||val1<0||val2<0)
            reverse();}
          else
           motors_stop();   
        }
      }
      
        if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500||pwm1>30||pwm2>30) {
         Serial.println(F("RightHatX: "));
         Serial.println(Xbox.getAnalogHat(RightHatX));
         Serial.println("\t");
         if(Xbox.getAnalogHat(RightHatX) > 7500)
            {
            Serial.println(F("Right: ")); 
            Serial.println(Xbox.getAnalogHat(RightHatX));
            Serial.println("\t");
            
            if (Xbox.getAnalogHat(RightHatX) > 26000||val1>0||val2>0)
              right();}
            else
              motors_stop();}

         if (Xbox.getAnalogHat(RightHatX) < -7500||pwm1>30||pwm2>30)
          {
          Serial.println(F("Left: ")); 
          Serial.println(Xbox.getAnalogHat(RightHatX));
          Serial.println("\t");
          
          if (Xbox.getAnalogHat(RightHatX) < -26000||val1<0||val2<0)
            left();}
          else
             motors_stop();   
            }
         }

         if (Xbox.getButtonClick(B)){ 
         Serial.println(F("Stop"));
         motors_stop();}
         }
    delay(1);
   }
}

  
void forward()
{
  Serial.println("forward ");
  analogWrite(pwm1,val1);   
  digitalWrite(dir1,LOW);
  analogWrite(pwm2,val2);   
  digitalWrite(dir2,HIGH);
}

void reverse()
{
  Serial.println("reverse ");
  analogWrite(pwm1,val1);   
  digitalWrite(dir1,HIGH);
  analogWrite(pwm2,val2);   
  digitalWrite(dir2,LOW);
}

void left()
{
  Serial.println("left ");
  analogWrite(pwm1,val1);   
  digitalWrite(dir1,LOW);
  analogWrite(pwm2,val2);   
  digitalWrite(dir2,LOW);
}

void right()
{
  Serial.println("right");
  analogWrite(pwm1,val1);   
  digitalWrite(dir1,LOW);
  analogWrite(pwm2,val2);   
  digitalWrite(dir2,LOW);
}

void motors_stop()
{
  Serial.println("stop");
  analogWrite(pwm1,0);   
  digitalWrite(dir1,LOW);
  analogWrite(pwm2,0);   
  digitalWrite(dir2,LOW);
}
