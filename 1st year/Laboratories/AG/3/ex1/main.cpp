#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <boost/heap/fibonacci_heap.hpp>

#define INPUT_FILE "in.txt"
#define VMAX 64

void read_graph(int * v, int g[][VMAX]) {
    int i, j, k;
    FILE * in = fopen(INPUT_FILE, "r");
    if (in == nullptr) {
        perror(INPUT_FILE);
        exit(EXIT_FAILURE);
    }
    fscanf(in, "%i", v);
    if (*v > VMAX) {
        *v = 0;
        fclose(in);
        return;
    }
    memset(g, 0, sizeof (**g) * VMAX * VMAX);
    while (!feof(in)) {
        fscanf(in, "%i %i %i", &i, &j, &k);
        g[i - 1][j - 1] = k;
    }
    fclose(in);
}

void print_graph(int v, int g[][VMAX]) {
    int i, j;
    printf("   ");
    for (i = 0; i < v; ++i) {
        printf("%2i ", i + 1);
    }
    printf("\n");
    for (i = 0; i < v; ++i) {
        printf("%2i ", i + 1);
        for (j = 0; j < v; ++j) {
            printf("%2i ", g[i][j]);
        }
        printf("\n");
    }
}

void print_distances(int v, int dist[]) {
    int i;
    for (i = 0; i < v; ++i) {
        printf("%2i ", i + 1);
    }
    printf("\n");
    for (i = 0; i < v; ++i) {
        printf("%2i ", dist[i]);
    }
    printf("\n");
}

int min_distance(int v, int dist[], bool spntree[]) {
    int min_index = 0, min = INT_MAX;
    for (int i = 0; i < v; i++) {
        if (spntree[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int src, int v, int graph[][VMAX], int dist[]) {
    bool spntree[VMAX];
    for (int i = 0; i < v; ++i) {
        dist[i] = INT_MAX;
        spntree[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < v - 1; ++count) {
        int u = min_distance(v, dist, spntree);
        spntree[u] = true;
        for (int t = 0; t < v; ++t) {
            if (!spntree[t] && graph[u][t] && dist[u] != INT_MAX && dist[u] + graph[u][t] < dist[t]) {
                dist[t] = dist[u] + graph[u][t];
            }
        }
    }
}

//struct ComparePair {
//    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) const {
//        return p1.first > p2.first;
//    }
//};

//void dijkstra_fibonacci(int src, int v, int graph[][VMAX], int dist[]) {
//    boost::heap::fibonacci_heap<std::pair<int, int>, boost::heap::compare<ComparePair>> fib_dist;
//    for (int i = 0; i < v; ++i) dist[i] = INT_MAX;
//    dist[src] = 0;
//    for (int i = 0; i < v; ++i) fib_dist.push({dist[i], i});
//    while (!fib_dist.empty()) {
//        int u = fib_dist.top().second;
//        for (auto xt : fib_dist) {
//            int t = xt.second;
//            if (graph[u][t] && dist[u] != INT_MAX && dist[u] + graph[u][t] < dist[t]) {
//                xt.first = dist[t] = dist[u] + graph[u][t];
//            }
//        }
//        for (auto bgn = fib_dist.ordered_begin(), end = fib_dist.ordered_end(); bgn != end; ++bgn) {
//            auto x = *bgn;
//            printf("%i %i\n", x.second);
//        }
//        printf("\n");
//        fib_dist.pop();
//    }
//}

bool bellman_ford(int src, int v, int graph[][VMAX], int dist[]) {
    for (int i = 0; i < v; ++i) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    for (int i = 0; i < v - 1; ++i) {
        for (int s = 0; s < v; ++s) {
            for (int t = 0; t < v; ++t) {
                if (dist[s] != INT_MAX && graph[s][t] && dist[s] + graph[s][t] < dist[t]) {
                    dist[t] = dist[s] + graph[s][t];
                }
            }
        }
    }
    for (int s = 0; s < v; ++s) {
        for (int t = 0; t < v; ++t) {
            if (dist[s] != INT_MAX && graph[s][t] && dist[s] + graph[s][t] < dist[t]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    int v, dist[VMAX], graph[VMAX][VMAX];
    read_graph(&v, graph);
    print_graph(v, graph);
//    dijkstra(0, v, graph, dist);
    if (!bellman_ford(0, v, graph, dist)) {
        printf("Negative cycle detected\n");
    }
//    dijkstra_fibonacci(0, v, graph, dist);
    printf("\n");
    print_distances(v, dist);
    return 0;
}
