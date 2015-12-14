//
// Created by eduardo on 10/12/15.
//

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

int const MAZE_SIZE = 100000;
int const TURN_RIGHT = 1;
int const TURN_LEFT = 2;
int const FORWARD = 3;
int const BACKWARDS = 4;
char const *WALL = "--";
char const *SIDE_WALL = "|";
char const *EMPTY = " ";
bool const EXPLORED = true;
bool const NOT_EXPLORED = false;

struct SquareCell {
    char *front;
    char *right;
    char *left;
    char *back;
    bool explored;
};

struct Maze {
    struct SquareCell *walked;
    size_t size;
    size_t used;
};

void add_cell_to_maze(struct Maze *maze, struct SquareCell cell);

void init_maze(struct Maze *maze)
{
    maze->walked = (struct SquareCell *)malloc(MAZE_SIZE * sizeof(struct SquareCell));
    maze->size = MAZE_SIZE;
    maze->used = 0;
}

void destroy_maze(struct Maze *maze)
{
    free(maze->walked);
}

int choose_direction(struct Maze *maze, int left, int right, int front)
{
    int paths = 0;
    struct SquareCell cell;
    cell.explored = EXPLORED;
    if (left == 1) {
        strcpy(cell.left, SIDE_WALL);
    } else {
        strcpy(cell.left, EMPTY);
        paths++;
    }
    if (right == 1) {
        strcpy(cell.right, SIDE_WALL);
    } else {
        strcpy(cell.right, EMPTY);
        paths++;
    }

    if (front == 1) {
        strcpy(cell.front, SIDE_WALL);
    } else {
        strcpy(cell.front, EMPTY);
        paths++;
    }

    add_cell_to_maze(maze, cell);

    if (paths == 0) {
        return  0;
    }

}

void add_cell_to_maze(struct Maze *maze, struct SquareCell cell)
{
    if (maze->used == maze->size) {
        maze->size*2;
        maze->walked = (struct SquareCell *)realloc(maze->walked, maze->size * sizeof(struct SquareCell));
    }
    maze->walked[maze->used++] = cell;
}

