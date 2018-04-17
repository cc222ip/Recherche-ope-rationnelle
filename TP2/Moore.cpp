#include "graph.hpp"
#include <iostream>

using namespace std;

Resultat Graph::Moore_Dijkstra(int sommet_depart)
{

	//tableau C : sommets de G pour lesquels le plus court chemin est connu
	bool *C = new bool [size()];
	for (int i = 0; i < size(); i++)
		C[i] = i == sommet_depart;
	
	//tableau d : tableau des valeurs du plus courts chemin
	int *d = new int  [size()];
	for (int i = 0; i < size(); i++)
		d[i] = i == sommet_depart ? 0 : -1;

	//tableau pere : tableau donnant pour chaque sommet i le sommet precedent i (pere[i]) dans le plus court chemin de sommet_depart a i
	int *pere = new int [size()];
	for (int i = 0; i < size(); i++)
		pere[i] = 0;
	

	//PARTIE ALGORITHME

	int mind;
	int indiceMin;
	int j = sommet_depart;

	// Lance l'algorithme n-1 fois
	for (int l = 1; l <= size() - 1; l++)
	{
		//On selectione les sommets "i" qui sont pas dans C et qui sont voisin de j
		for (int i = 0; i < size(); i++)
		{
// 		getVertex(i + 1)->display();
// 		getVertex(j + 1)->display();
// cout<<endl;
	//	cout<<getVertex(j + 1)->isNeighbour(getVertex(i + 1))<<endl;
			if (!C[i] && getVertex(j + 1)->isNeighbour(getVertex(i + 1)))
			{
				long poids = getVertex(j + 1)->getArc(getVertex(i + 1))->weight;
				//Si la valeur de base est null on l'update de base
				if (d[i] == -1)
				{
					d[i] = d[j] + poids;
					pere[i] = j;
				}

				//Sinon on verifie qu'on on trouve une plus petite
				else
				{
					if (d[j] + poids < d[i])
					{
						d[i] = d[j] + poids;
						pere[i] = j;
					}
				}

				//On recherche la plus petite valeur de d
				mind = -1;
				indiceMin = -1;
				for (int x = 0; x < size(); x++)
				{
					if (mind == -1)
					{
						mind = d[x];
						indiceMin = x;
					}
					else
					{
						if (mind > d[x])
						{
							mind = d[x];
							indiceMin = x;
						}
					}
			
				}

				//On l'attribue a j et on inclue j dans C
				d[j] = mind;
				C[j] = true;
				j = indiceMin;
			}
		}
	}
	Resultat R;
	R.pere = pere;
	R.d = d;
	return R;
}
