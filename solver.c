
#include <stdlib.h>

int const STOP = 0;
int const FORWARD = 1;
int const TURN_RIGHT = 2;
int const TURN_LEFT = 3;
int const BACKWARDS = 4;
//char const *WALL = "--";
//char const *SIDE_WALL = "|";
//char const *EMPTY = " ";

int choose_direction_for_unexplored(int left, int right, int front)
{
    int *paths = (int *)malloc(4);
    int possible_paths = 0;

    if (front == 0) {
        paths[possible_paths] = FORWARD;
        possible_paths++;
    }

    if (left == 0) {
        paths[possible_paths] = TURN_LEFT;
        possible_paths++;
    }

    if (right == 0) {
        paths[possible_paths] = TURN_RIGHT;
    }

    if (right == 1 && left == 1 && front == 1) {
        return BACKWARDS;
    } else if (right == 0 && left == 0 && front ==0) {
        return STOP;
    }


    return paths[0];
}
