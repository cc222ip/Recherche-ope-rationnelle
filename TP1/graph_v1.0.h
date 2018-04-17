/*********************************************************/
/* Auteur : Serigne Gueye		 		 */
/* Pour le cours L3 Informatique RO			 */
/* TP Flot dans les réseaux				 */
/* Dernière date de modification :  			 */
/* Avignon, le  26 février 2017  			 */
/*********************************************************/
/* Ce code est une simplification des sources libres
/* de la librairie NGraph++.
/*********************************************************
/* Nous nous restreignons ici à des 1-graphes. C'est à dire des graphes orientés
/* n'ayant pas plus d'un arc entre deux sommets.
/*********************************************************
/* De nouveaux types ont été introduits,
/* des méthodes non utiles par rapport aux objectifs du TP ont été enlevées,
/* d'autres simplifiées, et de nouvelles écrites
/*********************************************************
/* Le code originel (complet) Ngraph++ peut être trouvé sur le lien :
/* http://math.nist.gov/~RPozo/ngraph/ngraph_index.html.
/* La description de Ngraph++ tel qu'inscrite dans les sources
/* d'origines est décrite ci-dessous.
/********************************************************/
/* L'idée est de vous fournir des méthodes de base de manipulation de graphes que
/* vous n'avez ainsi pas à recoder depuis le début.
/* A partir de ce noyau simplifié,  l'objectif pédagogique consiste à  AJOUTER
/* progressivement des méthodologies enseignées en cours ET INEXISTANTES dans Ngraph++ :
/*
/* - algorithme de Ford et Fulkerson,
/* - algorithme de recherche de flots compatibles,
/* - etc.
/*************************************************************************/



/*
*
* NGraph++ : a simple graph library
*
* Mathematical and Computational Sciences Division
* National Institute of Technology,
* Gaithersburg, MD USA
*
*
* This software was developed at the National Institute of Standards and
* Technology (NIST) by employees of the Federal Government in the course
* of their official duties. Pursuant to title 17 Section 105 of the
* United States Code, this software is not subject to copyright protection
* and is in the public domain. NIST assumes no responsibility whatsoever for
* its use by other parties, and makes no guarantees, expressed or implied,
* about its quality, reliability, or any other characteristic.
*
*/

// version 4.2

#include <iostream>
#include <set>
#include <map>
#include <utility>      // for std::pair
#include <iterator>     // for inserter()
#include <vector>       // for exporting edge_list
#include <string>
#include <algorithm>
#include <sstream>      // for I/O << and >> operators
#include <stack>

/****************************************************************/
/* Commentaires d'origine de la librairie Ngraph++		*/
/****************************************************************/

// TEMPLATE DIRECTED GRAPH (with in-out adjacency list)
//
//
// T is the v type
//
//  An adjacency graph format lists for each v, a set of neighbors
//  the it connects to (outlinks) and optionally another set of neighbors
//  which connect to it.  (The second set provides a quick way to find
//  out who is pointing to you.)
//
//     v  {out-neighbors}  {in-neighbors}
//

/**

    @brief A mathematical graph object: a simple, directed, connected graph,
    where nodes are of arbitrary type (colores, cities, names, etc.)
    Operations for adding and removing edges and vertices, together with
    functions for finding neighbors, subgraphs, and other properties are
    included.

   Example:


<pre>
    enum color {blue, green, red, yellow, pink, black};
    Graph<color> A;

    A.insert_edge(blue, red);
    A.insert_edge(yellow, blue);
    A.insert_edge(blue, black);

    Graph<color> B(A), S=A.subgraph(blue);

</pre>


*/
/***************************************************************/

using namespace std;

class Graph {

private:
	typedef struct {
		int * pred;
		int minflow;
	}DfsPathRes;
	public:
	/* arc */
	typedef pair<int,int> edge;
	/* Ensemble d'arcs */
	typedef set<edge> E;
        /* Structure permettant de stocker la capacité et le flot d'un arc */
        typedef struct {
            int cap;    // capacité maximale
            int flow;   // flot sur l'arc
        } info;
	/* Paire d'ensemble destiné à contenir pour un sommet : l'ensemble des arcs entrants et sortants */
	typedef pair<E,E> in_out;
	/* Permet d'associer à chaque sommet l'ensemble de ses sommets successeurs et prédécesseurs */
	typedef map<int, in_out>  inc_list;
        /* Permet d'associer à chaque arc des informations (son flot et sa capacité) */
        typedef map<edge, info> edge_info;

