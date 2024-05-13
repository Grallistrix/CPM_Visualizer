//---------------------------------------------------------------------------

#pragma hdrstop

#include "Zdarzenie.h"
#include <sstream>

Zdarzenie::Zdarzenie(char Nazwa, int Czas) {
    this->Nazwa = Nazwa;
    this->Czas = Czas;
	if (Poprzednicy.empty()) {
        EarlyStart = 0;
        EarlyFinish = Czas;
    }
}

Zdarzenie::Zdarzenie(){
	Nazwa=(char)(Random(26) + 'A');
	Czas=Random(99);
	EarlyStart=Random(99);
	EarlyFinish=Random(99);
	LastStart=Random(99);
	LastFinish=Random(99);
	Rezerwa=Random(99);
}

Zdarzenie::Zdarzenie(const std::string input){
	std::istringstream iss(input);
		std::string temp;

		// Read the first character as Nazwa
		iss >> Nazwa;

		// Read the second part as Poprzednicy
		iss >> temp;
		for (char c : temp) {
		if (std::isalpha(c)) { // Check if the character is a letter
			this->Poprzednicy.push_back(c);
			}
		}

		// Read the third part as Czas
		iss >> Czas;
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

std::string Zdarzenie::getString() const {
    std::ostringstream oss;
    oss << "Nazwa: " << Nazwa << std::endl;
    oss << "Poprzednicy: ";
    for (char c : Poprzednicy) {
        oss << c << " ";
    }
    oss << std::endl;
    oss << "Nastepcy: ";
    for (char c : Nastepcy) {
        oss << c << " ";
    }
    oss << std::endl;
    oss << "Czas: " << Czas << std::endl;
    oss << "EarlyStart: " << EarlyStart << std::endl;
    oss << "EarlyFinish: " << EarlyFinish << std::endl;
    oss << "LastStart: " << LastStart << std::endl;
    oss << "LastFinish: " << LastFinish << std::endl;
    oss << "Rezerwa: " << Rezerwa << std::endl;
    return oss.str();
}

std::string Zdarzenie::ZdarzenieToCSV() {
	std::string csvString;

	// Nazwa
	csvString += Nazwa;
	csvString += ";";

	//Poprzednicy
	csvString += '"';
	for (char c : Poprzednicy) {
		csvString.push_back(c);
	}
	csvString += "\";";

	//  Nastepcy
	csvString += '"';
	for (char c : Nastepcy) {
		csvString.push_back(c);
	}
	csvString += "\";";

	 //Czasy
	csvString += std::to_string(Czas) + ";" + std::to_string(EarlyStart) + ";" + std::to_string(EarlyFinish) + ";" + std::to_string(LastStart) + ";" + std::to_string(LastFinish) + ";" + std::to_string(Rezerwa);

    return csvString;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
