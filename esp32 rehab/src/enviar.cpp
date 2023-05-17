#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include "recibir.h"
#include "sensor.h"
//--------------------Variables---------------------------------
esp_now_peer_info_t peerInfo; //Variable matriz que sirve para emparejar 1 a 1

uint8_t broadcastAddressMaster[6]={0x0C,0xB8,0x15,0xCB,0xEE,0x00}; //Dirección MAC del Master
                            
uint8_t slaveMACS[2][6]={
    {0x0C,0xB8,0x15,0xCB,0xFF,0x84}, //ESP2 - ID 1  //cambiar porque se quemaron los otros
    {0x0C,0xB8,0x15,0xCB,0xFA,0x1C} //ESP3 - ID 2
};

struct_message_to_master toMaster; //información que tengo que enviar al master.
//----------------Funciones peer---------------------------------
    void peering(){
        // Register peer
        memcpy(peerInfo.peer_addr,broadcastAddressMaster, 6); 
        peerInfo.channel = 0;  
        peerInfo.encrypt = false;
        // Add peer        
        if (esp_now_add_peer(&peerInfo) != ESP_OK){
            Serial.println("Failed to add ESP");
            return;
        } else{
            Serial.println("Added ESP");
    }
    } //Establezco la conectividad entre el Master y Slave. 
//--------------------Funcion onDatasent-------------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
} // Capaz descartar esta parte porque no se ejecuta. 
//--------------------Funcion defineID-------------------------------
void defID(){
    uint8_t mac[6];
    WiFi.macAddress(mac);
    for(int i=0; i<2; i++){
        if(memcmp(slaveMACS[i], mac, 6) == 0){ //Si es 0, memcmp dice que son iguales los valores de mac y la biblioteca de MACs
            toMaster.id=i+1;
        }
    }
} //función que asigna una ID a cada ESP. Comparo la MAC del propio ESP con el del banco de memoria. 
//--------------------Funcion enviar---------------------------------
void enviar(){
    esp_err_t result = esp_now_send(broadcastAddressMaster, (uint8_t *) &toMaster, sizeof(toMaster)); //enviar información toMaster al Master. 
}

