#include "raylib.h"
#include "include/maze.h"
#include "include/tile.h"

void render() {
	// Maze *m = maze_from_file("src/mazes/small_maze.txt");
	// Maze *m = maze_from_file("src/mazes/large_maze.txt");
	Maze *m = maze_from_file("src/mazes/medium_maze.txt");
	maze_solve_dfs(m);

	int width = 1600;
	int height = 1600;

	width = (width / m->width) * m->width;
	height = (height / m->height) * m->height;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(240);
    InitWindow(width, height, "Maze Solver");

	float step_timer = 0.0f;
	float step_delay = 0.005f;

    while (!WindowShouldClose())
    {
		float dt = GetFrameTime();
		step_timer += dt;

		if (step_timer >= step_delay) {
			step_timer -= step_delay;
			maze_step(m);
		}

		if (IsWindowResized()) {
			int w = GetScreenWidth();
			int h = GetScreenHeight();

			width = w;
			height = h;
		}

        BeginDrawing();

		ClearBackground(WHITE);

		for (int y = 0; y < m->height; ++y) {
			for (int x = 0; x < m->width; ++x) {
				Tile t = m->tiles[y][x];
				Color c = WHITE;

				switch (t.type) {
					case WALL:
						c = BLACK;
						break;
					case EMPTY:
						c = WHITE;
							break;
					case START:
					case PATH:
						c = BLUE;
						break;
					case PATH_COMPLETE:
						c = GREEN;
						break;
					case END:
						c = RED;
						break;
				}

				int w = width / m->width;
				int h = height / m->height;

				DrawRectangle(x * w, y * h, w, h, c);
			}
		}

		EndDrawing();
    }

    CloseWindow();

	maze_free(m);
}

int main(void)
{
	face_table_init();

	// Maze *m = maze_from_file("src/mazes/maze.txt");
	// maze_print(m);

	render();

    return 0;
}