#include "rulet.h"
void Rulet::meni() {
	std::cout << "=================================================================";
	std::cout << std::endl;
	std::cout << " Boje (Crvena-Crna)  [P]                    Otkazi igru [O]" << std::endl;
	std::cout << " Pogodi Trecinu:     [T]" << std::endl;
	std::cout << " Podogi broj:        [B]" << std::endl;
	std::cout << " Kraj:               [K]" << std::endl;
	std::cout << " Igrate Rulet:          RACUN:" << racun << std::endl;
	std::cout << "=================================================================";
	std::cout << std::endl;
}
double Rulet::getRacun() { return racun; }
double Rulet::getUlog() { return ulog; }
void Rulet::setRacun(int x) { racun = x; pocetni_racun = x; }
void Rulet::setUlog(int x) { ulog = x; }
Rulet::Rulet(int x, int y, int o) :racun(x), kraj(y), otkazi_kljuc(o) {
	strcpy(kljuc, "1111-2222-3333-4444"); otkljucana = 0;
}
Rulet::Rulet(char* pom, int x, int y, int o) : racun(x), kraj(y), otkazi_kljuc(o) {
	strcpy(kljuc, pom); otkljucana = 0;
}



//ovo mi ne treba i ne koristi se
void Rulet::Sacuvaj_u_fajl()
{

	std::ofstream File("Statistika_rulet_CSV.txt");//ovo mi ne treba i ne koristi se
	if (File)
	{
		//for (int i = 0; i < 4; i++)//Ucitavamo statistiku igara, prikazuje se statistika sve 4 igre, jedna ispod druge.
		//{
			File << std::endl;
			//File << "\tIGRA " << i + 1 << std::endl; //Statistika i-te igre.
			
			std::map<int, std::string>::iterator it = statistika_rulet.begin();
			int brojac = 0; //Pom promjenjiva, koristi se pri ispisu.
			for (it = statistika_rulet.begin(); it != statistika_rulet.end() && brojac <= 10; ++it)
				File << ++brojac << ".)  " << it->first << "  " << it->second << '\n';
		}
		File.close(); //Zatvaranje fajla
	
}
// u fajl upise broj ulozenih ili dobijenih bodova  i vrijeme
void Rulet::Sacuvaj_u_fajl(int x)
{

	std::fstream File("Statistika_rulet.txt", std::ios_base::app);
	if (File)
	{
		time_t curr_time;
		tm * curr_tm;
		time(&curr_time);
		curr_tm = localtime(&curr_time);
		char temp[50];
		strftime(temp, 50, "%B %d, %Y, %T", curr_tm);
		File << x << " " << temp;
		File << std::endl;
	}
	File.close(); //Zatvaranje fajla
}


//pokusaj za statistiku :D
/*
void Rulet::Sacuvaj_u_fajl_jedan()
{

	std::ofstream File("Statistika_rulet_CSV.txt");
	if (File)
	{

		File << std::endl;

		//std::map<int, std::string>::iterator it = statistika_rulet.begin();
		int brojac = 0; //Pom promjenjiva, koristi se pri ispisu.
		//for (it = statistika_rulet.begin(); it != statistika_rulet.end() && brojac <= 10; ++it)
	//	File << ++brojac << ".)  " << statistika_rulet.first << "  " << statistika_rulet._Get_data.second << '\n';

		File.close(); //Zatvaranje fajla
		

	}
}
*/

void Rulet::zvukLose() {
	PlaySound(TEXT("lose.wav"), NULL, SND_SYNC);
}
void Rulet::zvukWin()
{
	PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
}

// pomocna fja koja provjeri da li u stringu postoji nesto sto nije broj
int provjera(char* string)
{
	int len = strlen(string);
	for (int i = 0; i < len; i++)
	{
		if (string[i]<'0' || string[i]>'9')
			return 0;
	}
	return 1;
}

int Rulet::ulozi() {
	do {
		char pom[100];
		if (racun <=0)//ne mozemo uloziti manje od 0
			return 0;
		std::cout << "Unesite ulog:";
		std::cin >> pom;
		int x = 0;
		if (provjera(pom))//provjera da li su ineseni brojeva ili ima i neko slovo
		{
			int len = strlen(pom);
			std::string pomString(pom);
			x = stoi(pomString, nullptr, 10);
		}
		ulog = x;// x je 0 u ovom slucaju , ako je string, da vrati opet na unos
	} while (ulog < 1 || (racun - ulog) < 0);
	racun -= ulog;
	if (racun < 0)
		return 0;
	else return 1;
}

void Rulet::otkljucaj()
{
	system("color 1f");
	char pom[100];
	if (!otkazi_kljuc)//ako nismo otkazali igru onda unosimo kljuc
	{
		if (!otkljucana) {
			std::cout << " Unesite kljuc: xxxx-xxxx-xxxx-xxxx" << std::endl;
			std::cin >> pom;
			if (!strcmp(pom, kljuc))
			{
				std::cout << " Uspjesno ste otkljucali igru!" << std::endl;
				otkljucana = 1;
				igraj();
			}
			else {

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
				std::cout << " Pogresan kljuc!";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
			}
		}

		else if (otkljucana && (!otkazi_kljuc))
		{
			igraj();
		}
	}
	else {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
		std::cout << " Otkazali ste igru, morate ponovo instalirati!";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	}
}
int Rulet::onemoguci()
{
	if (racun > (0.6*pocetni_racun))
	
		return 1;

	else return 0;




}



