#include <Keypad.h>
#include "RTClib.h"
RTC_DS3231 rtc;
String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" }; //seteo los dias de la semana 
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" }; //seteo los meses
int LedRojo = 13; // pin de la luz roja
int LedVerde = 10; // pin de la luz verde
const byte Filas = 3; //tamaño de teclado 3x3
const byte Columna = 3; //tamaño de teclado 3x3
char keys[Filas][Columna] = {
  {'7','8','9'},
  {'4','5','6'},
  {'1','2','3'}};  //valores para toda la matriz del teclado
byte Filapins[Filas] = {12,11,8};//Defino los pines  para las filas 
byte ColumnaPins[Columna] = {6,5,4};//Defino los pines para la columna
Keypad keypad = Keypad( makeKeymap(keys), Filapins, ColumnaPins,Filas, Columna);  //objeto tipo keypad, configurando el mapeo de teclas y el tamaño del teclado

int valor; //la declaro para poder guardarla cuando presione un numero con el teclado
int contador = 0; // variable para tener cuantas veces fue apretandose el teclado para sacar el promedio
int sumatoria = 0; // variable para el promedio y la sumatoria de las veces que se fue ingresando un numero
void setup() {

    if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
   // Si se ha perdido la corriente, fijar fecha y hora
   if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Utilizo la fecha y hora de la computadora, del reloj integrado
      }
  pinMode(LedRojo, OUTPUT); // pone el pinLedR como output
  pinMode(LedVerde, OUTPUT); // pone el pinLedV como output
  Serial.begin (9600); //para utilizar la terminal
}

void loop() {
  char key = keypad.getKey(); //guardo lo que se presiono por teclado
  DateTime now = rtc.now(); //aca inicio un objeto tipo reloj
  if(key) {
    switch (key){
    case '1':        
    valor = 1; //guardo lo que se ingreso por teclado en una variable
    break;
    case '2':        
    valor = 2; //guardo lo que se ingreso por teclado en una variable
    break;
    case '3':        
    valor = 3; //guardo lo que se ingreso por teclado en una variable
    break;
    case '4':        
    valor = 4; //guardo lo que se ingreso por teclado en una variable
    break;
    case '5':        
    valor = 5; //guardo lo que se ingreso por teclado en una variable
    break;
    case '6':        
    valor = 6; //guardo lo que se ingreso por teclado en una variable
    break;
    case '7':        
    valor = 7; //guardo lo que se ingreso por teclado en una variable
    break;
    case '8':        
    valor = 8; //guardo lo que se ingreso por teclado en una variable
    break;
    case '9':        
    valor = 9; //guardo lo que se ingreso por teclado en una variable
    break;
    }
   fecha(now); // hago uso de la funcion siempre que se presione una tecla
   paridad(); // hago uso de la funcion siempre que se presione una tecla
   binario(valor); // hago uso de la funcion siempre que se presione una tecla
   promedio(); // hago uso de la funcion siempre que se presione una tecla
}

}

void fecha(DateTime date){
   Serial.print("Se presiono la tecla el dia: ");
   Serial.print(date.day(), DEC);
   Serial.print('/');
   Serial.print(date.month(), DEC);
   Serial.print('/');
    Serial.print(date.year(), DEC);
   Serial.print(" a las ");
   Serial.print(date.hour(), DEC);
   Serial.print(':');
   Serial.print(date.minute(), DEC);
   Serial.print(':');
   Serial.print(date.second(), DEC);
   Serial.println();
}
void binario(int valor){
  Serial.print("el valor en binario es: ");
  Serial.print(valor, BIN); // imprime el valor en binario
  Serial.println();
  Serial.print("el valor en hexadecimal es: ");
  Serial.print(valor, HEX);  // imprime el valor en hexadecimal
  Serial.println();
  Serial.print("El valor en octal es: ");
  Serial.print(valor, OCT); // imprime el valor en octal
  Serial.println();
  byte complemento1 = ~valor ; // Obtiene el complemento a 1 en forma de byte
  byte complemento2 = ~valor + 1 ; //Obtengo el complemento a 2 en forma de byte
  Serial.print("El valor en complemento a 1 es: ");
  Serial.print(complemento1, BIN); // Imprime los byte transformandolo en binario y tenemos el complemento a 1
  Serial.println();
  Serial.print("El valor en complemento a 2 es: "); 
  Serial.print(complemento2, BIN); // imprime los byte transformandolo en binario y tenemos el complemento a2
  Serial.println();
}
void paridad(){
   int resto = valor % 2; //obtengo el resto del valor guardado en la variable valor
   if(resto==1){ //si el resultado es 1 es impar y si es 0 es par
    analogWrite(LedRojo, 255);  //Prendo la luz roja
    Serial.print("El numero ingresado es impar");
    Serial.println();
    delay(500); //retardo antes de apagar 
    analogWrite(LedRojo, 0); //apago la luz roja
    }else{
      analogWrite(LedVerde, 255); //Prendo la luz verde
      Serial.print("El numero ingresado es par");
      Serial.println();
      delay(500); //retardo antes de apagar 
      analogWrite(LedVerde, 0); //apago la luz verde
      }
}
void promedio(){
   contador++; //incremento de a 1
   sumatoria = sumatoria + valor; //sumo todos los valores que se estan ingresando por teclado
   Serial.print("Sumatoria total: ");
   Serial.print(sumatoria); //Imprimo la suma de los valores que se van ingresando 
   Serial.println();
   Serial.print("Cantidad total de numeros ingresado: ");
   Serial.print(contador); //imprimo la cantidad de numeros que fueron ingresandose utilizando el contador
   Serial.println();
   Serial.print("Promedio: ");
   Serial.println(sumatoria / contador); //saco el promedio con la suma total / la cantidad de veces que se ingreso un numero
   Serial.println();
}

