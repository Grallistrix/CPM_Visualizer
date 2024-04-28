//---------------------------------------------------------------------------

#pragma hdrstop

#include "Zdarzenie.h"

Zdarzenie::Zdarzenie(char Nazwa, int Czas) {
    this->Nazwa = Nazwa;
    this->Czas = Czas;
    if (Poprzednicy.empty()) {
        EarlyStart = 0;
        EarlyFinish = Czas;
    }
}

Zdarzenie::Zdarzenie(char Nazwa, int Czas, vector<char> Poprzednicy) {
    this->Nazwa = Nazwa;
    this->Czas = Czas;
    if (Poprzednicy.empty()) {
        EarlyStart = 0;
        EarlyFinish = Czas;
    }
    this->Poprzednicy = Poprzednicy;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
