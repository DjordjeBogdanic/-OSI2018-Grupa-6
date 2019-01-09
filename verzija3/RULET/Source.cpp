#define _CRT_SECURE_NO_WARNINGS
#include "Uvod.h"
void pomocna() {
	std::ofstream file("Statistika_rulet.txt");
	{if (file)
		file.close();
	}
}
int main()
{
	system("Color 0F"); //Postavlja boju konzole/teksta (Crna konzola)
	Uvod UVOD;
	pomocna();//da pri svakom pokretanju igre fajl Statistika_rulet bude prazan
	UVOD.Meni();
	system("pause");
}