int generisi_broj()
{
	srand(time(NULL));
	int broj;
	broj = rand();// generisanje slucajno izvucenog broja
	broj = broj % 37;
	return broj;
}

// fja koja ispisuje kuglicu u odredjenoj boji
void Rulet::odredi_boju(int broj)
{
	if (broj == 0) {//ZELENA
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 175);
		std::cout << "(" << broj << ")" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	}
	else if (broj % 2 == 0)//CRVENA
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
		std::cout << "(" << broj << ")" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	}
	else//CRNA
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::cout << "(" << broj << ")" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	}
}
void Rulet::igraj() {
	kraj = 1;
	system("color 1f");
	if (!otkazi_kljuc)// ako nismo otkazali igru onda igramo, a otkljucali smo u fji otkljucaj
	{
		do
		{
			meni();//ispis menija
			char c;
			std::cin >> c;// izbor opcije
			
			int broj;
			
			if (c == 'T' || c == 't')
			{
				int interval;
				char pom[100];
				int x = 0;
				if (this->ulozi())
				{
					std::cout << "Izaberite interval:(1-12)(1) (13-24)(2) (25,36)(3)" << std::endl;
					do
					{
						std::cout << "Unesite interval:";
						std::cin >> pom;
						if (provjera(pom))
						{
							int len = strlen(pom);
							std::string pomString(pom);
							interval = stoi(pomString, nullptr, 10);
						}
						else interval = 5;//da nas opet vrati na unos, jer je granica 4, a unos nije bio korektan
					} while (interval > 3 || interval < 0);
				ponovi1:
					broj = generisi_broj();

					if (broj > 0 && broj < 13)
						x = 1;
					else if (broj > 12 && broj < 25)
						x = 2;
					else if (broj == 0)
						x = 0;
					else x = 3;

					if (x == interval)
					{
						
						int bodovi = ulog * 3;
						racun += bodovi;
						if (onemoguci())
						{
							racun -= bodovi;
							goto ponovi1;
						}
						zvukWin();
						odredi_boju(broj);
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));
					}
					else {
						zvukLose();
						int bodovi = -ulog;
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));						odredi_boju(broj);//izbaci odredi boju vise puta
					}
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
					std::cout << "Nemate na vise na racunu!" << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
					kraj = 0;
				}
			}
			if (c == 'o' || c == 'O')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
				std::cout << " Otkazali ste igru, morate ponovo instalirati!";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
				kraj = 0;
				otkazi_kljuc = 1;
			}
			if (c == 'P' || c == 'p')
			{
				char boja;
				if (this->ulozi())
				{
					do {
						std::cout << "Izaberite boju:" << std::endl << "          crvena[R]  crna[B]:";
						std::cin >> boja;
					} while (boja != 'r'&&boja != 'R'&&boja != 'b'&&boja != 'B');
				ponovi2:
					broj = generisi_broj();

					if ((broj != 0) && (broj % 2 == 0) && (boja == 'r' || boja == 'R'))
					{
						int bodovi = ulog * 2;
						racun += bodovi;
						if (onemoguci())
						{
							racun -= bodovi;
							goto ponovi2;
						}
						zvukWin(); 
						odredi_boju(broj);
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));						
						
					}
					else if ((broj % 2 == 1) && ((boja == 'b') || boja == 'B'))
					{
						int bodovi = ulog * 2;
						racun += bodovi;
						if (onemoguci())
						{
							racun -= bodovi;
							goto ponovi2;
						}
						zvukWin();
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));						racun += ulog * 2;
						odredi_boju(broj);
					}
					else {
						zvukLose();
						int bodovi = -ulog;
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));						odredi_boju(broj);
					}
				}

				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
					std::cout << "Nemate na vise na racunu!" << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
					kraj = 0;
				}
			}
			if (c == 'B' || c == 'b')
			{
				int Uneseni_broj;
				char pom[100];
				if (this->ulozi()) {
					do
					{
						std::cout << "Unesite broj:";
						std::cin >> pom;
						if (provjera(pom))
						{
							int len = strlen(pom);
							std::string pomString(pom);
							Uneseni_broj = stoi(pomString, nullptr, 10);
						}
						else Uneseni_broj = 37;//da nas vrati ponovo na unos, jer je max 36, a uneseni su i zabranjeni znakovi
					} while (Uneseni_broj < 0 || Uneseni_broj>36);
				ponovi3:
					broj = generisi_broj();
					if (broj == Uneseni_broj)
					{
						int bodovi = ulog * 37;
						racun += bodovi;
						if (onemoguci())
						{
							racun -= bodovi;
							goto ponovi3;
						}
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));						zvukWin();
						odredi_boju(broj);
					}
					else
					{
						zvukLose();
						int bodovi = -ulog;
						Sacuvaj_u_fajl(bodovi);
						statistika_rulet.insert(std::pair<int, std::string>(bodovi, __TIMESTAMP__));						odredi_boju(broj);
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
					std::cout << "Nemate na vise na racunu!" << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
					kraj = 0;
				}
			}
			if (c == 'k' || c == 'K')	{	kraj = 0;}

		} while (kraj);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
		std::cout << " Otkazali ste igru, morate ponovo instalirati!";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	}
}


