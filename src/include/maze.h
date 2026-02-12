#ifndef MAZE_H
#define MAZE_H

#define MAX_BUFF_LEN 256
#define MAX_QUEUE_LEN 256

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tile.h"
#include "point.h"
#include "path.h"
#include "raylib.h"

typedef struct {
    Tile **tiles;
    size_t width;
    size_t height;

    Path *solution;
    size_t step;

    Point start;
    Point end;
} Maze;

typedef enum {
    DFS,
    BFS,
} MazeStrategy;

Maze *maze_new(size_t width, size_t height);
Maze *maze_generate(size_t width, size_t height);
Maze *maze_from_file(const char *path);

bool maze_valid_point(Maze *m, Point p);

void maze_dfs(Maze *m, Point p, bool visited[m->height][m->width], Point *pred[m->height][m->width]);
void maze_bfs(Maze *m, Point start, bool visited[m->height][m->width], Point *pred[m->height][m->width]);

void maze_solve(Maze *m, MazeStrategy strategy);

void maze_step(Maze *m);

void maze_print(Maze *m);
void maze_free(Maze *m);

#endif