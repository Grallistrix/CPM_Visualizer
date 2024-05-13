#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Zdarzenie.h"
#include "Funkcje.h"
#include <Windows.h>                                    //ErrorMSG
#include <System.Character.hpp> //isUpper, isLetter etc
#include "Zdarzenie_View.h"
#include <fstream>
#include <utility>

//Mapa Obiektow
unordered_map <char, Zdarzenie> mapaZdarzen;
vector<Zdarzenie> tablicaZdarzen;
vector<char> keys;
 //Zmienne Globalne
string CPM_PATH;
bool calculated=false;

TForm1 *Form1;

using std::string;
using std::vector;
using std::sort;
using std::isalpha;

vector<char> alreadyUsedNames;

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}


//50/50----------------------------------------------------
void __fastcall TForm1::Add_ButtonClick(TObject *Sender)
{

//wyzeruj wszystko

				//Zczytaj Tekst
	String czas = Time_EditBox->Text;
	String poprz = Predecesor_EditBox->Text;
	String actNazwa = Activity_EditBox->Text;


				//Sanityzuj Tekst
			//-------------------------Czas
	if(!timeCheck(czas))
		return;



			//-------------------------Czynnosc
	//if Czynnosc is no a single Big Character
	//nie powtarza sie     - OK
	//Len=1 - OK
	//Alpha - OK


	char ZdrzLetter = actNazwa[1];

	if ( actNazwa.Length() > 1 or !isalpha(ZdrzLetter)) {
		 ErrorBox(L"Nazwa musi byæ pojedyñcz¹, du¿¹, niepowtarzaj¹c¹ siê liter¹!!!");
		 return;
	}

	ZdrzLetter = toupper(ZdrzLetter);
	String ZdrzLetterStr = ZdrzLetter;

	for (int i = 0; i < ActivitiesList->Items->Count; ++i) {
		String itemText =ActivitiesList->Items->Strings[i];


		if (itemText[1] == ZdrzLetter) {
		ErrorBox(L"Zdarzenia nie moga sie powtarzac!");
			return;
        }
	}





			//-------------------------Predecessors
	String sortPredStr=poprz;

	if(sortPredStr.Length()>1)sort(sortPredStr.begin()-1,sortPredStr.end());

				//Stworz wpis na LISTE
	String predecLetters = extractLetters(sortPredStr); //NonAlpha pomijac

	if(predecLetters=="") predecLetters="-";



    	if(poprz!=""){

		for(int i=1;i<poprz.Length()+1;i++	){
			char znak = poprz[i];

			if(isalpha(znak)==false)	continue;

			znak = (char)toupper(znak);

			if(sortPredStr.Pos(znak)==0)
				sortPredStr+=(char)toupper(znak);

			if(sortPredStr.Pos(actNazwa)!=0){
				ErrorBox(L"Aktywnosc nie moze byc swoim poprzednikiem!");
				return;
			}

		}
	}

	String addObject=(ZdrzLetterStr +" "+predecLetters+" "+czas);
	ActivitiesList->Items->Add(addObject);
				 //Wyzeruj tekst
	Time_EditBox->Text = "";
	Activity_EditBox->Text = "";
	Predecesor_EditBox->Text = "";
	calculated=false;
}

 //SKOÑCZONE
void __fastcall TForm1::Delete_ButtonClick(TObject *Sender)
{
    //Zaznaczone (Not non-selected) to usuñ
	if (ActivitiesList->ItemIndex != -1)
		ActivitiesList->Items->Delete(ActivitiesList->ItemIndex);
	CPM_Edit->Text ="";
	Memo1->Lines->Text ="";
	calculated=false;



	mapaZdarzen.clear();
	tablicaZdarzen.clear();
	keys.clear();
}
//SKOÑCZONE
void __fastcall TForm1::Button_Info_click(TObject *Sender){


	if (ActivitiesList->ItemIndex == -1 or !calculated){
		return;
	}

	 int searchedIndex = ActivitiesList->ItemIndex;
	 UnicodeString firstItemText = ActivitiesList->Items->Strings[searchedIndex];
	 char searchedZdarzenie = firstItemText.SubString(1, 1).c_str()[0];

	 String searchedChar = ActivitiesList->ItemIndex    ;

	 Zdarzenie ABC = mapaZdarzen.find(searchedZdarzenie)->second;

	 string text =  ABC.getString();

	 Memo1->Lines->Text = text.c_str();

}

