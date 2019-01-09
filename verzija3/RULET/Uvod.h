#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdarg>
#include<cstdio>
#include "Loto.h"
#include "Kviz.h"
#include "rulet.h"
Rulet r;// da bi se samo jednom pozvao konstruktor, jer od njega zavisi da li je kraj i 
//da li je igra OTKAZANA I NE MOZE SE VISE igrati

int Kviz::Total = 0;

//Pretrazivanje vektora
int PretraziNiz(std::vector<int>Niz, int v)
{
	for (int j = 0; j < Niz.size(); j++)
		if (v == Niz[j])
			return 1;
	return 0;
}

//Pitanja koja se postavljaju u drugoj igri
void Pitanja(std::list < Kviz >Lista)
{
	Kviz q1(" Malteski jezik potièe od: ", "Nordijskog.", "Turskog.", "Arapskog.", 3, 20);
	Kviz q2(" Pored osoba, na Novom Zelandu se i ovi entiteti zakonski smatraju fizickim licima:", "Prirodna bogatstva.", "Orci, elfovi i hobiti.", "Psi i macke.", 1, 20);
	Kviz q3(" U Južnoj Koreji, ljudi veruju da ovaj kuæni aparat može da vas ubije: ", "Blender.", "CD plejer.", "Ventilator.", 3, 20);
	Kviz q4("Koji je najveci okean na svijetu ?", "Atlantski", "Tihi", "Indijski", 2, 20);
	Kviz q5("Koji je de facto glavni grad EU-a ?", "London", "Lisabon", "Bruxelles", 3, 20);
	Kviz q6("Gdje se nalazi najvisa planina na svijetu?", "Kini", "Nepalu", "Indiji", 2, 20);
	Kviz q7("Koju valutu koristi Indonezija? ", "Rupija", "Rangit", "Rijal", 3, 20);
	Kviz q8("Koji je sesti planet od Sunca? ", "Saturn", "Jupiter", "Neptun", 1, 20);

	Lista.push_back(q1);
	Lista.push_back(q2);
	Lista.push_back(q3);
	Lista.push_back(q4);
	Lista.push_back(q5);
	Lista.push_back(q6);
	Lista.push_back(q7);
	Lista.push_back(q8);
}

class Uvod
{
	std::map<int, std::string> IGRA_[4]; //Mape, u koju se smjestaju sortirani rezultati igara.
	int Ukupan_broj_bodova;					//treba smanjiti na 3 jer moja igra nije tu?

public:
	Uvod();
	void Meni();
private:
	void Pregled_statistike();
	void Igranje();

	//Cuvanje ukupnog broja bodova koje korisnik posjeduje, u fajl.
	void Sacuvaj_bodove_u_fajl(int Ukupan_broj_bodova)
	{
		std::ofstream UB("Bodovi.txt");
		if (UB)
		{
			UB << Ukupan_broj_bodova;
			UB.close();
		}
	}

	//Cuvanje statistike u CSV fajl.
	void Sacuvaj_u_fajl()
	{

		std::ofstream File("Statistika.txt");
		if (File)
		{
			for (int i = 0; i < 4; i++)//Ucitavamo statistiku igara, prikazuje se statistika sve 4 igre, jedna ispod druge.
			{
				File << std::endl;
				File << "\tIGRA " << i + 1 << std::endl; //Statistika i-te igre.

				std::map<int, std::string>::iterator it = IGRA_[i].begin();
				int brojac = 0; //Pom promjenjiva, koristi se pri ispisu.
				for (it = IGRA_[i].begin(); it != IGRA_[i].end() && brojac <= 10; ++it)
					File << ++brojac << ".)  " << it->first << "  " << it->second << '\n';
			}
			File.close(); //Zatvaranje fajla
		}
	}

