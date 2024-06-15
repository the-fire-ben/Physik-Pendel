//Einstellung der Sensitivität des Potis

volatile int i = 0;

void setup() {
  Serial.begin(115200);
  attachInterrupt(0, Event, RISING);
  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Event(){
  i++;
  Serial.print("Ausschlag Nr. ");
  Serial.println(i);
}
