byte byte_received = 0;
int led = 13;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    byte_received = Serial.read();
    digitalWrite(led, byte_received);
  }
  

  
}
