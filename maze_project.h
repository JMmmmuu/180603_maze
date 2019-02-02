/*************************************************
 ***************** maze project ******************
 ******************** Yuseok *********************
 ******************** 180603 *********************
 *************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#define START_ROW 1
#define START_COL 1
#define MAX_DIR_SIZE 4

typedef struct {
    int row, col, dir;
} element;

typedef struct {
    short int vert, horiz;
} offsets;

typedef struct node* nptr;
typedef struct node {
    int row, col;
    nptr link;
} CursorNode;

int HEIGHT, WIDTH;
int** maze;
int** mark;
int count;
//offsets mv[MAX_DIR_SIZE];// = { { -1,0 },{ 0,1 }, { 1,0 }, { 0,-1 } }; // clockwise from N
element* stck;
int top;
nptr pHeader;

void makeMaze();
int** initMaze(int** m, int HEIGHT, int WIDTH);
void printMaze(int**m, int HEIGHT, int WIDTH);
void BreakWall(int** m, int row, int isPerfect);
void BreakFloor(int** m, int col);
void makeSame(int** m, int row, int cnt, int pre);
void makeImperfect(int** m);

int moveCursor(int** m);
void pushCursor(int row, int col);
nptr popCursor();

void findPath();
void push(element item);
element pop();
