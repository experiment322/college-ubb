#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

typedef vector<vector<size_t>> Graf;

Graf read_graph()
{
    ifstream in("graf.txt");
    size_t n, m; in >> n >> m;
    Graf graph(n, vector<size_t>(n, 0));
    for (size_t i = 0; i < m; ++i)
    {
        size_t x, y, w;
        in >> x >> y >> w;
        graph[x - 1][y - 1] = w;
    }
    in.close();
    return graph;
}

void print(vector<size_t>& parents, size_t src, size_t dst)
{
    if (dst != src)
        print(parents, src, parents[dst]);
    cout << dst << " ";
}

void find_shortest_paths(Graf& graph, size_t src, size_t dst)
{
    queue<size_t> q;
    vector<size_t> dist(graph.size(), SIZE_MAX);
    vector<size_t> parents(graph.size(), SIZE_MAX);
    dist[src] = 0;
    parents[src] = src;
    q.push(src);
    while (!q.empty())
    {
        size_t j = q.front();
        for (size_t i = 0; i < graph.size(); ++i)
        {
            if (graph[j][i])
            {
                if (dist[i] == SIZE_MAX || dist[i] >= dist[j] + graph[j][i])
                {
                    dist[i] = dist[j] + graph[j][i];
                    parents[i] = j;
                    q.push(i);
                    if (i == dst)
                    {
                        print(parents, src, dst);
                        cout << endl;
                    }
                }
            }
        }
        q.pop();
    }
}

int main()
{
    size_t src, dst;
    Graf graph = read_graph();
    cout << "Sursa: "; cin >> src;
    cout << "Destinatie: "; cin >> dst;
    find_shortest_paths(graph, src - 1, dst - 1);
    return 0;
}
