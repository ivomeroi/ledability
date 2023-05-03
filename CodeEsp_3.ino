// CÓDIGO PARA EL ESP32 N° 3
#include <esp_now.h>
#include <WiFi.h>

// SEND
uint8_t MAC2[] = {0x0C, 0xB8, 0x15, 0xCB, 0xFF, 0x84};
int LEDCITO = 4;
int START = 15;
bool RcvNewDel2 = false;

// BOTH Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board
    int x;
    int y;
} struct_message;

// SEND Create a struct_message called myData
struct_message DatosMios3;

// RCV Create a structure to hold the readings from each board
struct_message board2;
// RCV Create an array with all the structures
struct_message boardsStruct[1] = {board2};//, board2, board3};


//SEND
esp_now_peer_info_t amigoInfo2;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// RCV callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  //get the board mac address
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  //copy from incoming data to mydata 
  memcpy(&DatosMios3, incomingData, sizeof(DatosMios3));
  Serial.printf("Board ID %u: %u bytes\n", DatosMios3.id, len);
  // Update the structures with the new incoming data
  boardsStruct[DatosMios3.id-1].x = DatosMios3.x;
  boardsStruct[DatosMios3.id-1].y = DatosMios3.y;
  Serial.printf("x value: %d \n", boardsStruct[DatosMios3.id-1].x);
  Serial.printf("y value: %d \n", boardsStruct[DatosMios3.id-1].y);
  Serial.println();

  bool RcvNewDel2 = true;
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(LEDCITO,OUTPUT);
  pinMode(START,INPUT);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing el ESP-NOW 3");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(amigoInfo2.peer_addr, MAC2, 6);
  amigoInfo2.channel = 0;  
  amigoInfo2.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&amigoInfo2) != ESP_OK){
    Serial.println("Failed to add peeramigo");
    return;
  }
 
  esp_now_register_recv_cb(OnDataRecv);
  
}

void loop() {
  int Q3envie = 0;
  int STARTstate = digitalRead(START);
  if (STARTstate==LOW){
    delay(550);}
    else{int Q3envie = 0; // cambio aquí
    delay(3500);
    while (digitalRead(START) == HIGH) { // agregar un bucle de espera para la presión del botón
      delay(100);
    }
    Q3envie = 1; // activar el envío de datos después de presionar el botón
    delay(1000); // agregar una pequeña pausa para evitar rebotes de botones
    
    delay(3500);
/////SEND
  // put your main code here, to run repeatedly:
  if (Q3envie==1){
  DatosMios3.id = 3;
  DatosMios3.x = random(3,50);
  DatosMios3.y = random(0,3);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(MAC2, (uint8_t *) &DatosMios3, sizeof(DatosMios3));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success OH FUCK YEAH");
  Q3envie =0;
  }
  else {
    Serial.println("Error sending the data CARAJO");
  }
  
  delay (10000);}
///// RCV
  while (Q3envie==0){
  if (RcvNewDel2 == true) {
      digitalWrite(LEDCITO,HIGH);
      RcvNewDel2 = false;
      delay (15000);
      for (int i =0; i<20; i++) {      
      digitalWrite(LEDCITO,!digitalRead(LEDCITO));
       delay(100);
       }
       digitalWrite(LEDCITO,LOW);
  }
  Q3envie==1; /// borrable)?
  }
}}
