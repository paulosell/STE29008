int num = 0;

void setup() {
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    num = 1;
    Serial.write(num);
    delay(2000);
 

  
    num = 0;
    Serial.write(num);
    delay(2000);
  
  
}
