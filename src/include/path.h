#ifndef PATH_H
#define PATH_H

#define INITIAL_CAP 16

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "point.h"

typedef struct {
    Point *points;
    size_t size;
    size_t capacity;
} Path;

Path *path_new();
Point path_get(Path *path, size_t index);

void path_push(Path *path, Point p);
void path_insert(Path *path, Point p, size_t index);
void path_print(Path *path);
void path_free(Path *path);

#endif