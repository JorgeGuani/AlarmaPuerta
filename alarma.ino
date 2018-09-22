/*
 * Sistema Notificador de Llegada de Individuos
 * Autor: Jorge Enrique Aguado Guaní
*/

/* Creación de variables para los pines: */
#define buzzer 6
#define boton 2
#define led 3

boolean estadoBoton = false;

void setup() {
  pinMode(boton, INPUT);
  pinMode(buzzer, OUTPUT); //pin del buzzer como salida
  attachInterrupt(digitalPinToInterrupt(boton), interrupcion, RISING);
  Serial.begin(9600);
}

void loop() {
  alarma(); //activar alarma
}

void alarma() { //método para hacer sonar la alarma
  /*Secuencia o ritmo de la alarma: */
  while(estadoBoton) {
    tone(buzzer, 1000); //enviar 1kHz de señal
    delay(100);         
    noTone(buzzer);
    delay(100);
  }
}

void interrupcion() {
  delay(100000);
  estadoBoton = !estadoBoton; //switchear el estado del boton
}
