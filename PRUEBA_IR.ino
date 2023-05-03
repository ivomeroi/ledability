int sensorPin = 2;   // define el pin donde está conectado el sensor
int ledPin = 4;     // define el pin donde está conectado el LED

void setup() {
  pinMode(sensorPin, INPUT);   // el pin del sensor es una entrada
  pinMode(ledPin, OUTPUT);     // el pin del LED es una salida
  Serial.begin(9600);          // inicia la comunicación serial a 9600 baudios
}

void loop() {
  int sensorValue = 0;
  sensorValue= digitalRead(sensorPin);  // lee el valor del sensor
  Serial.println(sensorPin);
  if(sensorValue == HIGH){                   // si el sensor detecta algo
    digitalWrite(ledPin, HIGH);              // enciende el LED
  } else {                                   // si el sensor no detecta nada
    digitalWrite(ledPin, LOW);               // apaga el LED
  }
  delay(50);
}