	//Instalacija Programa.
	void Instalacija()
	{
		/*Simulira instalaciju.*/
		for (int i = 0; i < 100; i++)
		{
			std::cout << "Instalacija u toku: " << std::string(20, ' ') << i++ << " % ";
			Sleep(100);
			system("cls");
		}

		/*Kreiraju se fajlovi sa Imenom, i Lozinkom, sto predstavlja dio instalacionog procesa.*/
		std::ofstream File("IME.txt");
		std::ofstream FileLozinka("LOZINKA.txt");

		if (File && FileLozinka)
		{

			std::string ime, lozinka;
			std::cout << "REGISTRACIJA: " << std::endl;
			std::cout << std::string(10, ' ') << "Unesite IME: ", std::cin >> ime;
			do { std::cout << std::string(10, ' ') << "Unesite LOZINKU(maks. 8. karaktera): ", std::cin >> lozinka; } while (lozinka.size() > 8); //Ukoliko je velicina lozinke veca od 8, ponovni unos.

			File << ime << " ", File.close();
			FileLozinka << lozinka << " ", FileLozinka.close();
			Sacuvaj_bodove_u_fajl(Ukupan_broj_bodova = 10);//Pocetni bodovi se smjestaju u Fajl.
		}

	}

	//INST. POD. nam omogucavaju izbor kljuca po igrici, 1h ,1d,1s.
	void Instalaciona_podesavanja() {}

	//Deinstalacija Programa.
	void Deinstalacija()
	{
		std::remove("IME.txt");
		std::remove("LOZINKA.txt");
		/*Simulira deinstalaciju.*/
		for (int i = 0; i < 100; i++)
		{
			std::cout << "Deinstalacija u toku: " << std::string(20, ' ') << i++ << " % ";
			Sleep(100);
			system("cls");
		}
		std::cout << "Deinstalacija uspjesno izvrsena!" << std::endl;
	}

	//Ispisivanje 'obicne' linije.
	void Linije()
	{
		std::cout << "\t\t_________________________________________________" << std::endl;
	}

	//Unos opcije koju odabiramo pri izvrsavanju programa.
	char Unos(int n, ...)
	{
		char *znakovi = new char[n];
		char znak;
		va_list argumenti;
		va_start(argumenti, n);
		for (int i = 0; i < n; i++)
			znakovi[i] = va_arg(argumenti, char);

		do { std::cout << "\t-> ", std::cin >> znak; } while (Provjera_znaka(znak, znakovi, n));
		va_end(argumenti);
		delete[]znakovi;
		return znak;
	}

	//Provjera da li je koristeni znak, upravo jedan od mogucih.
	bool Provjera_znaka(char znak, char *znakovi, int n)
	{
		for (int i = 0; i < n; i++)
			if (znak == znakovi[i])
				return 0;
		return 1;
	}

	//Funkcija Zaglavlja
	void Zaglavlje(char znak, std::string String)
	{
		std::cout << "[" << znak << "] " << String << std::endl;
	}

	//Funkcija kojom se vracamo jedan, ili vise koraka unazad.
	void  Nazad()
	{
		std::cout << "Nazad [0]  Meni [9]" << std::endl;
		std::cout << "________________________________________________________" << std::endl;
	}

	//Pregled Menija pojedinacne igre.
	void MeniIgre()
	{
		Zaglavlje('1', "Zapocni Igru");
		Zaglavlje('2', "Info");
		Zaglavlje('3', "Podesavanja");
		Nazad();
	}

	//Pregled igara kojima mozemo pristupiti.
	void Igre()
	{
		system("cls");
		std::cout << "IGRE: " << std::endl;
		Zaglavlje('1', "Pogadjanje zamisljenog broja u intervalu [0-100]");
		Zaglavlje('2', "Kviz");
		Zaglavlje('3', "Loto");
		Zaglavlje('4', "Rulet");
		Nazad();
	} //Prikazuju se igre koje mozemo igrati


