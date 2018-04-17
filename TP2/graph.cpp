#include "Graph.hpp"

using namespace std;

char alphabet[] = {'.', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

bool operator==(const Vertex &a, const Vertex &b)
{
    return a.getValue() == b.getValue();
}

Vertex::Vertex(int value) : m_value(value), m_weight(999999), m_parent(nullptr)
{
}

void Vertex::addInArc(Arc *arc)
{
    m_in.push_back(arc);
}

set<Arc *> Vertex::getArcs() const
{
    set<Arc *> res;
    for (auto x : m_out)
        res.insert(x);

    for (auto x : m_in)
        res.insert(x);

    return res;
}

std::vector<Vertex *> Graph::GetVertice() const
{
    return m_vertice;
}

void Vertex::addOutArc(Vertex *dest, long weight)
{
    Arc *tmp = new Arc;

    tmp->weight = weight;
    tmp->dest = dest;
    tmp->src = this;

    m_out.push_back(tmp);
    dest->addInArc(tmp);
}

void Vertex::changeValue(int value)
{
    m_value = value;
}

int Vertex::getValue() const
{
    return m_value;
}

vector<Vertex *> Vertex::getNeighbours() const
{
    vector<Vertex *> res;

    for (auto x : m_out)
        res.push_back(x->dest);

    for (auto x : m_in)
        res.push_back(x->src);

    return res;
}

long Vertex::getWeight() const
{
    return m_weight;
}

void Graph::display() const
{
    for (auto x : m_vertice)
    {
        x->display();
        cout << endl;
    }
}

Arc *Vertex::getArc(Vertex *vertex) const
{
    for (auto x : m_out)
        if (x->dest == vertex)
            return x;
    return nullptr;
}

// bool Vertex::isNeighbour(Vertex *v) const
// {
//     for (auto x : m_out)
//         if (x == v)
//             return true;

//     for (auto x : m_in)
//         if (x == v)
//             return true;

//     return false;
// }

void Vertex::setParent(Vertex *vertex)
{
    m_parent = vertex;
}
Vertex *Vertex::getParent() const
{
    return m_parent;
}

void Vertex::setWeight(long weight)
{
    m_weight = weight;
}

void Vertex::display() const
{
    cout << "Vertex [" << alphabet[m_value] << "] => " << m_weight << endl;
    cout << "\tOut vertice:" << endl;
    for (auto out : m_out)
        cout << "\t\t- " << alphabet[out->dest->getValue()] << " (" << out->weight << ")" << endl;
    cout << endl
         << "\tIn vertice:" << endl;
    for (auto in : m_in)
        cout << "\t\t- " << alphabet[in->src->getValue()] << " (" << in->weight << ")" << endl;
}

void Graph::addVertex(Vertex *vertex)
{
    m_vertice.push_back(vertex);
}

Vertex *Graph::getVertex(int value) const
{

    for (auto x : m_vertice)
        if (x->getValue() == value)
            return x;
    return nullptr;
}

int Graph::size() const
{
    return m_vertice.size();
}
