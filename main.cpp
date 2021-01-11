#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <random>

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "SimuClient.h"
#include "vertagt_liste.h"

using namespace std;

void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();



//globale Uhr
double dGlobaleZeit = 0.0;

//Rundungstoleranz bei double-Vergleichen: Wähle hinreichend kleines Epsilon
double dToleranz = 0.001;

int main()
{
	vAufgabe_6a();
	
	return 0;
}

void vAufgabe_1()
{
	Fahrzeug tFahrzeug;
	Fahrzeug tFahrrad("Fahrrad");

	Fahrzeug* pFahrzeug = new Fahrzeug();
	Fahrzeug* pMotorrad = new Fahrzeug("Motorrad");
	delete pFahrzeug;
	delete pMotorrad;

	auto pRoller =  make_unique<Fahrzeug>("Roller");
	auto pCamper =  make_unique<Fahrzeug>("Camper");

	auto pLexus =  make_shared<Fahrzeug>("Lexus");
	auto pLaster =  make_shared<Fahrzeug>();

	// Erzeugen eines zweiten Pointers auf Laster.
	auto pLaster2 = pLaster;
	 cout << "Anzahl der Laster-Referenzen: " << pLaster.use_count() <<  "\n";

	auto pCamper2 =  move(pCamper);

	 vector< unique_ptr<Fahrzeug>> uVector;
	uVector.push_back( move(pRoller));
	uVector.push_back( move(pCamper2));
	 cout << "Clear Vektor aus  unique_ptr<Fahrzeug>" <<  "\n";
	uVector.clear();

	 vector< shared_ptr<Fahrzeug>> sVector;
	// Neuer shared_ptr auf Lexus im Vektor.
	sVector.push_back(pLexus);
	 cout << "Anzahl der Lexus-Referenzen: " << pLexus.use_count() <<  "\n";
	// Der shared_ptr von pLaster wird in den Vektor verschoben.
	sVector.push_back( move(pLaster));
	 cout << "Anzahl der Laster-Referenzen (mit Vektor und move): " << pLaster2.use_count() <<  "\n";
	 cout << "Clear Vektor aus  shared_ptr<Fahrzeug>" <<  "\n";
	//zweiter shared_ptr verschobener pLaster delete
	sVector.clear();

	 cout << "Scope Ende" <<  "\n";
}

void vAufgabe_1a()
{
	 vector< unique_ptr<Fahrzeug>> vector;

	vector.push_back( make_unique<Fahrzeug>("Volkswagen", 40.0));

	vector.push_back( make_unique<Fahrzeug>("AUTO3", 30.0));

	vector.push_back( make_unique<Fahrzeug>("VolvoTruck", 25.0));
	 cout <<  "\n";

	double intervals[5] = { 0.2, 0.5, 1.0, 0.1, 0.7 };
	for (auto dInterval : intervals) {
		dGlobaleZeit += dInterval;

		Fahrzeug::vKopf();
		for ( unique_ptr<Fahrzeug>& fahrzeug : vector) {
			fahrzeug->vSimulieren();
			//fahrzeug->vAusgeben();
			 cout <<  "\n";
		}
		 cout <<  "\n";
	}
}

double dRandom(double min, double max)
{
	double random = ((double) rand() / (double)RAND_MAX);
	return random * (max - min) + min;
}

void vAufgabe_2()
{
	int iPKWs, iRaeder;

	 cout << "Wieviele PKWs sollen erstellt werden?" <<  "\n";
	 cin >> iPKWs;
	 cout << "Wieviele Fahrr" << (unsigned char)132 << "der sollen erstellt werden?" <<  "\n";
	 cin >> iRaeder;

	 vector< unique_ptr<Fahrzeug>> fahrzeugVector;

	for (int i = 0; i < iPKWs; i++) {
		fahrzeugVector.push_back( make_unique<PKW>(
			"PKW" +  to_string(i + 1),
			dRandom(60.0, 180.0),
			dRandom(4.0, 13.8),
			dRandom(35.0, 80.7)
			));
	}

	for (int i = 0; i < iRaeder; i++) {
		fahrzeugVector.push_back( make_unique<Fahrrad>(
			"RAD" +  to_string(i + 1),
			dRandom(12.0, 39.6)
			));
	}

	bool bGetankt = false;
	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += dRandom(0.1, 0.7);

		if (!bGetankt and dGlobaleZeit >= 3.0) {
			for ( unique_ptr<Fahrzeug>& fahrzeug : fahrzeugVector) {
				fahrzeug->dTanken( numeric_limits<double>::infinity());	
			}
			bGetankt = true;
		}

		 cout <<  "\n" << "Globale Zeit: " <<  setprecision(2) <<  setiosflags( ios::fixed) << dGlobaleZeit <<  "\n";
		Fahrzeug::vKopf();
		for ( unique_ptr<Fahrzeug>& fahrzeug : fahrzeugVector) {
			fahrzeug->vSimulieren();
			//fahrzeug->vAusgeben();
			 cout <<  "\n";
		}
	}
}

