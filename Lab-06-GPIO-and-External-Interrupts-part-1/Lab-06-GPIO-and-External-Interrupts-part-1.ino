int interrupt_source = 0;
volatile boolean led_state = 0;
int debounce_limit = 200;
int sensitivity = HIGH;
int botao = 2;
unsigned long antes = 0;
unsigned long agora = 0;
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(botao), handler, HIGH);
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
   agora = millis();
  if(( agora - antes) > debounce_limit){
    antes = agora;
    return 1;
  }
  else {
    return 0;
  }
}
