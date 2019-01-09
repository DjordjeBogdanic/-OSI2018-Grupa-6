#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<string>
#include<list>
#include<vector>

class Kviz
{
public:
	static int Total;

private:

	std::string pitanje;
	std::string odg[3];
	char Tacan_odgovor, Odgovor;
	int Bodovi;
	static std::string KLJUC;
	void Cout_s(std::string poruka)
	{
		std::cout << poruka << std::endl;
	}

public:
	Kviz(std::string pitanje, std::string o1, std::string o2, std::string o3, char to, int bb) :pitanje(pitanje), Bodovi(bb), Tacan_odgovor(to)
	{
		odg[0] = o1, odg[1] = o2, odg[2] = o3;
	}
	int Postavi_pitanje(int i)
	{
		std::cout << i << "."; Cout_s(pitanje);
		for (int i = 0; i < 3; i++)
			std::cout << i + 1 << ".) ", Cout_s(odg[i]);
		Cout_s("Koji je vas odgovor? ");
		do { std::cout << "\t-> ", std::cin >> Odgovor; } while (Odgovor != '1' && Odgovor != '2' && Odgovor != '3');


		if (Odgovor == Tacan_odgovor)
		{
			Cout_s("Tacan ODGOVOR!"); std::cout << std::endl;
			Total += Bodovi;
			return 1; //Ako je odgovor tacan, vratimo '1'
		}
		else
		{
			Cout_s("Pogresan odgovor!");
			std::cout << "Tacan odgovor je: ", std::cout << Tacan_odgovor << std::endl << std::endl;
			Total += -30;
			return 0;//Ako odgovor nije tacan, vratimo '0' 
		}

	};
	static void Info()
	{
		std::cout << "Osnovne informacije o IGRI: " << std::endl;
		std::cout << "Korisniku se prikazuje 5 slucajno odabranih pitanja iz liste koja ima najmanje 15 pitanja." << std::endl;
		std::cout << "Uz svako pitanje korisniku se prikazuju 3 moguca odgovora, nakon cega korisnik unosi broj odgovora za koji smatra da je tacan. " << std::endl;
		std::cout << "Ako je odgovor tacan, korisnik ce dobiti 20 bodova. Ako korisnik odgovori tacno na sva pitanja dobija još 50 bodova bonusa." << std::endl;
		std::cout << "Svaki pogresan odgovor korisniku uzima 30 bodova." << std::endl;

	}
	static bool ProvjeraKljuca(std::string kljuc);
};
bool Kviz::ProvjeraKljuca(std::string kljuc)
{
	if (kljuc != KLJUC) return 0; return 1;
}
std::string Kviz::KLJUC = "0123-4567-8901-2345";


