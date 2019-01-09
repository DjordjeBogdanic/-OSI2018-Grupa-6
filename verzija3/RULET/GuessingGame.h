#pragma once
#include <iostream>
#include <ctime>
#include <string>

class GuessingGame
{
	int Guess, Rand;
	std::string KLJUC;
	int total;
public:
	GuessingGame();
	void Info();
	bool ProvjeraKljuca(std::string kljuc);
	int GenerateRand(int&);
	void InputNr(int&, int&);
	void Podesavanje() {}
	int CheckNr(int&, int&);
};

GuessingGame::GuessingGame() : total(0), KLJUC("0123-4567-8901-2345") {}

void GuessingGame::Info()
{
	std::cout << "Osnovne informacije o igri:" << std::endl;
	std::cout << "Racunar generise proizvoljan broj u intervalu od 0 do 100." << std::endl;
	std::cout << "Vas zadatak je da u sto manje pokusaja pogodite koji je to broj racunar generisao." << std::endl;
	std::cout << "Ukoliko pogodite broj, dobijate 100/broj pokusaja bodova." << std::endl;
}

bool GuessingGame::ProvjeraKljuca(std::string kljuc)
{
	return !(kljuc != KLJUC);
}

int GuessingGame::GenerateRand(int& Rand) //Funkcija koja generise proizvoljan broj od 0 do 100
{
	std::cout << ">>POGODI BROJ<<\n";
	srand(time(NULL));
	Rand = rand() % 100 + 1;
	std::cout << "Nasumicno smo izabrali broj izmedju 0 i 100. Pokusajte pogoditi koji broj smo izabrali. Srecno!\n\n";
	return 1; //Vraca jedinicu za uspjesno izvrsenu funkciju
}

void GuessingGame::InputNr(int& Guess, int &Rand) //Funkcija za unos brojeva
{
	int k;
	for (int i = 0; i < 5; i++)
	{
		do
		{
			std::cout << i + 1 << ". pokusaj:";
			std::cin >> Guess;
		} while (Guess < 1 || Guess > 100);
		k = CheckNr(Rand, Guess);
	}
	if (k != 0)
		std::cout << "Nazalost niste pogodili broj." << std::endl;
}

int GuessingGame::CheckNr(int& Rand, int& Guess) //Funkcija koja provjerava odnos unesenog i generisanog broja
{
	if (Rand < Guess)
	{
		std::cout << "Broj koji trazite je manji od unesenog." << std::endl;
		return -1;
	}
	else if (Rand > Guess)
	{
		std::cout << "Broj koji trazite je veci od unesenog." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "CESTITAMO! Pogodili ste broj." << std::endl;
		return 0;
	}
}