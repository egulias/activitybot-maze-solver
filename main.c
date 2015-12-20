#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"
#define PING_SENSOR 7
#define CLOSE_ENOUGH_CM 10

#define SIDE_LEFT_IR 13
#define SIDE_LEFT_SENSOR 11

#define SIDE_RIGHT_IR 0
#define SIDE_RIGHT_SENSOR 1

void turn_left();
void turn_right();
void turn_back();
void go_forward();
int choose_direction_for_unexplored(int left, int right, int front);
int is_something_forward();

int const STOP = 0;
int const FORWARD = 1;
int const TURN_RIGHT = 2;
int const TURN_LEFT = 3;
int const BACKWARDS = 4;
//char const *WALL = "--";
//char const *SIDE_WALL = "|";
//char const *EMPTY = " ";

int is_something_forward()
{
    int cm = 0;
    cm = ping_cm(PING_SENSOR);
    if (cm <= CLOSE_ENOUGH_CM) {
        return 1;
    } else {
        return 0;
    }

}

int choose_direction_for_unexplored(int left, int right, int front)
{
    int paths[] = {0,0,0,0};
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
int obstacleSensor(int ir, int sensorPin)
{
    int result = 0;
    freqout(ir, 1, 38000);
    if (input(sensorPin) != 1) result = 1;
    return result;
}

int main()
{
    int front, front_l, front_r, front_f_l, front_f_r, side_left, side_right;
    int speed = 0, direction;
    //For IR sensors
    low(26);
    low(27);

    drive_speed(speed,speed);
    while(1)
    {
        print("%c", HOME);
        front = is_something_forward();

        side_left = obstacleSensor(SIDE_LEFT_IR, SIDE_LEFT_SENSOR);
        side_right = obstacleSensor(SIDE_RIGHT_IR, SIDE_RIGHT_SENSOR);
        // Add main loop code here.
        print("front=%d", front);
        print("side_left=%d", side_left);
        print("side_right=%d", side_right);
        direction = choose_direction_for_unexplored(side_left, side_right, front);
        print("direction=%d%c",       // Display detector states
        		direction, CLREOL);

        if (direction == TURN_RIGHT) {
            turn_right();
        } else if (direction == TURN_LEFT) {
            turn_left();
        } else if (direction == BACKWARDS) {
            turn_back();
        }

        if (direction != STOP) {
            go_forward();
        } else {
            drive_speed(0,0);
        }
    }
}

void turn_left()
{
    drive_goto(-25, 26);
}

void turn_right()
{
    drive_goto(26, -25);
}

void go_forward()
{
    while(!is_something_forward()) {
        //drive_goto(32,32);
    }
}

void turn_back()
{
    turn_left();
    turn_left();
}
