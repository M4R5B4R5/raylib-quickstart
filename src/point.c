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

void point_print(Point p) {
    printf("(%d, %d)", p.x, p.y);
}