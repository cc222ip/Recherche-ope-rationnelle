#pragma once
#include <vector>
#include <iostream>
#include <set>

struct Arc;

class Vertex
{
public:
  Vertex(int value);
  void addOutArc(Vertex *dest, long weight);
  void changeValue(int value);
  void display() const;

  int getValue() const;
  Arc *getArc(Vertex *vertex) const;
  std::vector<Vertex *> getNeighbours() const;
  long getWeight() const;
  void setParent(Vertex* vertex);
  void setWeight(long weight);
  Vertex* getParent() const;
  // bool isNeighbour(Vertex* v) const;
  std::set<Arc*> getArcs() const;


private:
  void addInArc(Arc *arc);

private:
  int m_value;
  long m_weight;
  Vertex* m_parent;

  std::vector<Arc *> m_in;
  std::vector<Arc *> m_out;
};

struct Arc
{
  long weight;
  Vertex *src;
  Vertex *dest;
};



bool operator==(const Vertex &a, const Vertex &b);

class Graph
{
public:
  void addVertex(Vertex *vertex);
  void display() const;

  Vertex *getVertex(int value) const;
  int size() const;

  std::vector<Vertex *> GetVertice() const;

private:
  std::vector<Vertex *> m_vertice;
};
