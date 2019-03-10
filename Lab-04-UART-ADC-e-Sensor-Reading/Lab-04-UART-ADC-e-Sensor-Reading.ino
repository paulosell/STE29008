int val = 0;
int analogPin = A3;

void setup() {
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  val = RMS(30); 
  Serial.print("Digital: ");
  Serial.println(val);
  delay(1000);

  float volt = val*(5.0/1023.0);
  Serial.print("Analog: ");
  Serial.println(volt);
}

int media(int repeat){
  int x = 0;
  int digital_value = 0;
  int accumulated = 0;
  while(x < repeat){
    digital_value = analogRead(analogPin);
    accumulated = accumulated + (digital_value*digital_value);
    x=x+1;
  }

  int average = accumulated/repeat;
  return (average);
    
}

int RMS(int repeat){
  int x = 0;
  int digital_value = 0;
  int accumulated = 0;
  while(x < repeat){
    digital_value = analogRead(analogPin);
    accumulated = accumulated + (digital_value*digital_value);
    x=x+1;
  }

  int average = accumulated/repeat;
  return sqrt(average);
    
}
