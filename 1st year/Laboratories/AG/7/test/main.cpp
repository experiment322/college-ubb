// Acoperire de cost minim(kruskal)
// Arborele de cost minim al unui graf este un subgraf care contine toate
// nodurile din graful initial si un numar minim de muchii (de lungime
// minima) din acesta.
// ----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

typedef vector<vector<size_t>> Graph;
typedef pair<pair<size_t, size_t>, size_t> Edge;

Graph read_graph()
{
    size_t n, m;
    ifstream input("graph.txt");
    input >> n >> m;
    Graph graph = Graph(n, vector<size_t>(n, 0));
    for (size_t i = 0; i < m; ++i)
    {
        size_t x, y, w;
        input >> x >> y >> w;
        graph[x - 1][y - 1] = w;
    }
    input.close();
    return graph;
}

void print_graph(const Graph& graph)
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph.size(); ++j)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

void insert_edge(vector<Edge>& edges, const Edge& edge)
{
    int index = 0;
    for (auto e : edges)
    {
        if (e.second > edge.second)
        {
            edges.insert(edges.begin() + index, edge);
            return;
        }
        ++index;
    }
    edges.push_back(edge);
}

void connect(Graph& connected, size_t x, size_t y)
{
    for (size_t i = 0; i < connected.size(); ++i)
    {
        if (connected[x][i])
        {
            connected[y][i] = connected[i][y] = 1;
        }
        if (connected[y][i])
        {
            connected[x][i] = connected[i][x] = 1;
        }
    }
    connected[x][y] = connected[y][x] = 1;
}

Graph kruskal(const Graph& graph)
{
    vector<Edge> edges;
    Graph min_graph(graph.size(), vector<size_t>(graph.size(), 0));
    Graph connected(graph.size(), vector<size_t>(graph.size(), 0));
    for (size_t i = 0; i < graph.size(); ++i) // N log(N)
    {
        for (size_t j = 0; j < graph.size(); ++j)
        {
            if (graph[i][j] != 0)
            {
                insert_edge(edges, Edge({i, j}, graph[i][j]));
            }
        }
    }
    for (size_t i = 0; i < edges.size(); ++i) // E
    {
        auto x = edges[i].first.first;
        auto y = edges[i].first.second;
        auto w = edges[i].second;
        if (!connected[x][y])
        {
            min_graph[x][y] = w;
            connect(connected, x, y);
        }
    }
    return min_graph;
}

int main()
{

    Graph graph = read_graph();
    Graph min_graph = kruskal(graph);
    print_graph(min_graph);
    return 0;
}
