int ledVerde = 8;
int ledVerm = 9;
int bot1 = 2;
int bot2 = 3;
int val1 = 1;
int val2 = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVerm, OUTPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVerm, LOW);

  val1 = digitalRead(bot1);
  if(val1 == 0){
    digitalWrite(ledVerde,HIGH);
  }

  val2 = digitalRead(bot2);

  if(val2 == 1){
    digitalWrite(ledVerm, HIGH);
  }

  
  

}