	/* Iterateurs */
	typedef E::iterator E_iterator;
	typedef inc_list::iterator iterator;
    typedef edge_info::iterator edges_info_iterator;

	private:

	inc_list G_;
	edge_info E_;
	unsigned int num_edges_;

	public:

	Graph(){ num_edges_ = 0;}

	~Graph()
	{

		clear();
	}

	void clear()
	{
		G_.clear();
		E_.clear();
		num_edges_ = 0;
	}

	unsigned int num_vertices()
	{
		return G_.size();
	}

	unsigned int num_edges()
	{
		return num_edges_;
	}

	void insert_edge(int a, int b, int cap, int flow)
	{
		iterator pa = find(a);

		if (pa == G_.end())
			insert_vertex(a);
		iterator pb = find(b);
		if (pb == G_.end())
			insert_vertex(b);

		edge e = make_pair(a,b);
		info i;
		i.cap = cap;
		i.flow = flow;
		E_[e] = i;

		out_neighbors(a).insert(e);
		in_neighbors(b).insert(e);

		num_edges_++;
	}

	iterator begin() { return G_.begin(); }

	iterator end() { return G_.end(); }

	iterator find(int a)
	{
		return G_.find(a);
	}

	E &in_neighbors(int a)
	{
		return (G_[a]).first;
	}

	E &out_neighbors(int a)
	{
		return G_[a].second;
	}

	void insert_vertex(int a)
	{
		G_[a];
	}

	void display()
	{
		for (iterator p1=G_.begin(); p1 != G_.end(); p1++){
			cout << p1->first << ": " << endl ;

			cout << "arcs entrants : " << endl ;
			for (E_iterator p2=p1->second.first.begin(); p2 != p1->second.first.end(); p2++){
				cout << "(" << (*p2).first << "," << (*p2).second << ")" << " " ;
				cout << "capacité = " << E_[*p2].cap << "," << "flot =" << E_[*p2].flow << endl;
			}

			cout << endl;

			cout << "arcs sortants : " << endl;
			for (E_iterator p2=p1->second.second.begin(); p2 != p1->second.second.end(); p2++){
				cout << "(" << (*p2).first << "," << (*p2).second << ")" << " ";
				cout << "capacité = " << E_[*p2].cap << "," << "flot =" << E_[*p2].flow << endl;
			}
			cout << endl;
		}
	}

	DfsPathRes* dfs_path(int s, int t)
	{
		stack<int> P;
		int i;
		bool * visite = new bool[num_vertices()];
		int * pred = new int[num_vertices()];
		int minflow=-1;

		for(i = 0; i < num_vertices(); i ++){
			visite[i] = false;
			pred[i] = -1;
		}

		P.push(s);

		while(! P.empty()){
			i = P.top();
			P.pop();

			if(i == t){
				auto res = new DfsPathRes;
				res->pred = pred;
				res->minflow=minflow;
				return res;
			}


			if(visite[i] == false){
				iterator pi = find(i);
				visite[i] = true;
				for (auto p :pi->second.second)
					if( visite[p.second]  == false ){
						if(!(E_[p].flow == E_[p].cap))
						{
							auto tmp =E_[p].cap - E_[p].flow;
							if(minflow ==-1)
								minflow = tmp;
							else {
								if(minflow>tmp)
									minflow = tmp;
							}
							P.push(p.second);
							pred[p.second] = i;

						}
					}
			}
		}
		return nullptr;
		// cout << "visites = " ;
		// for(i = 0; i < num_vertices(); i ++)
		// 	cout << visite[i] << " ";
        //
		// cout << endl <<  "pred = " ;
		// for(i = 0; i < num_vertices(); i ++)
		// 	cout << pred[i] << " ";
        //
		// cout << endl;
	}

	int maxflow(int s, int t) {
		int flotMax;

		auto tmp = dfs_path(s,t);
		for(int i=0;i<num_vertices();i++){
			cout<<i<<":"<<tmp->pred[i]<<"\t";
			cout<<endl;
		}
		cout<<tmp->minflow<<endl;

		DfsPathRes * elem = nullptr;
		int current = s;
		do{

			elem = dfs_path(s,t);
			int next = t;
			while(next!=s){
					E_[pair<int,int>(next,elem->pred[next])].flow += elem->minflow;
					next = elem->pred[next];
			}

			for(int i=0;i<num_vertices();i++){
				cout<<i<<":"<<elem->pred[i]<<"\t";
				cout<<endl;
			}
			cout<<elem->minflow<<endl;
			system("pause");

		}while(elem!=nullptr);


		return flotMax;
	}
};
