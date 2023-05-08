#include <esp_now.h>
#include <WiFi.h>
#include <macaddresses.h>

uint8_t UNIV[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t MAC1[6]={0x0C,0xB8,0x15,0xCB,0xEE,0x00};
uint8_t MAC2[6]={0x0C,0xB8,0x15,0xCB,0xFF,0x84};
uint8_t MAC3[6]={0x0C,0xB8,0x15,0xCB,0xFA,0x1C};

// Must match the receiver structure
typedef struct struct_message1 {
    int id; // must be unique for each sender board
    char x;
    int y;
} struct_message1;

char POSICIONES[4]={'u','d','l','r'} //arriba, abajo, izquierda, derecha

// Create a struct_messag1e called myData
struct_message myData;

struct_message SlaveMacs[3]={MAC2,MAC3,UNIV};

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
  memcpy(&flag, incomingData, sizeof(flag));     // si hay objeto el flag pasaría a 0. 
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
  peering();

}
 
void loop() {
  // Set values to send
  for (int i = 0; i < 3; i++) {
    myData.id = i;
    myData.x = POSICIONES[random(0,4)];
    myData.y = random(0,3);

  // Send message via ESP-NOW
  esp_err_t result;
  result = esp_now_send(SlaveMacs[i], (uint8_t *) &myData, sizeof(myData));
   
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
}