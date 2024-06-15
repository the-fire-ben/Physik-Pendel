#include <math.h>

#define wdh 10    //wiederholungen der Messung
#define cnt 5     //countdown Länge in Sekunden
#define g 9.81 

float T;          //Periodendauer
float l;          //Fadenlaenge

volatile long ges = 0;      //Gesamtlänge der Perioden in Summe
volatile int mess[wdh+1];   //Array mit Messwerten
volatile int i = 0;         //Versuchsnummer

void setup() {

  Serial.begin(115200);
  Serial.println("Ready");
  Serial.print("Wiederholungen: ");
  Serial.println(wdh);
  
  for (int t=cnt ; t >= 0; t--) {     //Countdown zur Vorbereitung
    Serial.println(t);
    delay(1000);
  }

  
  attachInterrupt(0, schwingung, FALLING);
  

}

void loop() {

}

void schwingung(){
  mess[i] = (millis());
  i++;
  Serial.print("Schwingung Nr. ");
  Serial.println(i);

  if(i == wdh+1){
    noInterrupts();
    ende();
  }
}

void ende(){
    noInterrupts();
    for (i=1 ; i <= wdh; i++) {
      Serial.print("Messung Nr. ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(mess[i]-mess[i-1]);
      ges = ges + mess[i] - mess[i-1];
    }
    
    T = ges/wdh;
    Serial.print("Gesamtzeit in ms: ");
    Serial.println(ges);      
    Serial.print("Periodendauer in ms: ");
    Serial.println(T);

    T = T/1000;
    
    Serial.print("Periodendauer in s: ");
    Serial.println(T);

    l= ((pow(T,2) * g)) / (4 * pow(M_PI,2));
    Serial.print("Seillaenge in m: ");
    Serial.println(l);
    Serial.println("Done");
}