	//Pitanja koja ce se koristiti u Drugoj igri, uz odgovore.
	std::list < Kviz > Igra2()
	{
		std::list < Kviz >Lista;
		Kviz q1(" Malteski jezik potièe od: ", "Nordijskog.", "Turskog.", "Arapskog.", '3', 20);
		Kviz q2(" Pored osoba, na Novom Zelandu se i ovi entiteti zakonski smatraju fizickim licima:", "Prirodna bogatstva.", "Orci, elfovi i hobiti.", "Psi i macke.", '1', 20);
		Kviz q3(" U Južnoj Koreji, ljudi veruju da ovaj kuæni aparat može da vas ubije: ", "Blender.", "CD plejer.", "Ventilator.", '3', 20);
		Kviz q4("Koji je najveci okean na svijetu ?", "Atlantski", "Tihi", "Indijski", '2', 20);
		Kviz q5("Koji je de facto glavni grad EU-a ?", "London", "Lisabon", "Bruxelles", '3', 20);
		Kviz q6("Gdje se nalazi najvisa planina na svijetu?", "Kini", "Nepalu", "Indiji", '2', 20);
		Kviz q7("Koju valutu koristi Indonezija? ", "Rupija", "Rangit", "Rijal", '3', 20);
		Kviz q8("Koji je sesti planet od Sunca? ", "Saturn", "Jupiter", "Neptun", '1', 20);
		Kviz q9("Kako se zove mitolosko cudoviste u kojem su sjedinjeni lav i orao?", "Jednorog", "Minotaur", "Grifon", '3', 20);
		Kviz q10("Gdje je odapeta plamena strijela upalila olimpijski plamen?", " Barcelona 1992", " Barcelona 1881", " Barcelona 1999", '1', 20);
		Kviz q11("Tko je 395. godine razdijelio Rimsko carstvo na zapadno i istocno?", "Justinijan", "Heraklije", "Teodozije", '3', 20);
		Kviz q12("Gdje se nalazi labirint u ljudskom tijelu?", "Uhu", "Mozgu", "Plucima", '1', 20);
		Kviz q13("Koji sahovski kralj je najduze bio na tronu svjetskog prvaka?", "Gary Kasparov", "Emanuel Lasker", "George Lasquet", '2', 20);
		Kviz q14("Kojega metala u zlatnoj olimpijskoj medalji ima 92,5 posto?", "Srebra", "Zlata", "Bakra", '1', 20);
		Kviz q15("U kojoj je zemlji Legoland?", "Finska", "Danska", "Francuska", '2', 20);
		Kviz q16("Za koji je sport nadlezna FINA ?", "Fudbal", "Plivanje", "Odbojka", '2', 20);

		Lista.push_back(q1);
		Lista.push_back(q2);
		Lista.push_back(q3);
		Lista.push_back(q4);
		Lista.push_back(q5);
		Lista.push_back(q6);
		Lista.push_back(q7);
		Lista.push_back(q8);
		Lista.push_back(q9);
		Lista.push_back(q10);
		Lista.push_back(q11);
		Lista.push_back(q12);
		Lista.push_back(q13);
		Lista.push_back(q14);
		Lista.push_back(q15);
		Lista.push_back(q16);

		return Lista;
	}

};

//Konstruktor, konstruise se FAJL sa imenom korisnika, i lozinkom, te ukupan broj bodova.
Uvod::Uvod()
{
	std::ifstream Ispis("IME.txt");
	if (Ispis)
	{
		std::cout << "Pozdrav ";
		std::string line;
		std::getline(Ispis, line);
		std::cout << line << std::endl;
		Sleep(1000);
		system("cls");

		std::ifstream UB("Bodovi.txt"); //Ucitavanje ukupnog broja bodova.
		if (UB)
		{
			UB >> Ukupan_broj_bodova;
			UB.close();
		}
		Ispis.close();
	}
	else
	{
		/* Instalacija / Instalaciona podesavanja*/
		std::cout << std::string(28, ' ') << "DOBRODOSLI!" << std::endl;
		Zaglavlje('1', "INSTALACIJA");		Zaglavlje('2', "INSTALACIJONA PODESAVANJA");
		std::cout << "-------------------------------" << std::endl;
		Unos(2, '1', '2') == '1' ? Instalacija() : Instalaciona_podesavanja();

		system("cls");
	}
}

//Meni sa opcijama za igranje, i pregled statistike.
void Uvod::Meni()
{
	std::cout << std::string(30, ' ') << "4 GAMES!" << "\n";
	std::cout << "Ukupan Broj Bodova: " << Ukupan_broj_bodova << std::endl;
	Linije();
	std::cout << std::string(16, ' ') << "[1] IGRE\t[2] STATISTIKA \t[3] DEINSTALACIJA" << std::endl;
	Linije();
	char znak = Unos(3, '1', '2', '3');
	znak == '1' ? Igranje() : (znak == '2' ? Pregled_statistike() : Deinstalacija());
}

