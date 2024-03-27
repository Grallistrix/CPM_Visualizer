// CPM_C_Version.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <unordered_map>

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

	Zdarzenie(char Nazwa, int Czas) {
		this->Nazwa = Nazwa;
		this->Czas = Czas;
		if (Poprzednicy.empty()) {
			EarlyStart = 0;
			EarlyFinish = Czas;
		}
	}

	Zdarzenie(char Nazwa, int Czas, vector<char> Poprzednicy) {
		this->Nazwa = Nazwa;
		this->Czas = Czas;
		if (Poprzednicy.empty()) {
			EarlyStart = 0;
			EarlyFinish = Czas;
		}
		this->Poprzednicy = Poprzednicy;
	}
};

vector<Zdarzenie> tablicaZdarzen;
vector<char> keys;
unordered_map < char, Zdarzenie > mapaZdarzen;

ostream& operator<<(ostream& os, const vector<char> x) {
	if (x.empty())
		return os << "Brak";
	for (auto a : x)
		os << a;
	return os;
}

ostream& operator<<(ostream& os, Zdarzenie x) {
	os << "Zdarzenie " << x.Nazwa << " Czas: " << x.Czas << endl;
	os << "ES: " << x.EarlyStart << " EF:" << x.EarlyFinish << endl;
	os << "LS: " << x.LastStart << " LF:" << x.LastFinish << endl;
	os << "Rezerwa: " << x.Rezerwa << endl;
	os << "Poprzednicy: " << x.Poprzednicy << endl;
	os << "Nastepcy: " << x.Nastepcy << endl;
	return os;
}

void LogikaForward() {
	for (auto& xx : mapaZdarzen) {
		Zdarzenie* currZdarzenie = &xx.second;
		//Jesli nie ma poprzednika -> zdarzenie startowe -> ES=0, EF=CzasZdarzenia
		if (currZdarzenie->Poprzednicy.empty()) {
			currZdarzenie->EarlyStart = 0;
			currZdarzenie->EarlyFinish = currZdarzenie->Czas;
			continue;
		}
		//Jesli sa poprzednicy->Przejdz po nich->Wybierz najwiekszy EF z poprzednikow
		//Zakladam ze nikt sie nie pomylil w dodawaniu rzeczy
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
	//Iteruj po Zdarzeniach
	for (auto& xx : mapaZdarzen) {
		Zdarzenie* currZdarzenie = &xx.second;
		//Jesli ma poprzednika -> przeiteruje po nich i wstawie im Current jako nastepce
		if (!currZdarzenie->Poprzednicy.empty())
			for (int i = 0; i < currZdarzenie->Poprzednicy.size(); i++) {
				char klucz = (char)currZdarzenie->Poprzednicy[i];
				auto it = mapaZdarzen.find(klucz);
				it->second.Nastepcy.push_back(currZdarzenie->Nazwa);
			}
	}
}

void LogikaBackwards() {
	
	int totalTime = 0;

	for (auto& xx : mapaZdarzen) {	//Unordered Map mamy, ale chcemy iterowac spak -> potrzebujemy zrobic wlasny order -> It po Zdarzeniach -> znajdz total time + utworz order
		keys.push_back(xx.second.Nazwa);
		if (xx.second.EarlyFinish > totalTime)
			totalTime = xx.second.EarlyFinish;
	}

	reverse(keys.begin(), keys.end());					//Reverse Keys iterator -> Iteruj w tyl po hashmapie

	for (char Zdarz : keys) {
		auto it = mapaZdarzen.find(Zdarz);				//Jesli nie ma nastpecow -> koncowe -> LF = TotalTime
		if (it->second.Nastepcy.empty()) {
			it->second.LastFinish = totalTime;
		}
		else		//Jesli ma nastepcow:
		{
			//Iteruj po nastepcach -> znajdz nizszy LF -> Wstaw LF oraz LS
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

string WyznaczCPM() {
	string CPM_Path = "";
	reverse(keys.begin(), keys.end());

	for (char Zdarzenie : keys) {
		auto it = mapaZdarzen.find(Zdarzenie);
		if (it->second.Rezerwa == 0) {
			CPM_Path += it->second.Nazwa;
		}
	}
	return CPM_Path;
}

int main()
{
	/*
	Zdarzenie A('A', 3);
	Zdarzenie B('B', 4, vector<char>{'A'});
	Zdarzenie C('C', 2, vector<char>{'A'});
	Zdarzenie D('D', 5, vector<char>{'B'});
	Zdarzenie E('E', 1, vector<char>{'C'});
	Zdarzenie F('F', 2, vector<char>{'C'});
	Zdarzenie G('G', 4, vector<char>{'D', 'E'});
	Zdarzenie H('H', 3, vector<char>{'F', 'G'});
	tablicaZdarzen.insert(tablicaZdarzen.begin(), { A,B,C,D,E,F,G,H });
	*/
	Zdarzenie A('A', 7);
	Zdarzenie B('B', 9);
	Zdarzenie C('C', 12, vector<char>{'A'});
	Zdarzenie D('D', 8, vector<char>{'A', 'B'});
	Zdarzenie E('E', 9, vector<char>{'D'});
	Zdarzenie F('F', 6, vector<char>{'C', 'E'});
	Zdarzenie G('G', 5, vector<char>{'E'});
	tablicaZdarzen.insert(tablicaZdarzen.begin(), { A,B,C,D,E,F,G });


	int i = 0;
	for (Zdarzenie x : tablicaZdarzen) {
		mapaZdarzen.insert({ 65 + (i++), x });
	}
	LogikaForward();
	FindNastepcy();
	LogikaBackwards();

	for (auto xx : mapaZdarzen) {
		cout << xx.second << endl;
	}
	cout << endl << "Path to CPM:\t" << WyznaczCPM();
}