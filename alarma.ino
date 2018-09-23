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

/* Variable lógica para determinar si se ha pulsado el botón abrir/cerrar*/
boolean estadoBoton = false;

/* Variable para controlar el ritmo actual de la alarma*/
int ritmoAlarma = 1; //Tipo de ritmo secuencia

void setup() {
  pinMode(boton, INPUT); //Botón abrir/cerrar puerta como pin de entrada
  pinMode(botonSecuencia, INPUT); //Botón cambiar ritmo como pin de entrada
  pinMode(buzzer, OUTPUT); //Pin del buzzer como salida
  pinMode(led, OUTPUT); //Pin del led (inidicador) como salida
  pinMode(leda, OUTPUT); //a display
  pinMode(ledb, OUTPUT); //b display
  pinMode(ledc, OUTPUT); //c display
  pinMode(ledd, OUTPUT); //d display
  pinMode(lede, OUTPUT); //e display
  pinMode(ledg, OUTPUT); //g display
  attachInterrupt(digitalPinToInterrupt(boton), abrirCerrarPuerta, RISING);
  attachInterrupt(digitalPinToInterrupt(botonSecuencia), 
                  cambioDeSecuencia, 
                  RISING
                  );
  Serial.begin(9600);
  display1(); //Ritmo 1 predeterminado (ritmo inicial)
}

void loop() {
  while(estadoBoton) {
    if(ritmoAlarma == 1) {
      alarma1(); 
    }
    else if(ritmoAlarma == 2) {
      alarma2(); 
    }
    else if(ritmoAlarma == 3) {
      alarma3();
    }
    Serial.println("Estoy trabajando"); //el arduino está activo
  }
  Serial.println("Zzz..."); //El arduino está en modo bajo consumo
}

/* MÉTODOS PARA CADA RITMO DE LA ALARMA*/
void alarma1() { //Para hacer sonar la alarma 1
  /*Secuencia o ritmo de la alarma: */
  noTone(buzzer);
  tone(buzzer, 1000); //Enviar 1kHz de señal
  digitalWrite(led, HIGH);
  delay(100);         
  
  noTone(buzzer);
  digitalWrite(led, LOW);
  delay(100);
}

void alarma2() { //Para hacer sonar la alarma 2
  /*Secuencia o ritmo de la alarma 2: */
  noTone(buzzer);
  tone(buzzer, 950); //Enviar 950 Hz de señal
  digitalWrite(led, HIGH);
  delay(100);         
  
  noTone(buzzer);
  digitalWrite(led, LOW);
  delay(100);    
  tone(buzzer, 950);
  digitalWrite(led, HIGH);
  delay(100);             
  
  noTone(buzzer);
  digitalWrite(led, LOW);
  delay(400);
}

void alarma3() { //Para hacer sonar la alarma 3
  /*Secuencia o ritmo de la alarma 3: */
  noTone(buzzer);  
  tone(buzzer, 1000); //enviar 1kHz de señal
  digitalWrite(led, HIGH);
  delay(2000);         
  
  noTone(buzzer);
  digitalWrite(led, LOW);
  delay(2000);
}

/* MÉTODOS PARA MOSTRAR EN EL DISPLAY CADA NÚMERO*/
void display1() {
  apagarLedsDisplay();
  digitalWrite(ledb, LOW);
  digitalWrite(ledc, LOW);
}

void display2() {
  apagarLedsDisplay();
  digitalWrite(leda, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledg, LOW);
  digitalWrite(lede, LOW);
  digitalWrite(ledd, LOW);
}

void display3() {
  apagarLedsDisplay();
  digitalWrite(leda, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledc, LOW);
  digitalWrite(ledd, LOW);
  digitalWrite(ledg, LOW);
}

/* MÉTODO PARA APAGAR LOS LEDS DEL DISPLAY*/
void apagarLedsDisplay() {
  for(int i = 8; i <= 12; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(ledg, HIGH);
}

/*MÉTODOS DE LAS INTERRUPCIONES: */
void abrirCerrarPuerta() { //Botón 1 (abrir/cerrar puerta)
  noTone(buzzer);
  digitalWrite(led, LOW);
  estadoBoton = !estadoBoton; //Abrir/cerrar puerta
}

void cambioDeSecuencia() {
  ritmoAlarma++; //Cambia la secuencia rítmica
  if(ritmoAlarma > 3) ritmoAlarma = 1; //Reiniciar conteo de secuencia de tono
  if(ritmoAlarma == 1) display1();  //valor del display es el número de ritmo
  else if(ritmoAlarma == 2) display2();
  else if(ritmoAlarma == 3) display3();
}
