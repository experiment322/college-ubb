#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void read_graph(vector<vector<int>>& graph, size_t& v, size_t& m)
{
    size_t x, y;
    ifstream in("graf.txt");
    in >> v >> m;
    for (size_t i = 0; i < v; ++i)
    {
        graph.push_back(vector<int>{});
        for (size_t j = 0; j < v; ++j)
        {
            graph[i].push_back(0);
        }
    }
    for (size_t i = 0; i < m; ++i)
    {
        in >> x >> y;
        graph[x][y] = 1;
        graph[y][x] = 1;
    }
    in.close();
}

void convert_adj_to_inc(vector<vector<int>>& adj_graph, vector<vector<int>>& inc_graph, size_t& v, size_t& m)
{
    size_t k = 0;
    for (size_t i = 0; i < v; ++i)
    {
        inc_graph.push_back(vector<int>{});
        for (size_t j = 0; j < m; ++j)
        {
            inc_graph[i].push_back(0);
        }
    }
    for (size_t i = 0; i < v; ++i)
    {
        for (size_t j = i + 1; j < v; ++j)
        {
            if (adj_graph[i][j] == 1)
            {
                inc_graph[i][k] = 1;
                inc_graph[j][k] = 1;
                ++k;
            }
        }
    }
}

void write_inc_graph(vector<vector<int>>& inc_graph, size_t& v, size_t& m)
{
    ofstream out("graf_inc.txt");
    for (size_t i = 0; i < v; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            out << inc_graph[i][j] << " ";
        }
        out << endl;
    }
    out.close();
}

int main()
{
    size_t v, m;
    vector<vector<int>> adj_graph, inc_graph;
    read_graph(adj_graph, v, m);
    convert_adj_to_inc(adj_graph, inc_graph, v, m);
    write_inc_graph(inc_graph, v, m);
    return 0;
}
