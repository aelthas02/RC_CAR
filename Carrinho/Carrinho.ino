#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif

RH_ASK driver(2000, 8, 4, 0); 
char SW;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
  
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  #ifdef RH_HAVE_SERIAL
    Serial.begin(9600);
  #endif
    if (!driver.init())
      #ifdef RH_HAVE_SERIAL
             Serial.println("init failed");
      #else
  ;
  #endif
}

void loop()
{
    String X, Y;
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen))
    {
      String message;
      for(int i = 0; i < buflen; i++){
        message += (char)buf[i];
      }
      SW = buf[1];
      for(int i = 3; i < buflen; i++){
        if(isDigit((char)buf[i])){
          X += (char)buf[i];
        }else{
          for(int j = i + 1; j < buflen; j++){
            if(isDigit((char)buf[j])){
              Y += (char)buf[j];
            }else{
              break;
            }        
          }
          break;
        }        
      }
      Serial.print(SW);
      Serial.print(" X :");
      Serial.print(X);
      Serial.print(" Y :");
      Serial.println(Y);
      
      //YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
      if(Y.toInt() > 600 && (X.toInt() > 200 && X.toInt() < 600)){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }
      else {
        if(Y.toInt() < 200 && (X.toInt() > 200 && X.toInt() < 600)){
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
        }
        else{          
          if(X.toInt() > 600 && (Y.toInt() > 200 && Y.toInt() < 600)){
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
          }else{
            if(X.toInt() < 200 && (Y.toInt() > 200 && Y.toInt() < 600)){
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
            }else{
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
            }
          }
        }
      }
    }
}
