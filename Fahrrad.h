#pragma once 

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad();
	Fahrrad(string sName, double dMaxGeschwindigkeit);
	
	//gibt fahrzeug daten aus
	void vAusgeben(ostream& out) const override;

	//gibt aktuelle geschwindigkeit zurück
	double dGeschwindigkeit() const override;

	//zeichnet Fharrad
	void vZeichnen(const Weg&) const override;
};

