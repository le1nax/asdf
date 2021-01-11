#include "PKW.h"
#include "Verhalten.h"
#include "Weg.h"
#include "SimuClient.h"
#include <iomanip>

extern double dGlobaleZeit;
extern double dToleranz;

PKW::PKW(string initName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
	Fahrzeug(initName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(p_dTankvolumen / 2)
{
	cout << "PKW-Konstruktor mit Parameter p_sName, p_dMaxGeschwindigkeit, p_dVerbrauch und  p_dTankvolumen aufgerufen" << endl;
	cout << "Objekt der Klasse PKW mit ID " << p_iID << ", Name " << p_sName
		<< ", MaxGeschwindigkeit " << p_dMaxGeschwindigkeit << " , Verbrauch " << p_dVerbrauch << " und Tankvolumen "
		<< dTankvolumen << " erzeugt\n" << endl;
}


double PKW::dTanken(double dMenge)
{
	if ((dMenge + p_dTankinhalt) > (p_dTankvolumen - dToleranz))
	{
		double dGetankteMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dGetankteMenge;
	}
	else
	{
		p_dTankinhalt = p_dTankinhalt + dMenge;
		return dMenge;
	}
}

void PKW::vZeichnen(const Weg& weg) const
{
	bZeichnePKW(getName(), weg.getName(), getAbschnittStrecke() / weg.getLaenge(), dGeschwindigkeit(), p_dTankinhalt);
}


void PKW::vSimulieren()
{
	//Fahrzeug schon bearbeitet?

	double dAbstand = fabs(p_dZeit - dGlobaleZeit);
	if ((dAbstand < dToleranz) && (p_dZeit != 0) && (dGlobaleZeit != 0))
	{
		cout << "Fahrzeug bereits simuliert." << endl;
		return;
	}

	//Tankinhalt = 0:
	if ((p_dTankinhalt >= (0 - dToleranz)) && (p_dTankinhalt <= (0 + dToleranz)))
	{
		cout << "Tank von Fahrzeug " << this->getName() << " leer." << endl;
		double dVerstricheneZeit = dGlobaleZeit - p_dZeit;
		p_dZeit = dGlobaleZeit;
		p_dGesamtZeit = p_dGesamtZeit + dVerstricheneZeit;
	}
	//Tankinhalt = 0:
	else
	{
		double dVerstricheneZeit = dGlobaleZeit - p_dZeit;

		double dVerbrauchteSpritMenge = p_dMaxGeschwindigkeit * p_dVerbrauch * dVerstricheneZeit * 0.01;

		//setzt Tankinhalt auf 0, falls aufgebraucht
		if ((p_dTankinhalt - dVerbrauchteSpritMenge) <= (0 + dToleranz))
		{
			p_dTankinhalt = 0.0;

		}
		else
		{
			p_dTankinhalt = p_dTankinhalt - dVerbrauchteSpritMenge;
		}
		p_dGesamtStrecke = p_dGesamtStrecke + (p_dMaxGeschwindigkeit * dVerstricheneZeit);
		p_dZeit = dGlobaleZeit;
		p_dGesamtZeit = p_dGesamtZeit + dVerstricheneZeit;
	}
}

void PKW::vAusgeben(ostream& out) const
{
	//berechne Gesamtverbrauch
	double dGesamtVerbrauch = p_dGesamtStrecke * p_dVerbrauch * 0.01;
	Fahrzeug::vAusgeben(out);
	out << "|" << setw(15) << setprecision(2) << setiosflags(ios::fixed) << p_dTankinhalt << "|";
	out << "|" << setw(20) << setprecision(2) << setiosflags(ios::fixed) << dGesamtVerbrauch << "|";
	out << "|" << setw(25) << setprecision(2) << setiosflags(ios::fixed) << p_dMaxGeschwindigkeit << "|";
}

double PKW::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

PKW& PKW::operator=(const PKW& pkw)
{
	Fahrzeug::operator=(pkw);
	p_dTankinhalt = pkw.p_dTankinhalt;
	p_dVerbrauch = pkw.p_dVerbrauch;
	p_dTankvolumen = pkw.p_dTankvolumen;
	return *this;
}