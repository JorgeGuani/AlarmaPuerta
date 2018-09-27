/* INSTITUTO TECNONÓGICO DE LEÓN
 * Práctica 2: Sistema Notificador de Llegada de Individuos
 * Fecha: 20 de septiembre de 2018
 * Docente: Ing. Levy Rojas Carlos Rafael
 * Autor: Jorge Enrique Aguado Guaní
 * 7° semestre
*/

/* Creación de variables para los pines: */
#define buzzer 5          //bocina
#define boton 2           //abrir/cerrar puerta
#define botonSecuencia 3  //cambiar secuencia rítmica de la alarma
#define ledAlarma 4       //led inidicador de alarma activa

/* Variables para los leds del display de 7 segmentos*/
#define leda 6    //a del display
#define ledb 7    //b del display
#define ledc 8    //c del display
#define ledd 9    //d del display
#define lede 10   //e del display
#define ledf 11   //f del display
#define ledg 12   //g del display

boolean estadoBoton = false;  //alternar entre abrir/cerrar
int ritmoAlarma = 1;          //tipo de ritmo secuencia
int numeroAleatorio;          //frecuencia alarma 4

void setup() {
  pinMode(boton, INPUT);
  pinMode(botonSecuencia, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledAlarma, OUTPUT);
  pinMode(leda, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ledc, OUTPUT);
  pinMode(ledd, OUTPUT);
  pinMode(lede, OUTPUT);
  pinMode(ledf, OUTPUT);
  pinMode(ledg, OUTPUT);
  
  //Interrupciones para cada botón
  attachInterrupt(digitalPinToInterrupt(boton), 
                  abrirCerrarPuerta, 
                  RISING);
                  
  attachInterrupt(digitalPinToInterrupt(botonSecuencia), 
                  cambioDeSecuencia, 
                  RISING); 
                                 
  Serial.begin(9600);   //ajustar el monitor serie a 9600
  apagarLedsDisplay();  //limpia el display
  display1();           //ritmo 1 predeterminado (ritmo inicial)
}


void loop() {
  while(estadoBoton) { //Mientras esté activa la alarma
    switch(ritmoAlarma) { //irá al número de ritmo correspondiente
      case 1:
        alarma1();
        break;
        
      case 2:
        alarma2();
        break;
        
      case 3:
        alarma3();
        break;
        
      case 4:
        alarma4();
        break;  
    }
    Serial.println("Estoy trabajando"); //el arduino está activo
  }
  Serial.println("Zzz..."); //El arduino está en modo bajo consumo
}


/* MÉTODOS PARA CADA RITMO DE LA ALARMA */
void alarma1() {    //para hacer sonar la alarma 1
  /*Secuencia o ritmo de la alarma 1: */
  noTone(buzzer);
  tone(buzzer, 1000);             //enviar 1kHz de señal
  digitalWrite(ledAlarma, HIGH);
  delay(100);         
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(100);
}

void alarma2() {    //para hacer sonar la alarma 2
  /*Secuencia o ritmo de la alarma 2: */
  noTone(buzzer);
  tone(buzzer, 950);
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

void alarma3() {  //Para hacer sonar la alarma 3
  /*Secuencia o ritmo de la alarma 3: */
  noTone(buzzer);  
  tone(buzzer, 1000);   //enviar 1kHz de señal
  digitalWrite(ledAlarma, HIGH);
  delay(2000);         
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(2000);
}

void alarma4() { //Para hacer sonar la alarma 4
  /*Secuencia o ritmo de la alarma 4 (melodía): */
  randomSeed(analogRead(0)); // genera una semilla para el núm. aleatorio
  numeroAleatorio = random(523, 1479); //para la frecuencia
  
  noTone(buzzer);  
  tone(buzzer, numeroAleatorio);       //frecuencia aleatoria
  digitalWrite(ledAlarma, HIGH);
  delay(map(numeroAleatorio, 523, 1479, 200, 500)); //duración aleatoria        
  
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  delay(map(numeroAleatorio, 523, 1479, 200, 400)); //espera aleatoria        
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

void display4() {
  digitalWrite(ledf, LOW);
  digitalWrite(ledg, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ledc, LOW);
}

/* MÉTODO PARA APAGAR LOS LEDS DEL DISPLAY*/
void apagarLedsDisplay() {
  for(int i = 6; i <= 12; i++) {
    digitalWrite(i, HIGH);
  }
}

/*MÉTODOS DE LAS INTERRUPCIONES: */
/*Interrupción 1*/
void abrirCerrarPuerta() { //Botón 1 (abrir/cerrar puerta)
  noTone(buzzer);
  digitalWrite(ledAlarma, LOW);
  estadoBoton = !estadoBoton; //Abrir/cerrar puerta
}

/*Interrupción 2*/
void cambioDeSecuencia() {
  ritmoAlarma++;          //cambia la secuencia rítmica
  if(ritmoAlarma > 4) ritmoAlarma = 1;  //reiniciar conteo de secuencia de tono 
   
  apagarLedsDisplay();    //limpia el display

  switch(ritmoAlarma) {   //el valor del display es el número de ritmo
    case 1:
      display1();
      break;

    case 2:
      display2();
      break;

    case 3:
      display3();
      break;

    case 4:
      display4();
      break;
  }
}
