#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>//napraviti i za linux
#include <MMSystem.h>
#include <string>
#include <conio.h>
#include <map>
#include <fstream>
#include <ctime>
class Rulet
{
private:

	double racun;
	double ulog;
	int kraj;
	int otkazi_kljuc;
	int otkljucana;
	char kljuc[19];
	double pocetni_racun;//treba za 60%

	//std::string kljuc;
public:
	
	std::map<int, std::string> statistika_rulet;
	Rulet(int = 10, int = 1, int = 0);
	Rulet(char*, int = 10, int = 1, int = 0);
	//Rulet(char*);
	void meni();
	void setRacun(int);
	double getRacun();
	void setUlog(int);
	double getUlog();
	void igraj();
	int ulozi();
	void otkljucaj();
	void zvukWin();
	void zvukLose();
	void odredi_boju(int);
	void Sacuvaj_u_fajl();
	void Sacuvaj_u_fajl(int);
	//void Sacuvaj_u_fajl_jedan();
	int onemoguci();
};

