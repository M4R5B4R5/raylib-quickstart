#include "include/path.h"

static void path_resize(Path *p, size_t new_capacity) {
    p->points = (Point*)realloc(p->points, sizeof(Point) * new_capacity);
    p->capacity = new_capacity;
}

static void path_expand(Path *path) {
    if (path->size == path->capacity) {
        path_resize(path, path->capacity * 2);
    }
}

Path *path_new() {
    Path *p = malloc(sizeof(Path));
    p->points = (Point*)malloc(sizeof(Point) * INITIAL_CAP);
    p->size = 0;
    p->capacity = INITIAL_CAP;
    return p;
}

void path_push(Path *path, Point p) {
    path_expand(path);
    path->points[path->size] = p;
    ++path->size;
}

void path_insert(Path *path, Point p, size_t index) {
    path_expand(path);
    for (int i = path->size; i > (int)index; --i) {
        path->points[i] = path->points[i - 1];
    }
    path->points[index] = p;
    ++path->size;
}

Point path_get(Path *path, size_t index) {
    return path->points[index];
}

void path_print(Path *path) {
    printf("[");
    for (size_t i = 0; i < path->size; ++i) {
        printf("(%d, %d)", path->points[i].x, path->points[i].y);
        if (i != path->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void path_free(Path *path) {
    if (path != NULL) {
        free(path->points);
        free(path);
    }
}