//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Calculate_ButtonClick(TObject *Sender)
{

	RefreshOutline(Outline1);
	vector<String> vclStrings;
	vector<string> zczytaneString;

	vclStrings.clear();
	zczytaneString.clear();
	String empty = "";
	CPM_Edit->Text = empty;

	tablicaZdarzen.clear();
	keys.clear();
	CPM_PATH="";
	mapaZdarzen.clear();
	//TESTING 1
	RefreshOutline(Outline1);


	//TESTING PART    2    - dane przykladowe

		//BDEF
	/*
	string a = "A - 7";
	string b = "B - 9";
	string c = "C A 12";
	string d = "D AB 8";
	string e = "E D 9";
	string f = "F CE 6";
	string g = "G E 5";
	string tempStr[] = {a,b,c,d,e,f,g};
	  //ABDGH

	string a = "A - 3";
	string b = "B A 4";
	string c = "C A 2";
	string d = "D B 5";
	string e = "E C 1";
	string f = "F C 2";
	string g = "G DE 4";
	string h = "H FG 3";
	string tempStr[] = {a, b, c, d, e, f, g, h};

	//TESTING PART 3 -  zaludnij Liste

	ActivitiesList->Clear();
	for (const auto& str : tempStr) {
		vclStrings.push_back(String(str.c_str()));
	}

	for (const auto& str : vclStrings) {
		ActivitiesList->Items->Add(str);
	}
       */
	//ZCZYTAJ Z DIAGRAMU


	for (int i = 0; i < ActivitiesList->Items->Count; ++i) {
		String vclString = ActivitiesList->Items->Strings[i];
		zczytaneString.push_back(AnsiString(vclString).c_str());
	}

	//Wrzuc Zdarzenia na mape [do kalkulacji]
	 for(string zdarzenieStr: zczytaneString){
	   Zdarzenie temp = Zdarzenie(zdarzenieStr);
	   mapaZdarzen[temp.Nazwa] = temp;
	 }


	//KALKULACJE
	LogikaForward();
	FindNastepcy();
	LogikaBackwards();

	CPM_PATH = SanitizeCPM(WyznaczCPM());
	CPM_Edit->Text = CPM_PATH.c_str();



	//Wektor Zdarzen przekalkulowanych
	for (const auto& pair : mapaZdarzen) {
		tablicaZdarzen.push_back(pair.second);
	}


	 int boxX=100, boxY=100;
	//RYSOWANIE

	Graph(tablicaZdarzen,Outline1);
	/*
	 for(auto pair: mapaZdarzen){

		Zdarzenie X = pair.second;
		bool isCPM =  false;

		for(char c:CPM_PATH)
			if(c==X.Nazwa) isCPM=true;

		BoxDrawer(Outline1, boxX, boxY, isCPM, X);
		 boxY+=50;
	 }
	 */

	calculated=true;
}


//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __fastcall TForm1::Edit_ButtonClick(TObject *Sender)
{
	//Niezaznaczone, to skipuj
	if (ActivitiesList->ItemIndex == -1)
		return;

	//Zczytaj nowe dane
	String czas = Time_EditBox->Text;
	String poprz = Predecesor_EditBox->Text;
	String actNazwa = Activity_EditBox->Text;


	//Time Check
	if(!timeCheck(czas)) return;

	//Pred Check
		//tutaj trzeba usun¹æ i co wtedy?!?!?!

	//Wstaw
    ActivitiesList->Items->Strings[0] = "New Value";

	calculated=false;
}

//SKOÑCZONE
void __fastcall TForm1::CalcFile_ButtonClick(TObject *Sender)
{
	//Calculate
	Calculate_ButtonClick(CalcFile_Button);
	//open file
	std::ofstream file("Result.txt");
	if (!file.is_open()) {
		ErrorBox(L"Pliku nie udalo sie utworzyc");
        return;
	}
	 //save to fileee
	for(Zdarzenie x:tablicaZdarzen){
		string csv_string = x.ZdarzenieToCSV() ;
		file<<csv_string<<endl;
	}
    file.close();
}

