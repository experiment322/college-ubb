#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "in.txt"
#define VMAX 32
#define EMAX (VMAX * (VMAX - 1)) / 2

void read_adj_graph(int * v, int g[][VMAX])
{
    int i, j;
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
    for (i = 0; i < *v; ++i)
    {
        for (j = 0; j < *v; ++j)
        {
            g[i][j] = 0;
        }
    }
    while (!feof(in))
    {
        fscanf(in, "%i %i", &i, &j);
        g[i - 1][j - 1] = g[j - 1][i - 1] = 1;
    }
    fclose(in);
}

int convert_adj_inc(int v, int src[][VMAX], int dst[][EMAX])
{
    int i, j, e = 0;
    for (i = 0; i < v; ++i)
    {
        for (j = i + 1; j < v; ++j)
        {
            if (src[i][j])
            {
                dst[i][e] = 1;
                dst[j][e] = 1;
                ++e;
            }
        }
    }
    return e;
}

void convert_inc_adj(int v, int e, int src[][EMAX], int dst[][VMAX])
{
    int i, j, k = -1, l = -1;
    for (j = 0; j < e; ++j)
    {
        for (i = 0; i < v; ++i)
        {
            if (src[i][j] && k == -1)
            {
                k = i;
            }
            if (src[i][j] && k > -1)
            {
                l = i;
            }
        }
        dst[k][l] = 1;
        dst[l][k] = 1;
    }
}

void print_adj_graph(int v, int g[][VMAX])
{
    int i, j;
    for (i = 0; i < v; ++i)
    {
        for (j = 0; j < v; ++j)
        {
            printf("%i ", g[i][j]);
        }
        printf("\n");
    }
}

void print_inc_graph(int v, int e, int g[][EMAX])
{
    int i, j;
    for (i = 0; i < v; ++i)
    {
        for (j = 0; j < e; ++j)
        {
            printf("%i ", g[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int v, e, graph_adj[VMAX][VMAX], graph_ind[VMAX][EMAX];

    read_adj_graph(&v, graph_adj);

    printf("V = %i\n", v);
    print_adj_graph(v, graph_adj);
    printf("\n");

    e = convert_adj_inc(v, graph_adj, graph_ind);
    printf("V = %i, E = %i\n", v, e);
    print_inc_graph(v, e, graph_ind);
    printf("\n");

    return 0;
}
