#include <iostream>
#include <cmath>
using namespace std;

int f(float x, float tableau[], int degre)
{
	int puissance = degre;
	float resultat = 0;
	for (int i=0; i<degre; i++)
	{
		resultat += pow(tableau[i], puissance);
		puissance -= 1;
	}
	return resultat;
}

int main()
{
	
	int degre;
	cout << "Quel est le degre du polynome? : \n";
	cin >> degre;
	float tableau[degre+1];
	
	
	float valeur;
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
	
	const float DIVISIONS = (borne1 - borne2)/3;
	
	float aire = 0;
	for(float i=borne1; i<borne2; i+=DIVISIONS)
	{
		aire += (DIVISIONS)*((f(i, tableau, degre)+f(borne1+DIVISIONS, tableau, degre))/2);
		cout << i << "\n";
	}
	
	cout << aire << "\n"	;
	
	return 0;
}

