#ifndef ZDARZENIE_H
#define ZDARZENIE_H

#include <vector>
using namespace std;

class Zdarzenie {
public:
    char Nazwa;
    vector<char> Poprzednicy;
    vector<char> Nastepcy;
    int Czas;
    int EarlyStart;
    int EarlyFinish;
    int LastStart;
    int LastFinish;
    int Rezerwa;

    Zdarzenie(char Nazwa, int Czas);
    Zdarzenie(char Nazwa, int Czas, vector<char> Poprzednicy);
};

#endif

