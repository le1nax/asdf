#pragma once 

#include "Simulationsobjekt.h"
#include "Verhalten.h"
#include <memory>

using namespace std;

class Fahrzeug : public Simulationsobjekt
{

protected:
	double p_dMaxGeschwindigkeit = 30.0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dAbschnittStrecke = 0;

	unique_ptr<Verhalten> p_pVerhalten;

public:
	Fahrzeug();	//Standardkonstruktor
	Fahrzeug(string sName);
	Fahrzeug(string sName, double dMaxGeschwindigkeit);

	void vAusgeben(ostream& out) const override; //gibt fahrzeugspezifische Daten aus
	virtual double getGesamtZeit() const;
	static void vKopf(); //gibt einen Header f�r die Ausgabe der Fahrzeugdaten aus
	virtual void vSimulieren() override;	//simuliert das Fahrzeugobjekt und aktualisiert entsprechende Attribute
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());	//realsisiert das Auftanken eines Fahrzeugs mit Menge dMenge
	virtual double getGesamtStrecke() const; // gibt die Gesamtstrecke zur�ck
	virtual double getAbschnittStrecke() const; //gibt die Abschnitts Strecke zur�ck
	virtual double dGeschwindigkeit() const; //gibt die aktuelle Geschwindigkeit des Fahrzeugs zur�ck
	void vNeueStrecke(Weg&, double dStartZeit = numeric_limits<double>::infinity());
	virtual void vZeichnen(const Weg&) const;


	bool operator<(const Fahrzeug& fahrzeug) const; //�berl�dt den <-Operator: gibt true zur�ck, 
													//falls p_dGesamtStrecke von 1.Operanden kleiner als die des rechten Operanden
	Fahrzeug& operator=(const Fahrzeug& fahrzeug); 	//�berl�dt den =-Operator: Zuweisung eines Objekts zu einem anderen
};

//�berladung des Ausgabestream-operators f�r die Klasse Fahrzeug
//�berladung im globalen Bereich, das sonst der erste Parameter ein this-Zeiger w�re, was in diesem Fall nicht sinnvoll ist
ostream& operator<<(ostream& out, const Fahrzeug& fahrzeugReference);
