#include <stdio.h>
#include <stdlib.h>

#include "include/maze.h"

Maze *maze_new(size_t width, size_t height) {
    Maze *m = malloc(sizeof(Maze));
    m->tiles = malloc(sizeof(Tile*) * height);
    m->width = width;
    m->height = height;
    for (int y = 0; y < height; ++y) {
        m->tiles[y] = malloc(sizeof(Tile) * width);
        for (int x = 0; x < width; ++x) {
            m->tiles[y][x] = tile_new(EMPTY);
        }
    }
    return m;
}

Maze *maze_from_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("Unable to open file");
        exit(1);
    }

    Maze *m = malloc(sizeof(Maze));
    m->tiles = NULL;

    int y = 0;
    int x = 0;

    char buff[MAX_BUFF_LEN];
    while (fgets(buff, MAX_BUFF_LEN, f) != NULL) {
        int width = strlen(buff) - 1;
        buff[width] = 0;
        
        m->tiles = realloc(m->tiles, sizeof(Tile*) * (y + 1));
        m->tiles[y] = malloc(sizeof(Tile) * width);
        
        x = 0;
        for (char *c = buff; *c != 0; ++c) {
            if (tile_from_char(*c, &m->tiles[y][x]) == -1) {
                printf("Error parsing: Unknown byte: '%c'\n", *c);
                exit(1);
            }
            ++x;
        }
        ++y;
    }

    m->width = x;
    m->height = y;
    return m;
}

void maze_dfs(Maze *m, Point p) {
    // TODO
}

void maze_solve_dfs(Maze *m) {
    maze_dfs(m, P(0, 0));
}

void maze_print(Maze *m) {
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            printf("%c", m->tiles[y][x].type);
        }
        printf("\n");
    }
    printf("\n");
}