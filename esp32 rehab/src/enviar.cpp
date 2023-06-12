#include <WiFi.h>
#include <esp_now.h>
#include <cstring>
#include "counter.h"
#include "hc05.h"
#include "enviar.h"

//--------------------Variables---------------------------------
esp_now_peer_info_t peerInfo[3]; // Array de 2 para vincular los ESP slaves

uint8_t broadcastAddress[3][6] = {
    {0x0C, 0xB8, 0x15, 0xCB, 0xFF, 0x84}, // ESP2
    {0x0C, 0xB8, 0x15, 0xCB, 0xFA, 0x1C}, // ESP3
    {0x94, 0xE6, 0x86, 0x00, 0xEF, 0xEC}  // ESP4
};


//----------------Funciones peer---------------------------------
void peering()
{ // funcion de peer que empareja el ESPmaster con los slaves. peerInfo como matriz igual a la cantidad de ESPs slaves
    for (int i = 0; i < 3; i++)
    {
        memcpy(peerInfo[i].peer_addr, broadcastAddress[i], 6);
        peerInfo[i].channel = 0;
        peerInfo[i].encrypt = false;
        if (esp_now_add_peer(&peerInfo[i]) != ESP_OK)
        {
            return;
        }
    }
}
//--------------------Funcion checkID----------------------------
int checkID(const uint8_t *MACAddr)
{
    for (int i = 0; i < 3; i++)
    {
        if (memcmp(MACAddr, broadcastAddress[i], 6) == 0)
        {
            return i+1;
        }
    }
    return -1;
}
//--------------------Funcion enviar----------------------------------
void enviarMensaje(const uint8_t *MACAddr)
{
    if (randomValue==true){
        int numb = random(0, 10);
        enviar.patron = patron[numb]; // envio el elemento X (según en contador) del array patron
    }
    else{
        enviar.patron = patron[counter]; // envio el elemento X (según en contador) del array patron
    }
    enviar.color = BTmessage.color;  // cambiar a BTmessage.color con la App
    if (BTmessage.color == 4){
        enviar.color = color_counter;
        color_counter++;
        if (color_counter > 3){
            color_counter = 0;
        }
    } else if (BTmessage.color == 5){
        enviar.color = random(0, 4);
    }

    int padID = checkID(MACAddr);
    esp_now_send(MACAddr, (uint8_t *)&enviar, sizeof(enviar));
    writeBT(padID, enviar.patron, enviar.color);
    //--------------------Control de Counter--------------------------------
    counter++; //actualizo el valor del contador para que el proximo valor a enviar.
    if (counter>=strlen(patron)){ //controlo el contador. Si llega al final del array, lo reinicio y se repite el patron.
      counter=0;
    } 

}