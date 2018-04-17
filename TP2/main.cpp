#include "Graph.hpp"
#include "dijkstra.hpp"
#include <iostream>

using namespace std;

int main()
{

    Graph *g = new Graph;
    for (int i = 1; i < 11; i++)
        g->addVertex(new Vertex(i));
    g->getVertex(1)->addOutArc(g->getVertex(2), 85);
    g->getVertex(1)->addOutArc(g->getVertex(5), 173);
    g->getVertex(1)->addOutArc(g->getVertex(3), 217);

    g->getVertex(2)->addOutArc(g->getVertex(6), 80);

    g->getVertex(6)->addOutArc(g->getVertex(9), 250);

    g->getVertex(9)->addOutArc(g->getVertex(10), 84);

    g->getVertex(5)->addOutArc(g->getVertex(10), 502);

    g->getVertex(3)->addOutArc(g->getVertex(7), 186);
    g->getVertex(3)->addOutArc(g->getVertex(8), 103);

    g->getVertex(8)->addOutArc(g->getVertex(4), 183);
    g->getVertex(8)->addOutArc(g->getVertex(10), 167);


    Dijkstra *d = new Dijkstra(*g, 1, 10);
    // auto pere = d->getShortestPath();
    // for(auto x:pere)
    //     cout<<x<<endl;
    // d->Solve();
    d->BellmanFord();
    d->display_shortest_paths();
    return 0;
}