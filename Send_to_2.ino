#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddressUNO[] = {0x0C, 0xB8, 0x15, 0xCB, 0xEE, 0x00};

uint8_t broadcastAddressTRES[] = {0x0C, 0xB8, 0x15, 0xCB, 0xFA, 0x1C};
 

// Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board
    int x;
    int y;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t amigoInfo1;
esp_now_peer_info_t amigoInfo3;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(amigoInfo1.peer_addr, broadcastAddressUNO, 6);
  amigoInfo1.channel = 0;  
  amigoInfo1.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&amigoInfo1) != ESP_OK){
    Serial.println("Failed to add peeramigo1");
    return;
  }
  memcpy(amigoInfo3.peer_addr, broadcastAddressTRES, 6);
  amigoInfo3.channel = 1;  
  amigoInfo3.encrypt = false;
  
  if (esp_now_add_peer(&amigoInfo3) != ESP_OK){
    Serial.println("Failed to add peeramigo3");
    return;
  }
}
 
void loop() {
  // Set values to send
  myData.id = 2;
  myData.x = random(0,2);
  myData.y = random(0,50);


  esp_err_t result1 = esp_now_send(broadcastAddressUNO, (uint8_t *) &myData, sizeof(myData));
   
  if (result1 == ESP_OK) {
    Serial.println("Sent with success OH FUCK YEAH1");
  }
  else {
    Serial.println("Error sending the data CARAJO1");
  }
  delay(8000);

  esp_err_t result2 = esp_now_send(broadcastAddressTRES, (uint8_t *) &myData, sizeof(myData));
   
  if (result2 == ESP_OK) {
    Serial.println("Sent with success OH FUCK YEAH3");
  }
  else {
    Serial.println("Error sending the data CARAJO3");
  }
  delay(8000);
  
}
