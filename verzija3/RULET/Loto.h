#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<algorithm>
#include<iostream>
#include<ctime>
#include<chrono>
#include<Windows.h>
#include<string>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

class Loto
{
private:
	int niz[7];
	int total;
	std::string KLJUC;
	bool Provjera(int podatak, int n);

public:
	Loto();
	int cijena_igre;
	void Info();
	bool ProvjeraKljuca(std::string kljuc);
	int Izvlacenje_brojeva();
	void Unos_brojeva();
	void Podesavanje() {}
};

void Loto::Info()
{
	std::cout << "Osnovne informacije o IGRI: " << std::endl;
	std::cout << "Korisnik unosi 7 razlicitih brojeva u opsegu od 1 do 45, nakon cega zapocinje proces izvlacenja dobitnih brojeva." << std::endl;
	std::cout << "Racunar na slucajan nacin bira 20 brojeva, te za svaki pogodjen broj, korisnik dobija (redni broj pogotka)*10 bodova. " << std::endl;

}
bool Loto::ProvjeraKljuca(std::string kljuc)
{
	return !(kljuc != KLJUC);
}
int Loto::Izvlacenje_brojeva()
{
	std::cout << "Izvuceni brojevi su: " << std::endl;
	std::srand(time(NULL));

	int i = 0, pom = 0, pogodak = 0;
	int Niz[20]; //Niz gdje cemo smjestiti 20 izvucenih brojeva

	do //Izvuceni brojevi ne smiju da se ponavljaju
	{
		pom = 0; //kontrolna promjenjiva
		int Broj = 1 + (rand() % 45); //Biramo broj : 1-45

		for (int j = 0; j < i; j++) //Prolazak kroz niz, gdje su smjesteni izvuceni brojevi
			if (Niz[j] == Broj) //Ukoliko naidjemo na broj u nizu, koji je trenutno izvucen
				pom = 1, j = i; //Odbacujemo dodavanje, kontrolnom promjenjivom sugerisemo da izvlacimo ponovo

		if (!pom)//Ukoliko nam kontrolna prom. sugerise da je izvuceni broj, prvi put izvucen, pretrazimo niz, da vidimo da li je korisnik izabrao upravo taj broj
		{
			Niz[i] = Broj;
			Sleep(1000); //Da bi izmedju izvlacenja 2 susjedna broj, bilo vremenskog razmaka
			if (!Provjera(Niz[i], 7)) //Provjeravamo da li je korisnik izabrao upravo taj izvuceni broj
			{
				SetConsoleTextAttribute(console, FOREGROUND_GREEN); //Promjena boje karaktera
				total += 10 * (++pogodak); //Uko;iko imamo pogodjen broj, dobijamo odredjen broj bodova, koji se racuna po datom algoritmu
			}
			std::cout << Niz[i++] << " "; //Ispis izvucenog broja
			SetConsoleTextAttribute(console, 15);
		}
	} while (i < 20); //Izvlaci se 20 slucajnih brojeva

	if (pogodak == 7) //Ukoliko pogodimo svih 7 brojeva, treptajuca konzola
	{
		for (int i = 0; i < 2; i++)
			system("Color 4F"), Sleep(70), system("Color 1F"), Sleep(70);
	}

	std::cout << std::endl;
	std::cout << "Ukupan broj pogodaka: " << pogodak << std::endl;
	std::cout << "Ukupan broj osvojenih bodova: " << total << std::endl;
	return total;
}
void Loto::Unos_brojeva()
{
	int i = 0;
	std::cout << "Unesite 7 razlicitih brojeva, u opsegu [1-45]: ";
	do
	{
		int podatak;
		std::cin >> podatak;

		if (!std::cin)//Ukoliko unesemo nesto sto nije cijeli broj
		{
			std::cin.clear(); //Klirujemo ulazni bafer, u koji se smjesta uneseni podatak
			std::cin.ignore(256, '\n'); //Ignorisemo unos
			goto Korak_Naprijed; //Prebacujemo se na labelu 'Korak_Naprijed', kojim oznacavamo neispravan unos
		}

		if (Provjera(podatak, i)) //Provjera da li smo vec prije taj broj unijeli, i da li je broj iz opsega
			niz[i++] = podatak;
		else
			Korak_Naprijed: std::cout << "Neispravan Unos!" << std::endl;
	} while (i < 7);
}
bool Loto::Provjera(int podatak, int n) //Provjera da li je uneseni broj iz opsega, i da li smo ga vec prije unijeli
{  //Takodje, ova funkcija je iskoristena za provjeru da li je izvuceni random broj, upravo korisnicki izabran broj
	if (podatak < 1 || podatak>45)
		return 0;
	for (int i = 0; i < n; i++) //Pretraga niza, za provjeru da li je izvuceni broj, korisnicki broj.
		if (niz[i] == podatak)
			return 0;

	return 1;	//Ukoliko nisu ispunjeni prethodni uslovu, tj. podatak je ispravno unesen, ali ga nije odabrao korisnik, vracamo '1'
}
Loto::Loto() : total(0), KLJUC("0123-4567-8901-2345"), cijena_igre(100) {}