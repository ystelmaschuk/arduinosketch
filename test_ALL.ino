#include <TimeLib.h> // Підключення бібліотеки TimeLib.h
#include <avr/wdt.h> // додайте бібліотеку

volatile int hallSensor1 = 2;  // Пін для датчика Hall
volatile int counter = 0;      // Лічильник обертів колінвала
unsigned long lastTime = 0;    // Останній час вимірювання обертів
unsigned long rpm = 0;         // Кількість обертів колінвала на хвилину


//const int hallSensor1 = 2; // пін для датчика холлу 1
const int hallSensor2 = 3; // пін для датчика холлу 2
const int hallSensor3 = 4; // пін для датчика холлу 3
const int hallSensor4 = 5; // пін для датчика холлу 4
const int hallSensor5 = 6; // пін для датчика холлу 5
const int hallSensor6 = 7; // пін для датчика холлу 6

const int ignition1 = 8; // пін для катушки запалення 1
const int ignition2 = 9; // пін для катушки запалення 2
const int ignition3 = 10; // пін для катушки запалення 3
const int ignition4 = 11; // пін для катушки запалення 4
const int ignition5 = 12; // пін для катушки запалення 5
const int ignition6 = 13; // пін для катушки запалення 6

int hallValue1 = 0;
int hallValue2 = 0;
int hallValue3 = 0;
int hallValue4 = 0;
int hallValue5 = 0;
int hallValue6 = 0;

int delayTime1 = 0;
int delayTime2 = 0;
int delayTime3 = 0;
int delayTime4 = 0;
int delayTime5 = 0;
int delayTime6 = 0;


int previousMillis1 = 0;
int previousMillis2 = 0;
int previousMillis3 = 0;
int previousMillis4 = 0;
int previousMillis5 = 0;
int previousMillis6 = 0;
int potentiometerValue = 0;
const int potentiometerPin = A0;
const int minValue = 1;
const int maxValue = 1000;

void setup() {

  wdt_enable(WDTO_2S); // ПЕРШИЙ в войді!!! таймер сторожового догляду на 2 секунди

    
    // Встановлення функції, яка буде виконуватися при зміні стану піна датчика Hall
  attachInterrupt(digitalPinToInterrupt(hallSensor1), countPulses, FALLING);
}

  
  
  
  pinMode(hallSensor1, INPUT_PULLUP);
  pinMode(hallSensor2, INPUT_PULLUP);
  pinMode(hallSensor3, INPUT_PULLUP);
  pinMode(hallSensor4, INPUT_PULLUP);
  pinMode(hallSensor5, INPUT_PULLUP);
  pinMode(hallSensor6, INPUT_PULLUP);

  pinMode(ignition1, OUTPUT);
  pinMode(ignition2, OUTPUT);
  pinMode(ignition3, OUTPUT);
  pinMode(ignition4, OUTPUT);
  pinMode(ignition5, OUTPUT);
  pinMode(ignition6, OUTPUT);

  Serial.begin(9600); 
}

void loop() {

  wdt_reset();  // Скидаємо сторожовий таймер
  
  
  hallValue1 = digitalRead(hallSensor1);
  hallValue2 = digitalRead(hallSensor2);  
  hallValue3 = digitalRead(hallSensor3);
  hallValue4 = digitalRead(hallSensor4);
  hallValue5 = digitalRead(hallSensor5);
  hallValue6 = digitalRead(hallSensor6);


  potentiometerValue = analogRead(potentiometerPin);

  // delayTime1 = ((potentiometerValue - 0) * (maxValue - minValue)) / (1023 - 0) + minValue;

 delayTime1 = map(potentiometerValue, 0, 1023, minValue, maxValue);  // ВИБРАТИ ЦЮ ФОРМУЛУ АБО ПОПЕРЕДНЮ
   delayTime2 = delayTime1;
  delayTime3 = delayTime1;
   delayTime4 = delayTime1;
  delayTime5 = delayTime1;
   delayTime6 = delayTime1;
   
  unsigned long currentMillis = millis ()*1000;  // перетворено в МІКРОСЕКУНДИ

   if (hallValue1 == HIGH && currentMillis - previousMillis1 >= delayTime1) {
    digitalWrite(ignition1, HIGH);
    previousMillis1 = currentMillis;
   } else {
    digitalWrite(ignition1, LOW); 
  }

  if (hallValue2 == HIGH && currentMillis - previousMillis2 >= delayTime2) {
    digitalWrite(ignition2, HIGH);
    previousMillis2 = currentMillis;     
  } else {
    digitalWrite(ignition2, LOW);
  }

  if (hallValue3 == HIGH && currentMillis - previousMillis3 >= delayTime3) {
digitalWrite(ignition3, HIGH);
previousMillis3 = currentMillis;
} else {
digitalWrite(ignition3, LOW); 
}

 if (hallValue4 == HIGH && currentMillis - previousMillis4 >= delayTime4) {
    digitalWrite(ignition4, HIGH);
    previousMillis4 = currentMillis;
  } else {
    digitalWrite(ignition4, LOW);
  }
   if (hallValue5 == HIGH && currentMillis - previousMillis5 >= delayTime5) {
    digitalWrite(ignition5, HIGH);
    previousMillis5 = currentMillis;
  } else {
    digitalWrite(ignition5, LOW);
  }
   if (hallValue6 == HIGH && currentMillis - previousMillis6 >= delayTime6) {
    digitalWrite(ignition6, HIGH);
    previousMillis6 = currentMillis;
  } else {
    digitalWrite(ignition6, LOW);

  }

// Функція, яка викликається при зміні стану піна датчика Hall
void countPulses() {
  // Якщо спрацьовував датчик Hall 1, збільшити лічильник обертів колінвала
  if (digitalRead(hallSensor1) == LOW) {
    counter++;
  
  // Перевіряємо, чи був перезапуск від сторожового таймера 
  if (bit_is_set(MCUSR, WDRF)) {
    Serial.println("Перезапуск плати Arduino через сторожовий таймер!");//!!!!! ЗАБРАТИ ПРИ РОБОТІ!!!!!
    // Очищуємо флаг перезапуску від сторожового таймера
    MCUSR &= ~(1<<WDRF);
  }
  
  
  }    
