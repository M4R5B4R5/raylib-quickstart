#include "include/point.h"

Point point_new(int x, int y) {
    return (Point) {
        .x = x,
        .y = y,
    };
}

Point point_add(Point p1, Point p2) {
    return P(p1.x + p2.x, p1.y + p2.y);
}

Point point_sub(Point p1, Point p2) {
    return P(p1.x - p2.x, p1.y - p2.y);
}

void point_neighbours(Point p, Point neighbours[NEIGHBOURS_LEN]) {
    neighbours[0] = point_add(p, P(0, -1));
    neighbours[1] = point_add(p, P(-1, 0));
    neighbours[2] = point_add(p, P(1, 0));
    neighbours[3] = point_add(p, P(0, 1));
}

void point_print(Point p) {
    printf("(%d, %d)", p.x, p.y);
}