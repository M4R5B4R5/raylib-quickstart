#ifndef TILE_H
#define TILE_H

#define ASCII_LEN 128

void face_table_init();

typedef enum {
    EMPTY = ' ',
    WALL = '#',
    START = 'S',
    END = 'E',
    PATH = '.',
    PATH_COMPLETE = '+',
    UNKNOWN,
} Face;

typedef struct {
    double width;
    double height;
    Face type;
} Tile;

Tile tile_new(Face type);
int tile_from_char(char c, Tile *out);

#endif