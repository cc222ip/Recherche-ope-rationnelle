#include "dijkstra.hpp"

using namespace std;
char alphabet2[] = {'.', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

Dijkstra::Dijkstra(Graph &g, int s, int t) : m_s(s), m_t(t), m_g(g)
{
}

void Dijkstra::dealWithNeighbours(Vertex *x, Vertex *&current, vector<Vertex *> &open_list, vector<Vertex *> &closed_list) const
{
    if (isInVector(x, closed_list) == -1) // see if we have to add things there
    {
        if ((current->getArc(x)->weight + current->getWeight()) < x->getWeight())
        {
            x->setWeight(current->getArc(x)->weight + current->getWeight());
            x->setParent(current);
        }

        open_list.push_back(x);
    }
}
bool Dijkstra::loopOnNeighbours(Vertex *&current, vector<Vertex *> &open_list, vector<Vertex *> &closed_list) const
{
    if (open_list.size() == 0)
        return 1;

    auto neighbours = current->getNeighbours();

    closed_list.push_back(current);
    open_list.erase(open_list.begin());

    for (auto x : neighbours)
        dealWithNeighbours(x, current, open_list, closed_list);

    sort(open_list);

    current = open_list[0];

    return 0;
}
vector<int> Dijkstra::getShortestPath()
{
    return this->run();
}

vector<int> Dijkstra::run()
{
    vector<Vertex *> closed_list, open_list;

    Vertex *current = m_g.getVertex(m_s);

    current->setWeight(0);
    open_list.push_back(current);

    do
    {
        if (loopOnNeighbours(current, open_list, closed_list))
            break;
    } while (1);

    return getPath(closed_list);
}

void Dijkstra::sort(vector<Vertex *> &v) const // shitty sort
{
    for (int i = 0; i < v.size(); i++)
        for (int j = i; j < v.size(); j++)
            if (v[i]->getWeight() > v[j]->getWeight())
            {
                auto tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
}

int Dijkstra::isInVector(Vertex *vertex, vector<Vertex *> &v) const
{
    int i = 0;
    for (auto x : v)
    {
        if (x == vertex)
            return i;
        i++;
    }

    return -1;
}

vector<int> Dijkstra::getPath(vector<Vertex *> &v) const
{
    vector<int> res;
    Vertex *current;

    for (auto x : v)
        if (x->getValue() == m_t)
            current = x;
    do
    {
        res.push_back(current->getValue());
        if (current->getParent() != nullptr)
            current = current->getParent();
        else
            break;

    } while (1);

    return res;
}

////////////////////////////////////////////////////////////
// Wikipedia way
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Init
// Init all the distances at +inf except for the beginning (0)
////////////////////////////////////////////////////////////
void Dijkstra::init()
{
    for (int i = 0; i < m_g.size() + 1; i++)
        m_d[m_g.getVertex(i)] = numeric_limits<int>::max();

    m_d[m_g.getVertex(m_s)] = 0;
}

////////////////////////////////////////////////////////////
// FindMin
// Return the vertex with the lowest arc value
////////////////////////////////////////////////////////////
Vertex *Dijkstra::FindMin(vector<Vertex *> &Q)
{
    int min = numeric_limits<int>::max();
    Vertex *vertex = nullptr;

    for (auto x : Q)
        if (m_d[x] < min)
        {
            min = m_d[x];
            vertex = x;
        }
    return vertex;
}

////////////////////////////////////////////////////////////
// UpdateDistances
// Should we update distances? Either yes or not, we r treating it here
////////////////////////////////////////////////////////////
void Dijkstra::UpdateDistances(Vertex *s1, Vertex *s2)
{
    if (s1->getArc(s2) == nullptr)
        return;
    if (m_d[s2] > m_d[s1] + s1->getArc(s2)->weight)
    {
        m_d[s2] = m_d[s1] + s1->getArc(s2)->weight;
        m_p[s2] = s1;
    }
}

////////////////////////////////////////////////////////////
// DeleteFromQ
// Deletes elem from Q
////////////////////////////////////////////////////////////
void Dijkstra::DeleteFromQ(vector<Vertex *> &Q, Vertex *elem) const
{
    for (int i = 0; i < Q.size(); i++)
        if (Q[i] == elem)
        {
            Q.erase(Q.begin() + i);
            return;
        }
}

////////////////////////////////////////////////////////////
// Solve
// Solves Dijsktra
////////////////////////////////////////////////////////////
void Dijkstra::Solve()
{
    init();
    vector<Vertex *> Q = m_g.GetVertice();

    while (Q.size() != 0)
    {

        auto s1 = FindMin(Q);

        DeleteFromQ(Q, s1);
        auto neighbours = s1->getNeighbours();
        for (auto n : neighbours)
            UpdateDistances(s1, n);
    }
}

map<Vertex *, Vertex *> Dijkstra::MooreDijkstra() const
{
    return m_p; // ARNAAUD
}

void Dijkstra::display_shortest_paths()
{

    vector<int> path;
    int s = m_t;
    while (s != m_s)
    {
        path.push_back(s);

        s = m_p[m_g.getVertex(s)]->getValue();
    }

    for (auto x : path)
        cout << x << endl;
    cout << m_s << endl;
}

void Dijkstra::BellmanFord()
{
    init();
    for (int i = 1; i < m_g.size() + 1; i++)
    {
        auto arc = m_g.getVertex(i)->getArcs();
       
        for (auto x : arc)
            if (x != nullptr)
            {

                auto chris = m_d[m_g.getVertex(i)] +x->weight;
                 cout<<chris<<","<<m_d[m_g.getVertex(i)]<<endl;
                if (chris < m_d[m_g.getVertex(i)])
                {
                    m_d[m_g.getVertex(i)] = chris;
                    m_p[m_g.getVertex(i)] = m_g.getVertex(i);
                }
            }
    }
  for (int i = 1; i < m_g.size() + 1; i++)
    {
    auto arc = m_g.getVertex(i)->getArcs();
    for (auto x : arc)
        if (x != nullptr)
        {
            auto chris = m_d[m_g.getVertex(i)] + x->weight;
            if (chris < m_d[m_g.getVertex(i)])
            {
                cout << "Nop, error" << endl;
            }
        }
    }
}