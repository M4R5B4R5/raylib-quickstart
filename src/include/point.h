#ifndef POINT_H
#define POINT_H

typedef struct {
    int x;
    int y;
} Point;

#define P(x, y) point_new(x, y)

Point point_new(int x, int y);
Point point_add(Point p1, Point p2);
Point point_sub(Point p1, Point p2);

void point_print(Point p);

#endif