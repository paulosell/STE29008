int interrupt_source = 0;
int led_state = 0;
int debounce_limit = 200;
int sensitivity = HIGH;
int botao = 2;
int antes = 0;
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(interrupt_source), handler, HIGH);
  pinMode(botao, INPUT);
  pinMode(13, OUTPUT);
  antes = millis();
}

void loop() {
  digitalWrite(13, led_state);
  
}

void handler(){
  
  if(debounce()){
    led_state = !led_state;
  }
  
}

int debounce(){
  int agora = millis();
  if(( agora - antes) > 200){
    antes = agora;
    return 1;
  }
  else {
    return 0;
  }
}
