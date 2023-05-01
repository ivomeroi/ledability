#include <esp_now.h>
#include <WiFi.h>

int LEDCITO =15;
int LEDA =4;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int x;
  int y;
}struct_message;

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board2;
//struct_message board2;
//struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[1] = {board2};//, board2, board3};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  //get the board mac address
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  //copy from incoming data to mydata 
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].x = myData.x;
  boardsStruct[myData.id-1].y = myData.y;
  Serial.printf("x value: %d \n", boardsStruct[myData.id-1].x);
  Serial.printf("y value: %d \n", boardsStruct[myData.id-1].y);

  // check the received value
  if (myData.x == 1) {
    digitalWrite(LEDCITO, HIGH);  // turn on LEDCITO pin
    delay(6000); // wait for 6 seconds
    digitalWrite(LEDCITO, LOW);  // turn off LEDCITO pin
  } else if (myData.x == 0) {
    digitalWrite(LEDA, HIGH);  // turn on LEDA pin
    delay(6000); // wait for 6 seconds
    digitalWrite(LEDA, LOW);  // turn off LEDA pin
  }
  
  Serial.println();
}
 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(LEDCITO,OUTPUT);
  pinMode(LEDA,OUTPUT);
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);


  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing este 1 ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Acess the variables for each board
  int board1X = boardsStruct[myData.id-1].x;
  int board1Y = boardsStruct[myData.id-1].y;
  
}
