#include <iostream>
#include <cmath>
#include <ctime>
#include <sys/time.h>
using namespace std;
//compilation : g++ -Wall sequential.cpp -o sequential

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
	struct timeval begin, end;
	gettimeofday(&begin, NULL);
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
	const int DIVISIONS = 300000;
/********************************************************************************************************************/

	double pas = ((double)(borne2 - borne1) / DIVISIONS);

	double aire = 0;
	double sigma = 0;

	// Calcul de sigma
	for(int i=1; i<DIVISIONS;i++)
	{
        	sigma += f((borne1+i*pas), tableau, degre);
	}

	// Calcul de l'intégrale
	aire = pas * (((f(borne1, tableau, degre) + f(borne2, tableau, degre))/2) + sigma);
	cout << "L'aire vaut : " << aire << endl;
	
	gettimeofday(&end, NULL);
	double totalTime = ((double)(1000*(end.tv_sec-begin.tv_sec)+((end.tv_usec-begin.tv_usec)/1000)));
	//difftime(end, begin);
	cout << "Temps d'execution : " << totalTime << endl;
	
	return 0;
}
