//---------------------------------------------------------------------------

#pragma hdrstop

#include "Funkcje.h"

extern std::unordered_map<char, Zdarzenie> mapaZdarzen;
extern std::vector<char> keys;

void LogikaForward() {
    for (auto& xx : mapaZdarzen) {
        Zdarzenie* currZdarzenie = &xx.second;
        // Jesli nie ma poprzednika -> zdarzenie startowe -> ES=0, EF=CzasZdarzenia
        if (currZdarzenie->Poprzednicy.empty()) {
            currZdarzenie->EarlyStart = 0;
            currZdarzenie->EarlyFinish = currZdarzenie->Czas;
            continue;
        }
        // Jesli sa poprzednicy->Przejdz po nich->Wybierz najwiekszy EF z poprzednikow
        // Zakladam ze nikt sie nie pomylil w dodawaniu rzeczy
        int tempEF = -1;
        for (int i = 0; i < currZdarzenie->Poprzednicy.size(); i++) {
            char klucz = (char)currZdarzenie->Poprzednicy[i];
            auto it = mapaZdarzen.find(klucz);
            if (it->second.EarlyFinish > tempEF)
                tempEF = it->second.EarlyFinish;
        }
        currZdarzenie->EarlyStart = tempEF;
        currZdarzenie->EarlyFinish = tempEF + currZdarzenie->Czas;
    }
}

void FindNastepcy() {
    // Iteruj po Zdarzeniach
    for (auto& xx : mapaZdarzen) {
        Zdarzenie* currZdarzenie = &xx.second;
        // Jesli ma poprzednika -> przeiteruje po nich i wstawie im Current jako nastepce
        if (!currZdarzenie->Poprzednicy.empty())
            for (int i = 0; i < currZdarzenie->Poprzednicy.size(); i++) {
                char klucz = (char)currZdarzenie->Poprzednicy[i];
                auto it = mapaZdarzen.find(klucz);
                it->second.Nastepcy.push_back(currZdarzenie->Nazwa);
            }
    }
}

std::string SanitizeCPM(std::string CPM) {
    std::string result = "";
    for (char zdarzenie : CPM) {
        auto it = mapaZdarzen.find(zdarzenie);
        // Jesli poczatek lub koniec - dodaj i tak
        if (it->second.Poprzednicy.empty() || it->second.Nastepcy.empty()) {
            result += zdarzenie;
            continue;
        }
        // Sprawdz czy nastepnicy sa w CPM -> if not, wywal
        bool isOk = false;
        // Przeiteruj po Nastepnikach
        for (char nastepnik : it->second.Nastepcy) {
            // Wska¿ na nastepnika
            auto it_nast = mapaZdarzen.find(nastepnik);
            // Jak ma rezerwe -> skip do nastepnego
            if (it_nast->second.Rezerwa == 0) {
                isOk = true;
                break;
            }
        }
        if (!isOk)
            continue;
        // Sprawdz w poprzednikach
        isOk = false;
        for (char poprzednik : it->second.Poprzednicy) {
            // Wska¿ na poprzednika
            auto it_pop = mapaZdarzen.find(poprzednik);
            // Jak ma rezerwe -> skip do nastepnego
            if (it_pop->second.Rezerwa == 0) {
                isOk = true;
                break;
            }
        }
        if (isOk)
            result += zdarzenie;
    }
    return result;
}

void LogikaBackwards() {
    int totalTime = 0;
    for (auto& xx : mapaZdarzen) { // Unordered Map mamy, ale chcemy iterowac spak -> potrzebujemy zrobic wlasny order -> It po Zdarzeniach -> znajdz total time + utworz order
        keys.push_back(xx.second.Nazwa);
        if (xx.second.EarlyFinish > totalTime)
            totalTime = xx.second.EarlyFinish;
    }

    std::reverse(keys.begin(), keys.end()); // Reverse Keys iterator -> Iteruj w tyl po hashmapie

    for (char Zdarz : keys) {
        auto it = mapaZdarzen.find(Zdarz); // Jesli nie ma nastpecow -> koncowe -> LF = TotalTime
        if (it->second.Nastepcy.empty()) {
            it->second.LastFinish = totalTime;
        }
        else { // Jesli ma nastepcow:
            // Iteruj po nastepcach -> znajdz nizszy LF -> Wstaw LF oraz LS
            int tempLF = totalTime;
            for (char klucz : it->second.Nastepcy) {
                auto itTemp = mapaZdarzen.find(klucz);
                if (tempLF > itTemp->second.LastStart)
                    tempLF = itTemp->second.LastStart;
            }
            it->second.LastFinish = tempLF;
        }
        it->second.LastStart = it->second.LastFinish - it->second.Czas;
        it->second.Rezerwa = it->second.LastFinish - it->second.EarlyFinish;
    }
}

std::string WyznaczCPM() {
    std::string CPM_Path = "";
    std::reverse(keys.begin(), keys.end());

    for (char Zdarzenie : keys) {
        auto it = mapaZdarzen.find(Zdarzenie);
        if (it->second.Rezerwa == 0) {
            CPM_Path += it->second.Nazwa;
        }
    }
    return CPM_Path;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
