/*
 * Sistema Notificador de Llegada de Individuos
 * Autor: Jorge Enrique Aguado Guaní
*/
/* Creación de variables para los pines: */
#define buzzer 6
#define boton 2 //abrir/cerrar puerta
#define botonSecuencia 3  //cambiar secuencia rítmica de la alarma
#define led 7 //led inidicador de alarma activa

/* Variables para los leds del display */
#define leda 8
#define ledb 9
#define ledc 10
#define ledd 11
#define lede 12
#define ledg 5

boolean estadoBoton = false;
boolean estadoBoton2 = false;
int contador = 1; //tipo de ritmo secuencia

void setup() {
  pinMode(boton, INPUT);
  pinMode(botonSecuencia, INPUT);
  pinMode(buzzer, OUTPUT); //pin del buzzer como salida
  pinMode(led, OUTPUT); //pin del led como salida
  pinMode(leda, OUTPUT); //a display
  pinMode(ledb, OUTPUT); //b display
  pinMode(ledc, OUTPUT); //c display
  pinMode(ledd, OUTPUT); //d display
  pinMode(lede, OUTPUT); //e display
  pinMode(ledg, OUTPUT); //g display
  attachInterrupt(digitalPinToInterrupt(boton), interrupcion, RISING);
  attachInterrupt(digitalPinToInterrupt(botonSecuencia), cambioDeSecuencia, RISING);
  Serial.begin(9600);
  display1();
}

void loop() {
  if(contador == 1) {
    alarma1(); //activar alarma
  }
  else if(contador == 2) {
    alarma2();
  }
  else if(contador == 3) {
    alarma3();
  }
}

void alarma1() { //método para hacer sonar la alarma 1
  /*Secuencia o ritmo de la alarma: */
  noTone(buzzer);
  while(estadoBoton) {
    tone(buzzer, 1000); //enviar 1kHz de señal
    digitalWrite(led, HIGH);
    delay(100);         
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
    
    noTone(buzzer);
    digitalWrite(led, LOW);
    delay(100);
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó cualquier botón
  }
  estadoBoton2 = false;
}

void display1() {
  apagarLedsDisplay();
  digitalWrite(ledb, LOW);
  digitalWrite(ledc, LOW);
}

void alarma2() { //método para hacer sonar la alarma 2
  /*Secuencia o ritmo de la alarma 2: */
  noTone(buzzer);
  while(estadoBoton) {
    tone(buzzer, 980); //enviar 1kHz de señal
    digitalWrite(led, HIGH);
    delay(100);         
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
    
    noTone(buzzer);
    digitalWrite(led, LOW);
    delay(100);
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
    tone(buzzer, 1000); //enviar 1kHz de señal
    digitalWrite(led, HIGH);
    delay(100);         
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
    
    noTone(buzzer);
    digitalWrite(led, LOW);
    delay(1000);
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
  }
  estadoBoton2 = false;
}

void display2() {
  apagarLedsDisplay();
  digitalWrite(leda, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledg, LOW);
  digitalWrite(lede, LOW);
  digitalWrite(ledd, LOW);
}

void alarma3() { //método para hacer sonar la alarma 2
  /*Secuencia o ritmo de la alarma 3: */
  noTone(buzzer);
  while(estadoBoton) {
    tone(buzzer, 1000); //enviar 1kHz de señal
    digitalWrite(led, HIGH);
    delay(2000);         
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
    
    noTone(buzzer);
    digitalWrite(led, LOW);
    delay(2000);
    if(!estadoBoton || estadoBoton2) break; //comprobar si ya se presionó el botón
  }
  estadoBoton2 = false;
}

void display3() {
  apagarLedsDisplay();
  digitalWrite(leda, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledc, LOW);
  digitalWrite(ledd, LOW);
  digitalWrite(ledg, LOW);
}

void interrupcion() {
  noTone(buzzer);
  digitalWrite(led, LOW);
  //delay(100000);
  estadoBoton = !estadoBoton; //switchear el estado del boton
}

void apagarLedsDisplay() {
  for(int i = 8; i <= 12; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(ledg, HIGH);
}

void cambioDeSecuencia() {
  estadoBoton2 = true;  //botón 2 (cambio de secuencia presionado)
  contador++;
  if(contador > 3) contador = 1; //reiniciar conteo de secuencia de tono
  Serial.println(contador);
  if(contador == 1) display1();
  else if(contador == 2) display2();
  else if(contador == 3) display3();
}
