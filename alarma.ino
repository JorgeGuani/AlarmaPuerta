/* INSTITUTO TECNONÓGICO DE LEÓN
 * Práctica 2: Sistema Notificador de Llegada de Individuos
 * Fecha: 20 de septiembre de 2018
 * Docente: Ing. Levy Rojas Carlos Rafael
 * Autor: Jorge Enrique Aguado Guaní
 * 7° semestre
*/

/***************************VARIABLES***************************/
/* Creación de variables para los pines: */
#define buzzer 6 //bocina
#define boton 2 //abrir/cerrar puerta
#define botonSecuencia 3  //cambiar secuencia rítmica de la alarma
#define ledAlarma 7 //led inidicador de alarma activa

/* Variables para los leds del display de 7 segmentos*/
#define leda 8  //a del display
#define ledb 9  //b del display
#define ledc 10 //c del display
#define ledd 11 //d del display
#define lede 12 //e del display
#define ledg 5  //g del display

boolean estadoBoton = false; //alternar entre abrir/cerrar
int ritmoAlarma = 1; //tipo de ritmo secuencia
/****************************************************************/


/*********************CONFIGURACIÓN INICIAL**********************/
void setup() {
  //Pines de entrada y salida
  pinMode(boton, INPUT);
  pinMode(botonSecuencia, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledAlarma, OUTPUT);
  pinMode(leda, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ledc, OUTPUT);
  pinMode(ledd, OUTPUT);
  pinMode(lede, OUTPUT);
  pinMode(ledg, OUTPUT);
  
  //Interrupciones para cada botón
  attachInterrupt(digitalPinToInterrupt(boton), 
                  abrirCerrarPuerta, 
                  RISING);
  attachInterrupt(digitalPinToInterrupt(botonSecuencia), 
                  cambioDeSecuencia, 
                  RISING); 
                                 
  Serial.begin(9600); //ajustar el monitor serie a 9600
  apagarLedsDisplay(); //limpia el display
  display1(); //ritmo 1 predeterminado (ritmo inicial)
}
/*****************************************************************/


/*********************ESTRUCTURA FUNCIONAL**********************/
void loop() {
  while(estadoBoton) { //Mientras esté activa la alarma
    if(ritmoAlarma == 1) { //Si está activo el ritmo 1
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

/* MÉTODOS PARA CADA RITMO DE LA ALARMA */
void alarma1() { //para hacer sonar la alarma 1
  /*Secuencia o ritmo de la alarma 1: */
  noTone(buzzer);
  tone(buzzer, 1000); //enviar 1kHz de señal
  digitalWrite(ledAlarma, HIGH);
  delay(100);         
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(100);
}

void alarma2() { //para hacer sonar la alarma 2
  /*Secuencia o ritmo de la alarma 2: */
  noTone(buzzer);
  tone(buzzer, 950); //enviar 950 Hz de señal
  digitalWrite(ledAlarma, HIGH);
  delay(100);         
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(100);    
  tone(buzzer, 950);
  digitalWrite(ledAlarma, HIGH);
  delay(100);             
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(400);
}

void alarma3() { //Para hacer sonar la alarma 3
  /*Secuencia o ritmo de la alarma 3: */
  noTone(buzzer);  
  tone(buzzer, 1000); //enviar 1kHz de señal
  digitalWrite(ledAlarma, HIGH);
  delay(2000);         
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(2000);
}

/* MÉTODOS PARA MOSTRAR EN EL DISPLAY CADA NÚMERO*/
void display1() {
  digitalWrite(ledb, LOW);
  digitalWrite(ledc, LOW);
}

void display2() {
  digitalWrite(leda, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledg, LOW);
  digitalWrite(lede, LOW);
  digitalWrite(ledd, LOW);
}

void display3() {
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
  digitalWrite(ledAlarma, LOW);
  estadoBoton = !estadoBoton; //Abrir/cerrar puerta
}

void cambioDeSecuencia() {
  ritmoAlarma++; //cambia la secuencia rítmica
  if(ritmoAlarma > 3) ritmoAlarma = 1; //reiniciar conteo de secuencia de tono
  
  apagarLedsDisplay(); //limpia el display
  
  if(ritmoAlarma == 1) display1();  //valor del display es el número de ritmo
  else if(ritmoAlarma == 2) display2();
  else if(ritmoAlarma == 3) display3();
}
/********************************************************************************/
