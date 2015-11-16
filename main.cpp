#include <iostream>
#include <cmath>
using namespace std;

int f(double x, double tableau[], int degre)
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

	int degre;
	cout << "Quel est le degre du polynome? : \n";
	cin >> degre;
	double tableau[degre+1];


	double valeur;
	cout << "Entrez les differentes valeurs : \n";

	for(int i=0; i<degre+1; i++)
	{
		cin >> valeur;
		cout << "\n";
		tableau[i] = valeur;
	}

	int borne1, borne2;
	cout << "Entrez les deux bornes : \n";
	cin >> borne1;
	cout << "\n";
	cin >> borne2;

	const double DIVISIONS = 300000000;

	double aire = 0;

	/*for(double i=borne1; i<borne2; i+=DIVISIONS)
	{
		aire += (DIVISIONS)*((f(i, tableau, degre)+f(borne1+DIVISIONS, tableau, degre))/2);
		cout << i << "\n";
	}*/

	double sigma = 0;
	for(int i=1; i<DIVISIONS-1;i++)
	{
        sigma += f(((double)borne1+(double)i*((double)(borne2-borne1)/DIVISIONS)), tableau, degre);
	}

	aire = ((double)(borne2 - borne1) / DIVISIONS) * (((f(borne1, tableau, degre) + f(borne2, tableau, degre))/2) + sigma);
	cout << aire;

	return 0;
}

