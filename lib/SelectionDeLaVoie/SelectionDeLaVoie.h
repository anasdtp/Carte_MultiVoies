#ifndef _SelectionDeLaVoie_LIB
#define _SelectionDeLaVoie_LIB

#include <Arduino.h>

typedef struct SelectionDeLaVoieBUS
{
    int pinA, pinB, pinC;
}SelectionDeLaVoieBUS;

typedef struct SelectionDeLaVoieENABLEMUX
{
    int EN_MUX0, EN_MUX1, EN_MUX2, EN_MUX3, EN_MUX4, EN_MUX5;
}SelectionDeLaVoieENABLEMUX;

class SelectionDeLaVoie
{
public:
    SelectionDeLaVoie(SelectionDeLaVoieBUS bus, SelectionDeLaVoieENABLEMUX enable);
    ~SelectionDeLaVoie();

    void selectionVoie(uint8_t voie = 0);

private:
    SelectionDeLaVoieBUS _bus;
    SelectionDeLaVoieENABLEMUX _enable;

    void initOutput();
    void setBus(uint8_t etat = 0);
    void enableMUX(uint8_t etat = 0);
    void disableMUX(bool disable = true);
};

#endif //_SelectionDeLaVoie_LIB
