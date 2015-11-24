#include <iostream>
#include <cmath>
using namespace std;

// Retourne la valeur de x
double f(double x, double tableau[], int degre)
{
	int puissance = degre;
	double resultat = 0;
	for (int i=0; i<degre+1; i++)
	{
		resultat += pow(x, puissance)*tableau[i];
		puissance -= 1;
	}
	return resultat;
}

int main()
{
/*****************************************************PARAMETRES*****************************************************/
	// Degre du polynome
	int degre = 5;
	// Valeurs de chaque indice dans un tableau de taille degre+1
	double tableau[] = {5, 6, 18, 12, 3, 1};

	// Bornes min et max
	double borne1 = 0.0;
	double borne2 = 5.0;

	// Nombre de divisions qui seront effectuees
	// Définit la précision
	const double DIVISIONS = 300000000;
/********************************************************************************************************************/

	double pas = ((double)(borne2 - borne1) / DIVISIONS);

	double aire = 0;
	double sigma = 0;

	// Calcul de sigma
	for(int i=1; i<DIVISIONS-1;i++)
	{
        sigma += f((borne1+i*pas), tableau, degre);
	}

	// Calcul de l'intégrale
	aire = pas * (((f(borne1, tableau, degre) + f(borne2, tableau, degre))/2) + sigma);
	cout << aire << endl;

	return 0;
}
