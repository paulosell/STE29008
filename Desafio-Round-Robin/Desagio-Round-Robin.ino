int led = 13;
int botao = 5;
int val = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(botao, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 piscaLed(1);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 
 piscaLed(0);

escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);
 escreveBotao();
 delay(200);


}

void piscaLed(int valor){
  digitalWrite(led, valor);
  

  
  
}

void escreveBotao(){
   val = digitalRead(botao);
  if(val == 0){
    
    Serial.println("botao pressionado");
  }
}