void vTriggerCopyConstructor(Fahrzeug fahrzeug)
{
}

void vAufgabe_3()
{
	auto Volkswagen =  make_unique<PKW>("Volkswagen", 129.9, 7.6, 55.0);

	auto BMWM =  make_unique<PKW>("BMWM", 95.7, 6.1, 60.0);

	auto rad =  make_shared<Fahrrad>("RAD1", 18.5);

	dGlobaleZeit = 0.5;
	Volkswagen->vSimulieren();
	BMWM->vSimulieren();
	rad->vSimulieren();

	Fahrzeug::vKopf();
	 cout << *Volkswagen <<  "\n"
		<< *BMWM <<  "\n"
		<< *rad <<  "\n";

	if (*BMWM < *Volkswagen) {
		 cout <<  "\n" << "BMWM < Volkswagen" <<  "\n";
	}

	if (*rad < *BMWM) {
		 cout << "RAD < BMWM" <<  "\n";
	}

	*BMWM = *Volkswagen;

	 cout <<  "\n" << "Gleichsetzen von BMWM und Volkswagen:" <<  "\n";
	Fahrzeug::vKopf();
	 cout << *Volkswagen <<  "\n"
		<< *BMWM <<  "\n"
		<< *rad <<  "\n" <<  "\n";

}

void vAufgabe_4()
{
	auto weg =  make_unique<Weg>("a40", 356.9);

	Weg::vKopf();
	 cout << *weg <<  "\n";
}

void vAufgabe_5()
{
	auto weg =  make_unique<Weg>("a40", 30);

	weg->vAnnahme(make_unique<Fahrrad>("RAD1", 15));

	weg->vAnnahme(make_unique<Fahrrad>("RAD2", 25), 2.0);

	weg->vAnnahme(make_unique<PKW>("Volkswagen", 100, 5, 60));

	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += 0.5;

		weg->vSimulieren();

		Weg::vKopf();
		 cout << *weg <<  "\n";
	}
}

void vAufgabe_6()
{
	bInitialisiereGrafik(1600, 1000);

	int iKoordinaten[4] = { 700, 250, 200, 250 };

	bZeichneStrasse("a40", "B1", 500, 2, iKoordinaten);

	auto a40 = make_unique<Weg>("a40", 500, Tempolimit::autobahn);

	a40->vAnnahme(make_unique<Fahrrad>("RennradScotts", 55), 2.0);

	a40->vAnnahme(make_unique<PKW>("Volkswagen", 150, 7, 80), 3.0);

	a40->vAnnahme(make_unique<Fahrrad>("RennradCanyon", 25));

	auto B1 =  make_unique<Weg>("B1", 500, Tempolimit::ausserorts);

	B1->vAnnahme(make_unique<PKW>("BMWM3", 75, 8, 20));

	B1->vAnnahme(make_unique<PKW>("BMWM2", 155, 7, 70), 3.0);

	B1->vAnnahme(make_unique<Fahrrad>("RennradPoison", 23));

	Weg::vKopf();
	 cout << *a40 <<  "\n"
		<< *B1 <<  "\n";

	while (dGlobaleZeit < 10.0) {
		dGlobaleZeit += 0.4;
		vSetzeZeit(dGlobaleZeit);
		 cout <<  "\n" << "Globale Zeit: " <<  setprecision(2) << dGlobaleZeit <<  "\n";

		a40->vSimulieren();
		B1->vSimulieren();

	}
}

void vAufgabe_6a()
{
	vertagt::VListe<int> liste;

	static mt19937 device(0);
	uniform_int_distribution <int> dist(0, 10);

	for (int i = 0; i < 7; i++) {
		liste.push_back(dist(device));
	}

	liste.vAktualisieren();

	 cout << "Liste:" <<  "\n";
	for (auto& iInteger : liste) {
		 cout << iInteger <<  "\n";
	}

	for (auto it = liste.begin(); it != liste.end(); it++) {
		if (*it > 5) {
			liste.erase(it);
		}
	}

	 cout <<  "\n" << "Liste:" <<  "\n";
	for (auto& iInteger : liste) {
		 cout << iInteger <<  "\n";
	}

	liste.vAktualisieren();

	 cout <<  "\n" << "Liste:" <<  "\n";
	for (auto& iInteger : liste) {
		 cout << iInteger <<  "\n";
	}

	liste.push_front(dist(device));
	liste.push_front(dist(device));
	liste.push_back(dist(device));
	liste.push_back(dist(device));
	liste.vAktualisieren();

	 cout <<  "\n" << "Liste:" <<  "\n";
	for (auto& iInteger : liste) {
		 cout << iInteger <<  "\n";
	}
}