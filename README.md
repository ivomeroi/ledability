# NeuroAbility KinePad
Bienvenido al repositorio GitHub del Proyecto KinePad para el centro de rehabilitación NeuroAbility. Este proyecto está diseñado para asistir en el tratamiento kinesiológico de pacientes con discapacidades neuromotoras.

Descripción
KinePad es un prototipo de un sistema de pads interactivos. Cada uno de los cuatro pads está equipado con sensores de proximidad y luces LED, y están interconectados mediante un módulo ESP32 o similar. Los pads se comunican de forma inalámbrica con una aplicación móvil que permite al terapista controlar y seleccionar diferentes programas adaptados a las necesidades del paciente.

Los programas incluyen secuencias de números, diferentes colores, y flechas en diferentes direcciones para guiar el movimiento y atención del paciente. El uso de este sistema proporciona una terapia personalizada, aumenta la motivación y compromiso del paciente, y se adapta a la evolución de la rehabilitación.

Librerías requeridas a instalar:
- adafruit/Adafruit NeoPixel@^1.11.0
-	plerup/EspSoftwareSerial@^8.0.3

Para obtener la dirección MAC de un ESP32 utilizando el Arduino IDE, sigue estos pasos:

1. Abre el Arduino IDE (o editor de código) y asegúrate de tener instalada la placa ESP32.
2. Crea un nuevo sketch o abre uno existente.
3. Copia y pega el siguiente código en el sketch:

   ```cpp
   #include <WiFi.h>

   void setup() {
     Serial.begin(115200);
     WiFi.begin();
     while (WiFi.status() != WL_CONNECTED) {
       delay(1000);
       Serial.println("Conectando a WiFi...");
     }
     Serial.print("Dirección MAC: ");
     Serial.println(WiFi.macAddress());
     byte mac[6];
     WiFi.macAddress(mac);
     Serial.print("Dirección MAC (formato de bytes): ");
     for (int i = 0; i < 6; ++i) {
       Serial.print(mac[i], HEX);
       if (i < 5) {
         Serial.print(":");
       }
     }
     Serial.println();
   }

   void loop() {
     // Tu código aquí
   }
