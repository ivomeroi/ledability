#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x0C,0xB8,0x15,0xCB,0xFF,0x84}; //va al ESP32 - 2

// Must match the receiver structure
typedef struct struct_message1 {
    int id; // must be unique for each sender board
    char x;
    int y;
} struct_message1;

// Create a struct_messag1e called myData
struct_message1 myData;

int flag;
// Create peer interface
esp_now_peer_info_t amigoInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 


void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  //get the board mac address
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  //-------------------------------------------------------------
  //copy from incoming bool to falg 
  memcpy(&flag, incomingData, sizeof(flag));
  //-------------------------------------------------------------
  Serial.println(flag, DEC);
}


void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing el coso este ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_recv_cb(OnDataRecv);

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(amigoInfo.peer_addr, broadcastAddress, 6);
  amigoInfo.channel = 0;  
  amigoInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&amigoInfo) != ESP_OK){
    Serial.println("Failed to add peeramigo");
    return;
  }
}
 
void loop() {
  // Set values to send
  myData.id = 2;
  myData.x = 'd';
  myData.y = random(0,2);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success OH FUCK YEAH");
  }
  else {
    Serial.println("Error sending the data CARAJO");
  }
  Serial.println(myData.id);
  Serial.println(myData.x);
  Serial.println(myData.y);
  Serial.println(flag);  
  
  delay(3000);
}
