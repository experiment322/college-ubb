#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START 'S'
#define FINAL 'F'
#define SPACE ' '
#define BLOCK '1'
#define VISIT '#'

#define HMAX 256
#define WMAX 256
#define QMAX 128

void print_matrix(int m[][WMAX], int h, int w) {
    int i, j;
    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            fputc(m[i][j], stdout);
        }
        fputc('\n', stdout);
    }
}

void read_maze(char * file_name, int maze[][WMAX], int * h, int * w) {
    int j;
    char buffer[WMAX];
    FILE * in = fopen(file_name, "r");
    *h = *w = 0;
    while (fgets(buffer, WMAX, in) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (*w == 0) {
            *w = (int)strlen(buffer);
        } else if (*w != (int)strlen(buffer)) {
            *h = *w = 0;
            break;
        }
        for (j = 0; j < (int)strlen(buffer); ++j) {
            maze[*h][j] = buffer[j];
        }
        *h += 1;
    }
    fclose(in);
}

void recursive_fill(int maze[][WMAX], int result[][WMAX], int x, int y, int * found) {
    if (!*found && result[x][y] != VISIT && maze[x][y] != BLOCK) {
        result[x][y] = VISIT;
        if (maze[x][y] == FINAL) {
            *found = 1;
            return;
        }
        recursive_fill(maze, result, x - 1, y, found);
        recursive_fill(maze, result, x, y - 1, found);
        recursive_fill(maze, result, x, y + 1, found);
        recursive_fill(maze, result, x + 1, y, found);
    }
    if (*found) {// fix
        result[x][y] = SPACE;
    }
}

void solve_maze(int h, int w, int maze[][WMAX], int result[][WMAX]) {
    int x, y, found = 0, sx = -1, sy = -1, fx = -1, fy = -1;
    for (x = 0; x < h; ++x) {
        for (y = 0; y < w; ++y) {
            result[x][y] = SPACE;
            if (maze[x][y] == START) {
                sx = x; sy = y;
            } else if (maze[x][y] == FINAL) {
                fx = x; fy = y;
            }
        }
    }
    if (sx == -1 || sy == -1 || fx == -1 || fy == -1) {
        return;
    }
    recursive_fill(maze, result, sx, sy, &found);
}

int main() {
    int height, width, maze[HMAX][WMAX], result[HMAX][WMAX];
    read_maze("maze.txt", maze, &height, &width);
    print_matrix(maze, height, width);
    solve_maze(height, width, maze, result);
    print_matrix(result, height, width);
    return 0;
}
