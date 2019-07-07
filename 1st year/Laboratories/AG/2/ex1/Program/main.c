#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "in.txt"
#define VMAX 32
#define INFINITY 99999

void read_graph(int * v, int g[][VMAX])
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
    memset(g, 0, sizeof (**g) * VMAX * VMAX);
    while (!feof(in))
    {
        fscanf(in, "%i %i", &i, &j);
        g[i - 1][j - 1] = 1;
    }
    fclose(in);
}

void read_source(int * s)
{
    printf("S = ");
    scanf("%i", s);
    *s -= 1;
}

void print_graph(int v, int g[][VMAX])
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
            printf("%2i ", g[i][j]);
        }
        printf("\n");
    }
}

void moore(int v, int s, int g[][VMAX], int l[], int p[])
{
    int i, x, queue[VMAX], qbgn = 0, qend = 1;
    for (i = 0; i < v; ++i)
    {
        p[i] = -1;
        l[i] = INFINITY;
    }
    l[s] = 0;
    queue[qbgn] = s;
    while (qbgn < qend)
    {
        x = queue[qbgn];
        for (i = x + 1; i < v; ++i)
        {
            if (g[x][i] && l[i] == INFINITY)
            {
                p[i] = x;
                l[i] += 1;
                queue[qend++] = i;
            }
        }
        ++qbgn;
    }
}

void print_path(int s, int p[])
{
    if (p[s] != -1)
    {
        print_path(p[s], p);
    }
    printf("%i ", s + 1);
}

void print_paths(int v, int p[])
{
    int i;
    for (i = 0; i < v; ++i)
    {
        if (p[i] != -1)
        {
            printf("Shortest path to %i: ", i + 1);
            print_path(i, p);
            printf("\n");
        }
    }
}

void warshall_closure(int v, int g[][VMAX], int tcg[][VMAX])
{
    int i, j, k;
    for (i = 0; i < v; ++i) {
        for (j = 0; j < v; ++j) {
            tcg[i][j] = g[i][j];
        }
    }
    for (i = 0; i < v; ++i) {
        for (j = 0; j < v; ++j) {
            for (k = 0; k < v; ++k) {
                if (!tcg[i][j]) {
                    tcg[i][j] = tcg[i][k] && tcg[k][j];
                }
            }
        }
    }
}

int main()
{
    int v, s, graph[VMAX][VMAX], tcgraph[VMAX][VMAX], l[VMAX], p[VMAX];

    read_graph(&v, graph);
    print_graph(v, graph);
    printf("\n");

    warshall_closure(v, graph, tcgraph);
    print_graph(v, tcgraph);
    printf("\n");

    read_source(&s);
    moore(v, s, graph, l, p);
    print_paths(v, p);
    printf("\n");

    return 0;
}
