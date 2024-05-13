//---------------------------------------------------------------------------

#ifndef FunkcjeH
#define FunkcjeH

#include "Zdarzenie.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <Vcl.Outline.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>

extern std::unordered_map<char, Zdarzenie> mapaZdarzen;
extern std::vector<char> keys;


#define boxWidth 60
#define boxHeight 40
 #define PEN_WIDTH 4


			//Funkcje CPM
void LogikaForward();
void FindNastepcy();
std::string SanitizeCPM(std::string CPM);
void LogikaBackwards();
std::string WyznaczCPM();

			//Funkcje Sanityzacji
bool timeCheck(String czas);

			//funkcje przydatne
bool isAlreadyUsed(char c, const vector<char>& usedNames);
String extractLetters(String str);
void DeleteChildren(TWinControl *parent);
void ErrorBox(wstring body);

			//Funkcje Rysowania
//                           (Outline1,                               ,     "TEXT" )
void DisplayLabelAtPosition(TWinControl *parent, int left, int top, const UnicodeString &caption);
void BoxDrawer(TWinControl *parent, int boxX, int boxY, bool isCPM, Zdarzenie ZdarzenieX);
void DrawLine(TOutline *parent, int startX, int startY, int endX, int endY, bool isCPM=false);
void DrawLine(TOutline *parent, pair<int,int> Start, pair<int,int> Ending, bool isCPM=false);
void RefreshOutline(TOutline* parent);
bool checkIfCritical(string Critical,char Name);
void Graph(vector<Zdarzenie> input,TOutline* parent);
//---------------------------------------------------------------------------
#endif
