#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "enviar.h"
#include "recibir.h"
#include <hc05.h>
#include <counter.h>
//--------------------Variables---------------------------------
esp_now_peer_info_t peerInfo[3]; //Array de 2 para vincular los ESP slaves

uint8_t broadcastAddress[3][6]={
    {0x0C,0xB8,0x15,0xCB,0xFF,0x84}, //ESP2 
    {0x0C,0xB8,0x15,0xCB,0xFA,0x1C}, //ESP3
    {0x94,0xE6,0x86,0x00,0xEF,0xEC}  //ESP4
};

struct_send enviar; //estructura de datos que contiene el patron y el color

struct_BTmessage BTmessage;

int counter;

//----------------Funciones peer---------------------------------
void peering() { //funcion de peer que empareja el ESPmaster con los slaves. peerInfo como matriz igual a la cantidad de ESPs slaves
    for (int i = 0; i < 3; i++) {
        memcpy(peerInfo[i].peer_addr, broadcastAddress[i], 6); 
        peerInfo[i].channel = 0;
        peerInfo[i].encrypt = false;
        if (esp_now_add_peer(&peerInfo[i]) != ESP_OK) {
        return;
        }
    }
}
void checkID(const uint8_t *MACAddr) {
    for (int i = 0; i < 3; i++) {
        if(memcmp(MACAddr, broadcastAddress[i], 6)==0){
            Serial.print(i+1);
        }
    }
}
//--------------------Funcion enviar----------------------------------
void enviarMensaje(const uint8_t *MACAddr) {
    
    enviar.patron=patron[counter]; //envio el elemento X (según en contador) del array patron
    enviar.color= BTmessage.color; //cambiar a BTmessage.color con la App
    checkID(MACAddr);
    Serial.print(patron[counter]);
    Serial.print(BTmessage.color);

    esp_now_send(MACAddr, (uint8_t *) &enviar, sizeof(enviar));


}