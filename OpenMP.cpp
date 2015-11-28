//RRAFFIN
//Compilation :
//g++ -Wall -fopenmp OpenMP.cpp -o OpenMP
//execution :
//export OMP_NUM_THREADS=4 ; ./OpenMP

#include <omp.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include <time.h>

#define MAXSIZE 2000

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

int main() {
	
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
	
/********************************************************************************************************************/
	double pas = ((double)(borne2 - borne1) / DIVISIONS);

	double aire = 0;
	double sigma = 0;

#pragma omp parallel
{  // Debut parallelisation
	const int thread_id = omp_get_thread_num();
	const int nthread = omp_get_num_threads(); // Do we really have to do this for each thread?

	std::cerr << "Thread n°"<< omp_get_thread_num() <<"\n";

	//#pragma omp for
        //for(int i=1+((DIVISIONS/4)*thread_id); i< (DIVISIONS/4)*(thread_id+1);i++)
	for(int i=1+((DIVISIONS/nthread)*thread_id); i< (DIVISIONS/nthread)*(thread_id+1);i++)
	{
        	sigma += f((borne1+i*pas), tableau, degre);
		//cerr << f((borne1+i*pas), tableau, degre) << endl;
	}

} // Fin parallelisation
	aire = pas * (((f(borne1, tableau, degre) + f(borne2, tableau, degre))/2) + sigma);
	std::cout << aire << "\n";

	return 0;
}
