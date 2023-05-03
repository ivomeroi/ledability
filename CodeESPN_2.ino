// CÓDIGO PARA EL ESP32 N° 2
#include <esp_now.h>
#include <WiFi.h>

// SEND
uint8_t MAC3[] = {0x0C, 0xB8, 0x15, 0xCB, 0xFA, 0x1C};
int LEDA = 4;
bool RcvNewDel3 = false;

// BOTH Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board
    int x;
    int y;
} struct_message;

// SEND Create a struct_message called myData
struct_message DatosMios2;

// RCV Create a structure to hold the readings from each board
struct_message board3;
// RCV Create an array with all the structures
struct_message boardsStruct[1] = {board3};//, board2, board3};


//SEND
esp_now_peer_info_t amigoInfo3;

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
  memcpy(&DatosMios2, incomingData, sizeof(DatosMios2));
  Serial.printf("Board ID %u: %u bytes\n", DatosMios2.id, len);
  // Update the structures with the new incoming data
  boardsStruct[DatosMios2.id-1].x = DatosMios2.x;
  boardsStruct[DatosMios2.id-1].y = DatosMios2.y;
  Serial.printf("x value: %d \n", boardsStruct[DatosMios2.id-1].x);
  Serial.printf("y value: %d \n", boardsStruct[DatosMios2.id-1].y);
  Serial.println();

  RcvNewDel3 = true;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
   pinMode(LEDA,OUTPUT);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing el ESP-NOW 3");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(amigoInfo3.peer_addr, MAC3, 6);
  amigoInfo3.channel = 1;
  amigoInfo3.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&amigoInfo3) != ESP_OK){
    Serial.println("Failed to add peeramigo");
    return;
  }
 
  esp_now_register_recv_cb(OnDataRecv);
  
}

void loop() {
///// RCV
  int Q2envie = 0;
  while (Q2envie == 0); {
    if (RcvNewDel3 == true) {
      LEDA = HIGH;
      RcvNewDel3 == false;
      Q2envie == 1;
      delay (15000);  ////
  }}
/////SEND
  // put your main code here, to run repeatedly:
  if (Q2envie ==1) {
  DatosMios2.id = 2;
  DatosMios2.x = random(0,3);
  DatosMios2.y = random(3,50);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(MAC3, (uint8_t *) &DatosMios2, sizeof(DatosMios2));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success OH FUCK YEAH");
  }
  else {
    Serial.println("Error sending the data CARAJO");
  }
    Q2envie==0; ///borrable)?
  delay (10000);

}}
