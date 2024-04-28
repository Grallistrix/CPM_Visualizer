//---------------------------------------------------------------------------

#ifndef FunkcjeH
#define FunkcjeH

#include "Zdarzenie.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

extern std::unordered_map<char, Zdarzenie> mapaZdarzen;
extern std::vector<char> keys;

void LogikaForward();
void FindNastepcy();
std::string SanitizeCPM(std::string CPM);
void LogikaBackwards();
std::string WyznaczCPM();


//---------------------------------------------------------------------------
#endif
