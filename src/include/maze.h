#ifndef MAZE_H
#define MAZE_H

#define MAX_BUFF_LEN 256

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

Maze *maze_new(size_t width, size_t height);
Maze *maze_generate(size_t width, size_t height);
Maze *maze_from_file(const char *path);

bool maze_valid_point(Maze *m, Point p);

void maze_solve_dfs(Maze *m);
void maze_step(Maze *m);

void maze_print(Maze *m);
void maze_free(Maze *m);

#endif