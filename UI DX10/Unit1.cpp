#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include "Zdarzenie.h"
#include "Funkcje.h"
#include <Windows.h>                                    //ErrorMSG
#include <cctype>
 #include <System.Character.hpp> //isUpper, isLetter etc
vector<Zdarzenie> tablicaZdarzen;
vector<char> keys;
unordered_map < char, Zdarzenie > mapaZdarzen;
string CPM_String;

TForm1 *Form1;


 using std::string;
 using std::vector;

 vector<char> alreadyUsedNames;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------




void ErrMsgNazwa(){
         int msgboxID = MessageBox(
			NULL,
			(LPCWSTR)L"Nazw¹ czynnoœci powinna byæ pojedyñcza, niepowtarzaj¹ca siê du¿a litera!!!",
			(LPCWSTR)L"B³¹d Nazwowy!",
			MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
		);

}

void __fastcall TForm1::Add_ButtonClick(TObject *Sender)
{

	Time_EditBox->Text = "12";
	Activity_EditBox->Text = "V";
	Predecesor_EditBox->Text = "A, B, C, D, E";


	String czas = Time_EditBox->Text;
	String poprz = Predecesor_EditBox->Text;
	String actNazwa = Activity_EditBox->Text;



	//If Time is not a number
	int czasINT;
	if (!TryStrToInt(czas, czasINT)) {
		int msgboxID = MessageBox(
			NULL,
			(LPCWSTR)L"Czas musi byæ podany jako liczba!!!",
			(LPCWSTR)L"B³¹d Czasowy!",
			MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
		);
		Time_EditBox->Text = "";
		return;
	}


	//if Czynnosc is no a single Big Character
	// isalpha        - X
	//length=1    - OK
	//isupper,           -X
	//nie powtarza sie     -X
	if (actNazwa.Length() != 1){
		 int msgboxID = MessageBox(
			NULL,
			(LPCWSTR)L"Nazwa musi byæ pojedyñcz¹, du¿¹, niepowtarzaj¹c¹ siê liter¹!!!",
			(LPCWSTR)L"B³¹d Nazwowy!",
			MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
		);

	}


	//Predecessors Stuff
	//Make some check in here:
	//Czy samo do siebie nie wskazuje-X
	//Czy wskazane istnieje     -X

	//-------------------------


	String predecLetters = extractLetters(poprz);

	String addedStuff="";
	addedStuff+=(    actNazwa +" "+predecLetters+" "+czas);

	ActivitiesList->Items->Add(addedStuff);



	Time_EditBox->Text = " ";
	Activity_EditBox->Text = " ";
	Predecesor_EditBox->Text = " ";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Delete_ButtonClick(TObject *Sender)
{
	if (ActivitiesList->ItemIndex != -1)
		ActivitiesList->Items->Delete(ActivitiesList->ItemIndex);

}
//---------------------------------------------------------------------------

