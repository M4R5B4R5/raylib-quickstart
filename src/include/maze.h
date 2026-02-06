#ifndef MAZE_H
#define MAZE_H

#define MAX_BUFF_LEN 256

#include <stdio.h>
#include <string.h>

#include "tile.h"
#include "point.h"

typedef struct {
    size_t width;
    size_t height;
    Tile **tiles;
} Maze;

Maze *maze_new(size_t width, size_t height);
Maze *maze_from_file(const char *path);

void maze_print(Maze *m);

#endif