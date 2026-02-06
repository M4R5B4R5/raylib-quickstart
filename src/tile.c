#include "include/tile.h"

Face face_table[ASCII_LEN];

void face_table_init() {
    for (int i = 0; i < ASCII_LEN; ++i) {
        face_table[i] = UNKNOWN;
    }

    face_table[' '] = EMPTY;
    face_table['#'] = WALL;
    face_table['S'] = START;
    face_table['E'] = END;
    face_table['.'] = PATH;
}

Tile tile_new(Face type) {
    return (Tile) {
        .type = type,
    };
}

int tile_from_char(char c, Tile *out) {
    Face f = face_table[c];
    if (f == UNKNOWN) {
        return -1;
    }

    *out = tile_new(f);
    return 0;
}