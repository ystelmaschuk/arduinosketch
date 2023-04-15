// Оголошення змінних
volatile int hallSensor1 = 2;  // Пін для датчика Hall
volatile int counter = 0;      // Лічильник обертів колінвала
unsigned long lastTime = 0;    // Останній час вимірювання обертів
unsigned long rpm = 0;         // Кількість обертів колінвала на хвилину

void setup() {
  // Ініціалізація піна датчика Hall як вхід з підтримкою внутрішнього pull-up резистора
  pinMode(hallSensor1, INPUT_PULLUP);
  
  // Ініціалізація зв'язку з монітором порту (Seriak Monitor)
  Serial.begin(9600);

  // Встановлення функції, яка буде виконуватися при зміні стану піна датчика Hall
  attachInterrupt(digitalPinToInterrupt(hallSensor1), countPulses, FALLING);
}

void loop() {
  // Вимірювання кількості обертів колінвала на хвилину кожну секунду
  if (millis() - lastTime >= 1000) {
    // Вимірювання кількості обертів колінвала на хвилину
    rpm = counter * 60 / 2;  //!!!! ОБЕРТИ НА ХВИЛИНУ
    
    // Виведення результатів в монітор порту
    Serial.print("RPM = ");
    Serial.println(rpm);
    
    // Скидання лічильника обертів колінвала
    counter = 0;
    
    // Оновлення часу вимірювання
    lastTime = millis();
  }
}

// Функція, яка викликається при зміні стану піна датчика Hall
void countPulses() {
  // Якщо спрацьовував датчик Hall 1, збільшити лічильник обертів колінвала
  if (digitalRead(hallSensor1) == LOW) {
    counter++;
  }
}
