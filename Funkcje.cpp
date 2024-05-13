//---------------------------------------------------------------------------

#pragma hdrstop

#include "Funkcje.h"
#include <cctype>
#include <vcl.h>


extern std::unordered_map<char, Zdarzenie> mapaZdarzen;
extern std::vector<char> keys;
extern vector<char> keys;
extern string CPM_PATH;
//Skoñczone
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
//Skoñczone
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
//Skoñczone
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
//Skoñczone
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
 //??????????????????????????????????????
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
 //TODO+++++++++++++++++++++++++++++++++++++++++++++++++++
bool isAlreadyUsed(char c, const vector<char>& usedNames) {
	if(usedNames.size()!=0)
		return std::find(usedNames.begin(), usedNames.end(), c) != usedNames.end();
    return false;
}
//SKOÑCZOZNE
String extractLetters(String str) {
	String result;

    for (int i = 1; i <= str.Length(); ++i) {
        char c = str[i];

        // Check if the character is not a comma or space
		if (c != ',' && !std::isspace(c)) {
			result += (char)toupper(c);
        }
	}
	return result;
}
 //SKOÑCZONE
void DisplayLabelAtPosition(TWinControl *parent, int left, int top, const UnicodeString &caption)
{
	TLabel* label = new TLabel(parent);
	label->Parent = parent;
	label->Left = left;
	label->Top = top;
	label->Width = 0;
	label->Height = 0;
	label->Caption = caption;
	label->Transparent=true;
}
//SKOÑCZONE
void BoxDrawer(TWinControl *parent, int boxX, int boxY, bool isCPM, Zdarzenie ZdarzenieX){
		  //Zczytaj dane ze zdarzenia
	String ES_Number = ZdarzenieX.EarlyStart;
	String EF_Number = ZdarzenieX.EarlyFinish;
	String LS_Number = ZdarzenieX.LastStart;
	String LF_Number = ZdarzenieX.LastFinish;
	String Zdarzenie_Nazwa = ZdarzenieX.Nazwa;
	String R_Number =   ZdarzenieX.Rezerwa;

			//Rysuj Box
	TShape* boxShape = new TShape(parent);
	boxShape->Parent = parent;
	boxShape->Shape = stRectangle;
	boxShape->Brush->Color = (isCPM ? clWebFirebrick : clWhite); // Zielone - CPM, Biale - normalne;
	boxShape->SetBounds(boxX, boxY, boxWidth, boxHeight);

	//Zasiedl Danymi
	DisplayLabelAtPosition(parent, boxShape->Left + 2, boxShape->Top + boxShape->Height - 20, "ID:"+Zdarzenie_Nazwa);
	DisplayLabelAtPosition(parent, boxShape->Left + 2, boxShape->Top,"R:"+ R_Number);
	DisplayLabelAtPosition(parent, boxShape->Left + boxShape->Width - 30, boxShape->Top, "ES:"+ES_Number);
	DisplayLabelAtPosition(parent, boxShape->Left + boxShape->Width - 30, boxShape->Top + boxShape->Height - 20,"LS:"+LS_Number);

}
//SKOÑCZONE
void DrawLine(TOutline *parent, int startX, int startY, int endX, int endY, bool isCPM){
		   //Ustawe parent canvas na nasz outline
		 TCanvas *canvas = parent->Canvas;
		 //Kolor i grubosc
		 canvas->Pen->Width=PEN_WIDTH;
		 canvas->Pen->Color = (isCPM ? clWebFirebrick : clBlack);
			//Ustaw kursor    i rysuj nim do punktu koncowego
		 canvas->MoveTo(startX,startY);
		 canvas->LineTo(endX,endY);
}

void DrawLine(TOutline *parent, pair<int,int> Start, pair<int,int> Ending, bool isCPM){

		 TCanvas *canvas = parent->Canvas;
		 canvas->Pen->Width=PEN_WIDTH;
		 canvas->Pen->Color = (isCPM ? clWebFirebrick : clBlack);

		 canvas->MoveTo(Start.first, Start.second);
		 canvas->LineTo(Ending.first, Ending.second);
}

 //SKOÑCZONE
void ErrorBox(wstring body){
	int msgID = MessageBox(
			NULL,
			body.c_str()	,
			L"GRAND ERROR",
			MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
		);

}

void DeleteChildren(TWinControl *parent) {
	//Pêtla po dzieciach
	while (parent->ControlCount > 0) {
		TControl *child = parent->Controls[0]; // Pierwszy dzieciak [co usuniêcie, wszystkie ID s¹ ID--]
		parent->RemoveControl(child); // Usuñ relacje
		delete child;
	}
}
void RefreshOutline(TOutline* parent){
	DeleteChildren(parent);
	parent->Refresh();
}
//SKOÑCZONE

bool timeCheck(String czas){
	int czasINT;
	if (!TryStrToInt(czas, czasINT)) {
		ErrorBox(L"Czas musi byæ podany jako liczba!!!");
		return false;
	}
	//Jesli jest non-positive
	if(czasINT<=0){
	   ErrorBox(L"Czas musi byæ dodatni!!!");
		return false;
	}

	return true;
}


//Skoñczone
bool checkIfCritical(string Critical,char Name)
	{
        return std::string::npos!=Critical.find(Name);
	}
void Graph(vector<Zdarzenie> input,TOutline* parent)
{
	//Mapa pozycji
	unordered_map<char,pair<int,int>> position;
	const int offsetref =80;
	int sign =1;
	int offset = 90;
	int tempX=0;
	int tempY=300;
	double gap = 1.15;
	for (int i = 0; i < input.size(); i++)
	{
	//Find points and offset
	tempX=i*70*gap+35;
	position[input[i].Nazwa]=std::make_pair(tempX,tempY);
	}
for (int i = 0; i < input.size(); i++)
    {
    //DrawLines
        for(int k=0;k<input[i].Nastepcy.size();k++)
            {
			sign=sign*-1;
			offset=sign*(Random(offsetref+20)+60);
			bool tempCPMStatus=checkIfCritical(CPM_PATH,input[i].Nazwa)&&checkIfCritical(CPM_PATH,input[i].Nastepcy[k]);
            //from node to iffset
            DrawLine(parent, position[input[i].Nazwa].first+35, position[input[i].Nazwa].second+20, position[input[i].Nazwa].first+35, position[input[i].Nazwa].second+offset+20, tempCPMStatus);
            //from offset to ancestor offset
			DrawLine(parent, position[input[i].Nazwa].first+35, position[input[i].Nazwa].second+offset+20, position[input[i].Nastepcy[k]].first+25, position[input[i].Nastepcy[k]].second+offset+20, tempCPMStatus);
            //from offset to ancestor
            DrawLine(parent, position[input[i].Nastepcy[k]].first+25, position[input[i].Nastepcy[k]].second+offset+20, position[input[i].Nastepcy[k]].first+25, position[input[i].Nastepcy[k]].second+20, tempCPMStatus);
            }
	}
	//Draw boxes
    for (int i = 0; i < input.size(); i++)
    {
        bool isCPM=checkIfCritical(CPM_PATH,input[i].Nazwa);
        BoxDrawer(parent, position[input[i].Nazwa].first, position[input[i].Nazwa].second, isCPM, input[i]);
	}
    position.clear();
}



//---------------------------------------------------------------------------
#pragma package(smart_init)
