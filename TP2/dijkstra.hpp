#pragma once
#include <map>
#include <limits>
#include "Graph.hpp"

class Dijkstra
{
public:
  Dijkstra(Graph &g, int s, int t);
  std::vector<int> getShortestPath();
  void Solve();

  std::map<Vertex *, Vertex *> MooreDijkstra() const;
  void display_shortest_paths();
  void BellmanFord();

private:
  std::vector<int> run();
  void dealWithNeighbours(Vertex *x, Vertex *&current, std::vector<Vertex *> &open_list, std::vector<Vertex *> &closed_list) const;
  void sort(std::vector<Vertex *> &v) const;
  bool loopOnNeighbours(Vertex *&current, std::vector<Vertex *> &open_list, std::vector<Vertex *> &closed_list) const;
  int isInVector(Vertex *vertex, std::vector<Vertex *> &v) const;
  std::vector<int> getPath(std::vector<Vertex *> &v) const;

  void init();
  Vertex *FindMin(std::vector<Vertex *> &Q);
  void UpdateDistances(Vertex *s1, Vertex *s2);

  void DeleteFromQ(std::vector<Vertex *> &Q, Vertex *elem) const;

private:
  Graph &m_g;
  int m_s;
  int m_t;
  std::map<Vertex *, int> m_d;
  std::map<Vertex *, Vertex *> m_p;
};