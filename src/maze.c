#include <stdio.h>
#include <stdlib.h>

#include "include/maze.h"

typedef struct {
    Point u;
    Point v;
} Edge;

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

Maze *maze_generate(size_t width, size_t height) {
    Maze *m = maze_new(width, height);

    

    maze_print(m);
}

Maze *maze_from_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("Unable to open file");
        exit(1);
    }

    Maze *m = malloc(sizeof(Maze));
    m->tiles = NULL;
    m->solution = NULL;
    m->step = 0;

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

            if (m->tiles[y][x].type == START) {
                m->start = P(x, y);
            } else if (m->tiles[y][x].type == END) {
                m->end = P(x, y);
            }
            ++x;
        }
        ++y;
    }

    m->width = x;
    m->height = y;
    return m;
}

bool maze_valid_point(Maze *m, Point p) {
    return p.x >= 0 && p.x < m->width && p.y >= 0 && p.y < m->height;
}

void maze_dfs(Maze *m, Point p, bool visited[m->width][m->height], Point *pred[m->width][m->height]) {
    visited[p.y][p.x] = true;

    Point neighbours[4] = {
        point_add(p, P(0, -1)),
        point_add(p, P(-1, 0)),
        point_add(p, P(1, 0)),
        point_add(p, P(0, 1))
    };

    int n = sizeof(neighbours) / sizeof(Point);
    for (int i = 0; i < n; ++i) {
        Point u = neighbours[i];
        if (maze_valid_point(m, u) && !visited[u.y][u.x] && m->tiles[u.y][u.x].type != WALL) {
            if (pred[u.y][u.x] == NULL) {
                pred[u.y][u.x] = malloc(sizeof(Point));
            }

            *pred[u.y][u.x] = p;
            maze_dfs(m, u, visited, pred);
        }
    }
}

void maze_solve_dfs(Maze *m) {
    bool visited[m->height][m->width];
    Point *pred[m->height][m->width];

    memset(visited, false, sizeof(visited));
    memset(pred, 0, sizeof(pred));

    maze_dfs(m, m->start, visited, pred);

    Path *path = path_new();
    Point *end = &m->end;
    while (end != NULL) {
        path_insert(path, *end, 0);
        end = pred[end->y][end->x];
    }

    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            free(pred[y][x]);
        }
    }

    m->solution = path;
}

void maze_step(Maze *m) {
    if (m->solution != NULL && m->step < m->solution->size) {
        Point p = path_get(m->solution, m->step);
        m->tiles[p.y][p.x].type = PATH;
        ++m->step;
    }

    if (m->step == m->solution->size) {
        for (int i = 0; i < m->solution->size; ++i) {
            Point p = path_get(m->solution, i);
            m->tiles[p.y][p.x].type = PATH_COMPLETE;
        }
    }
}

void maze_print(Maze *m) {
    printf("\n");
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            printf(" ");
            printf("%c", m->tiles[y][x].type);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void maze_free(Maze *m) {
    for (int y = 0; y < m->height; ++y) {
        free(m->tiles[y]);
    }

    free(m->tiles);
    path_free(m->solution);
    free(m);
}