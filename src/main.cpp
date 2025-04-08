#include <Arduino.h>
#include <SelectionDeLaVoie.h>
#include "IHM.h"


#define BUS_MUX0 18 //Choisi au hasard, à mettre les bonnes pin par rapport au kicad
#define BUS_MUX1 19
#define BUS_MUX2 33

#define EN_MUX0 16   // EN_MUX0 → GPIO16
#define EN_MUX1 17   // EN_MUX1 → GPIO17
#define EN_MUX2 25   // EN_MUX2 → GPIO33
#define EN_MUX3 26   // EN_MUX3 → GPIO25
#define EN_MUX4 27   // EN_MUX4 → GPIO26
#define EN_MUX5 32   // EN_MUX5 → GPIO35


unsigned long tempsEchantillonagePrecedent = 0;
unsigned long tempsEchantillonage = 1000; //En milliseconde

int compteurTemps = 0;

void setup() {
    Serial.begin(115200);

    // Define the bus and enable structures
    SelectionDeLaVoieBUS bus = {BUS_MUX0, BUS_MUX1, BUS_MUX2}; // Example pins for bus
    SelectionDeLaVoieENABLEMUX enable = {EN_MUX0, EN_MUX1, EN_MUX2, EN_MUX3, EN_MUX4, EN_MUX5}; // Example pins for enable

    // Create an instance of SelectionDeLaVoie
    SelectionDeLaVoie selection(bus, enable);
    initIHM(); // Initialize the IHM
    // Test printMidOLED
    printMidOLED("Bonjour\nSalut");
    delay(2000); // attendre 2 secondes

    
    // Test selectionVoie
    Serial.println("Testing selectionVoie sur voie 10...");
    
    selection.selectionVoie(10); // Example voie


}

void loop() {
    if((millis() - tempsEchantillonagePrecedent) >= tempsEchantillonage){
        //Si le temps d'échantillonage est écoulé, soit ici une seconde
        tempsEchantillonagePrecedent = millis();//En milliseconde

        compteurTemps++;
        Serial.printf("compteurTemps : %d", compteurTemps);
        if(compteurTemps >= 5){
            compteurTemps = 0;
            Serial.println("5 secondes écoulées");
        }

    }
}