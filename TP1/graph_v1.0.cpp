#include "graph_v1.0.h"

int main() {
	Graph A;

	A.insert_edge(0,1,5,0);
	A.insert_edge(1,2,3,0);
	A.insert_edge(2,3,5,0);
	A.insert_edge(0,4,1,0);
	A.insert_edge(4,5,3,0);
	A.insert_edge(1,5,2,0);
	A.insert_edge(5,3,2,0);

	cout << "Graph has " << A.num_vertices() << " vertices and " << A.num_edges() << " edges.\n";

A.maxflow(0,3);
A.display();

	return(0);
}
