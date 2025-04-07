#include <Arduino.h>
#include <SelectionDeLaVoie.h>

#define BUS_MUX0 2 //Chosi au hasard, à mettre les bonnes pin par rapport au kicad
#define BUS_MUX1 3
#define BUS_MUX2 4

#define EN_MUX0 5
#define EN_MUX1 6
#define EN_MUX2 7
#define EN_MUX3 8
#define EN_MUX4 9
#define EN_MUX5 10

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

    // Test selectionVoie
    Serial.println("Testing selectionVoie sur voie 10...");
    selection.selectionVoie(10); // Example voie
}

void loop() {
    if((millis() - tempsEchantillonagePrecedent) >= tempsEchantillonage){
        //Si le temps d'échantillonage est écoulé, soit ici une seconde
        tempsEchantillonagePrecedent = millis();//En milliseconde

        compteurTemps++;
        if(compteurTemps >= 5){
            compteurTemps = 0;
            Serial.println("5 secondes écoulées");
        }

    }
}