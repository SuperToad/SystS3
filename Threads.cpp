#include <iostream>
#include <cmath>
#include <pthread.h>
using namespace std;
//compilation : g++ -Wall threads.cpp -o threads -lpthread

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
	const double DIVISIONS = 3000000;
	
	// Nombre de threads crées
	const int nbThreads = 10;
/********************************************************************************************************************/
double pas = ((double)(borne2 - borne1) / DIVISIONS);
int incr = 0;

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

// Calcul du sigma
// La fonction que les threads utilisent
void * sigma (void * valeur)
{
	double * val = (double * ) valeur;
	double * tempSigma = new double();
	*tempSigma = 0;

	cerr << 1+((DIVISIONS/nbThreads)*(*val)) << " "<< (DIVISIONS/nbThreads)*((*val)+1) << "\n";

	for(int i=1+((DIVISIONS/nbThreads)*(*val)); i< (DIVISIONS/nbThreads)*((*val)+1);i++)
	{
		(*tempSigma) += f((borne1+i*pas), tableau, degre);
		incr++;
	}
	cerr << "Fin thread " << "\n";
	return (tempSigma);
}

int main()
{
	pthread_t thtab[nbThreads];

	double aire = 0;
	double totSigma = 0;

	double * t = new double[nbThreads];
	
	for (unsigned int i=0; i<nbThreads; ++i)
		t[i] = i;
	
	for (unsigned int th=0; th<nbThreads; th++)
	{
		pthread_create(&thtab[th], NULL, sigma, (void*) &t[th]);
		cerr << "lancement du thread " << th << "\n";
	}

	cerr << "Tous les threads ont été lancés\n";

	void * r;	
	double * res;
	for (unsigned int th=0; th<nbThreads; ++th) {
			pthread_join(thtab[th], &r);
			res = (double*) r;
			
			totSigma += (*res);
			cerr << "arrivée du thread " << th << " r= " << *res << " result+ = " << totSigma << "\n"; 
	}
	cerr << incr << endl;
	// Calcul de l'intégrale
	aire = pas * (((f(borne1, tableau, degre) + f(borne2, tableau, degre))/2) + totSigma);
	cout << aire << endl;

	return 0;
}