//Opcija za pregled statistike.
void Uvod::Pregled_statistike()
{
	system("cls");
	std::cout << "Pregled Statistike: " << std::endl; //10 zadnjih rezultata

	for (int i = 0; i < 4; i++)//Ucitavamo statistiku igara, prikazuje se statistika sve 4 igre, jedna ispod druge.
	{
		std::cout << std::endl;
		std::cout << "\tIGRA " << i + 1 << std::endl; //Statistika i-te igre.

		std::map<int, std::string>::iterator it = IGRA_[i].begin();
		int brojac = 0; //Pom promjenjiva, koristi se pri ispisu.
		for (it = IGRA_[i].begin(); it != IGRA_[i].end() && brojac <= 10; ++it)
			std::cout << ++brojac << ".)  " << it->first << "  " << it->second << '\n';
	}


	std::cout << "Sacuvaj REZULTAT [S] "; //Mogucnost cuvanja rezultata u CSV fajl.
	Nazad();
	if (Unos(3, '0', '9', 'S') == 'S')
	{
		std::cout << "Sacuvano u CSV fajl." << std::endl;
		Sacuvaj_u_fajl();
		Sleep(1000);
	}
	system("cls"), Meni();

}

//Glavna metoda objekta 'UVOD'.
void Uvod::Igranje()
{
	system("cls");
Jump1: Igre();
	
	char znak = Unos(6, '4', '3', '2', '1', '0', '9');
	/*IGRA3*/	  if (znak == '3')   // '3' IGRA 3
	{
		Loto LT;
		if (Ukupan_broj_bodova >= LT.cijena_igre) //Cijena igranja IGRE broj 3. je 100 bodova, provjerava se da li ostvarujemo taj uslov.
		{
			Ukupan_broj_bodova -= LT.cijena_igre; //Ukoliko imamo ukupno vise od 100 bodova, mozemo igrati igru.
			std::string kljuc;
			do
			{
				std::cout << "Unesite KLJUC igre, [xxxx-xxxx-xxxx-xxxx]: ", std::cin >> kljuc;
			} while (!LT.ProvjeraKljuca(kljuc));

		Jump2:system("cls");
			std::cout << "\t\t\t\t LOTO" << std::endl;
			MeniIgre();

			char znak = Unos(5, '1', '2', '3', '0', '9'); //Omogucen unos neke od opcija
			if (znak == '1') // '1' pokrecemo igru
			{
				system("cls");
				LT.Unos_brojeva(); //Unos korisnickih brojeva
				int Bodovi = LT.Izvlacenje_brojeva();
				Ukupan_broj_bodova += Bodovi; //Izvlacenje brojeva, funkcija vraca ostvarene bodove

											  //Cuvanje statistike.
				IGRA_[2].insert(std::pair<int, std::string>(Bodovi, __TIMESTAMP__));
				Sacuvaj_bodove_u_fajl(Ukupan_broj_bodova);

				Nazad(); //Ispis linije za odabir 

				if (Unos(2, '0', '9') == '0') //'0'=> korak nazad
				{
					if (Ukupan_broj_bodova >= LT.cijena_igre)
						goto Jump2;
					else
						goto Naprijed;
				}
				else
					system("cls"), Meni(); //'9' => Meni
			}
			else if (znak == '2')
			{
				char znak;
				system("cls");
				LT.Info();
				Nazad();
				if (Unos(2, '0', '9') == '0')
					goto Jump2;
				else
					system("cls"), Meni();
			}
			else if (znak == '3')
			{
				system("cls");
				LT.Podesavanje();
				Nazad();
				if (Unos(2, '0', '9') == '0')
					goto Jump2;
				else
					system("cls"), Meni();
			}
			else if (znak == '0')
				goto Jump1;
			else
			{
				system("cls");
				Meni();
			}
		}

		else //Ukoliko nemamo 100 bodova, ne mozemo igrati ovu igru
		{

		Naprijed: system("cls");
			std::cout << "Nedovoljno bodova. Da biste igrali ovu igru, treba Vam 100 bodova!" << std::endl;
			Nazad();
			if (Unos(2, '0', '9') == '0')
				goto Jump1;
			else
				system("cls"), Meni();

		}
	}
	//RULET
	else if (znak == '4')
	{
		system("cls");
		//Rulet r(Ukupan_broj_bodova);
		r.setRacun(Ukupan_broj_bodova);// prebaci u racun trenutrni broj bodova
		r.otkljucaj();                    //otkljuca igru
		Ukupan_broj_bodova = r.getRacun(); //po zavrsetku igre u Ukupan_broj_bodova koji i ostale igre treba da koriste
		r.Sacuvaj_u_fajl();	//upise trenutno stanje racuna
		system("cls");
		system("Color 0F");
		Meni();								//pozove meni() da igrac igra opet ovu igru ili neke druge
	}
	/*IGRA2*/	  else if (znak == '2')
	{

		std::string kljuc; //kljuc
		do
		{
			std::cout << "Unesite KLJUC igre, [xxxx-xxxx-xxxx-xxxx]: ", std::cin >> kljuc;
		} while (!Kviz::ProvjeraKljuca(kljuc));

		std::list < Kviz >Lista = Igra2(); //Funkcija koja vraca uredjenu listu pitanja za IGRU 2

	Jump: system("cls");
		std::cout << "\t\t\t\t KVIZ" << std::endl;
		MeniIgre();

		char znak = Unos(5, '1', '2', '3', '0', '9');
		if (znak == '1')
		{
			system("cls");//Brise sve u konzoli

			std::list<Kviz>::iterator it;
			int i = 0, tacnih_odgovora = 0;
			std::vector<int> Niz; //Niz u koji se smjesta slucajno odabran broj

			do {
				std::srand(time(NULL));
				int v = rand() % 16; //Slucajan broj 0 - 16

				if (!PretraziNiz(Niz, v)) //Pretrazimo prethodni niz, ako je je taj slucajno odabran broj
				{						 //prethodno vec "odabran", tada izvlacimo novi broj
					Niz.push_back(v);   //u suprotnom, stavljamo broj u NIZ, i tako oznacavamo da je to pitanje izvuceno
					std::advance(it = Lista.begin(), v);//U listi su smjestena pitanja, nadjemo pitanje pod rednim brojem 'v', i ispisemo ga
					tacnih_odgovora += it->Postavi_pitanje(i++ + 1);
				}
			} while (i < 5); //Postavljanje pitanja

			if (tacnih_odgovora == 5)//Ukoliko je svih 5 pitanja tacno, korisnik dobija 50 bodiva bonusa
				Kviz::Total += 50;
			Ukupan_broj_bodova += Kviz::Total;

			std::cout << "Tacnih odgovora: " << tacnih_odgovora << std::endl;
			std::cout << "Ukupan broj osvojenih bodova: " << Kviz::Total << std::endl << std::endl;

			//Bodovi koji cuvamo u statistici.
			IGRA_[1].insert(std::pair<int, std::string>(Kviz::Total, __TIMESTAMP__));
			Sacuvaj_bodove_u_fajl(Ukupan_broj_bodova);

			Kviz::Total = 0;//Prilikom sljedeceg pokretanja igre, pocetni broj bodova je 0 

			Nazad(); //Funkcija kojom se vracamo korak unazad

			if (Unos(2, '0', '9') == '0') //Unos znaka.
				goto Jump;
			else
				system("cls"), Meni();
		}
		else if (znak == '2')
		{
			system("cls");
			Kviz::Info();
			Nazad();
			if (Unos(2, '0', '9') == '0')
				goto Jump;
			else
				system("cls"), Meni();
		}
		else if (znak == '3')
		{
			system("cls");
			std::cout << "Podesavanje" << std::endl;
			Nazad();
			if (Unos(2, '0', '9') == '0')
				goto Jump;
			else
				system("cls"), Meni();
		}
		else if (znak == '0')
		{
			goto Jump1; Igre();
		}
		else
		{
			system("cls");
			Meni();
		}
	}
	else if (znak == '9' || znak == '0') { system("cls"); Meni(); }
}

