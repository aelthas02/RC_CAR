#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif

RH_ASK driver(2000, 4, 2, 0); 

int SW = 8;
int X = A1;
int Y = A0;
String message;
void setup()
{
  pinMode(SW, INPUT);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  #ifdef RH_HAVE_SERIAL
      Serial.begin(115200);	  // Debugging only
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
    // concatenar os valores SW , X e Y em uma String
    message = "-" + String(digitalRead(SW)) + "-" + String(analogRead(X)) + "-" + String(analogRead(Y));

    //criar um vetor do tamanho da String de mensagem
    char data[message.length()];

    //Inserir cada caractere da mensagem no vetor
    for(int i = 0; i < message.length(); i++){
      data[i] = message.charAt(i);
    }
    
    const char *msg = data;

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(50);
}
