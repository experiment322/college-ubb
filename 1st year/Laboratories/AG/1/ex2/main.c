#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "in.txt"
#define VMAX 32
#define INFINITY 99999

void read_adj_graph(int * v, int g[][VMAX])
{
    int i, j, w;
    FILE * in = fopen(INPUT_FILE, "r");
    if (in == NULL) {
        perror(INPUT_FILE);
        exit(EXIT_FAILURE);
    }
    fscanf(in, "%i", v);
    if (*v > VMAX)
    {
        *v = 0;
        fclose(in);
        return;
    }
    memset(g, 0, sizeof (**g) * VMAX * VMAX);
    while (!feof(in))
    {
        fscanf(in, "%i %i %i", &i, &j, &w);
        g[i - 1][j - 1] = g[j - 1][i - 1] = w;
    }
    fclose(in);
}

void compute_graph_degrees(int v, int g[][VMAX], int deg[])
{
    int i, j;
    for (i = 0; i < v; ++i)
    {
        deg[i] = 0;
        for (j = 0; j < v; ++j)
        {
            if (g[i][j])
            {
                ++deg[i];
            }
        }
    }
}

int is_graph_regular(int v, int deg[])
{
    int i;
    for (i = 0; i < v - 1; ++i)
    {
        if (deg[i] != deg[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

int is_graph_connected(int v, int g[][VMAX])
{
    int i, visited[VMAX], queue[VMAX], qbgn = 0, qend = 1;
    if (v < 1)
    {
        return 0;
    }
    queue[0] = 0;
    for (i = 0; i < v; ++i)
    {
        visited[i] = 0;
    }
    while (qbgn < qend)
    {
        visited[queue[qbgn]] = 1;
        for (i = queue[qbgn] + 1; i < v; ++i)
        {
            if (g[queue[qbgn]][i])
            {
                queue[qend++] = i;
            }
        }
        ++qbgn;
    }
    for (i = 0; i < v; ++i)
    {
        if (!visited[i])
        {
            return 0;
        }
    }
    return 1;
}

void prepare_warshall(int v, int g[][VMAX], int w[][VMAX])
{
    int i, j;
    for (i = 0; i < v; ++i)
    {
        for (j = 0; j < v; ++j)
        {
            w[i][j] = g[i][j] || i == j ? g[i][j] : INFINITY;
        }
    }
}

void warshall(int v, int g[][VMAX], int w[][VMAX])
{
    int i, j, k;
    prepare_warshall(v, g, w);
    for (k = 0; k < v; ++k)
    {
        for (i = 0; i < v; ++i)
        {
            for (j = 0; j < v; ++j)
            {
                if (w[i][j] > w[i][k] + w[k][j])
                {
                    w[i][j] = w[i][k] + w[k][j];
                }
            }
        }
    }
}

void print_adj_graph(int v, int g[][VMAX])
{
    int i, j;
    printf("   ");
    for (i = 0; i < v; ++i)
    {
        printf("%2i ", i + 1);
    }
    printf("\n");
    for (i = 0; i < v; ++i)
    {
        printf("%2i ", i + 1);
        for (j = 0; j < v; ++j)
        {
            printf("%2i ", g[i][j] == INFINITY ? -1 : g[i][j]);
        }
        printf("\n");
    }
}

void print_graph_degrees(int v, int deg[])
{
    int i, k = 0;
    for (i = 0; i < v; ++i)
    {
        k += deg[i] ? 0 : 1;
        printf("V = %i, # = %i => %s\n", i + 1, deg[i], deg[i] ? "not isolated" : "isolated");
    }
    printf("Graph has %i isolated vertices\n", k);
}

void print_graph_regular_check(int v, int deg[])
{
    printf("Graph is %s\n", is_graph_regular(v, deg) ? "regular" : "not regular");
}

void print_graph_connected_check(int v, int g[][VMAX])
{
    printf("Graph is %s\n", is_graph_connected(v, g) ? "connected" : "not connected");
}

int main()
{
    int v, adj_graph[VMAX][VMAX], weights[VMAX][VMAX], deg[VMAX];

    read_adj_graph(&v, adj_graph);
    print_adj_graph(v, adj_graph);
    printf("\n");

    compute_graph_degrees(v, adj_graph, deg);
    print_graph_degrees(v, deg);
    printf("\n");

    print_graph_regular_check(v, deg);
    printf("\n");

    print_graph_connected_check(v, adj_graph);
    printf("\n");

    warshall(v, adj_graph, weights);
    print_adj_graph(v, weights);
    printf("\n");
    return 0;
}
