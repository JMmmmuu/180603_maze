
/**************************************************
 * DFS Search to find the path
 **************************************************/
#include "maze_project.h"

void findPath(){ 
    int i, row, col, nextRow, nextCol, dir, found = false;
    int EXIT_ROW = HEIGHT-2, EXIT_COL = WIDTH-2;
    element position;
    stck = (element*)malloc(HEIGHT*WIDTH * sizeof(element));
    mark = (int**)malloc(HEIGHT*sizeof(int*));
    for(i=0;i<HEIGHT;i++) mark[i] = (int*)calloc(WIDTH, sizeof(int));
    mark[1][1] = 1; top = 0;
    stck[0].row = 1; stck[0].col = 1; stck[0].dir = 1;
    offsets mv[MAX_DIR_SIZE] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};    // clockwise from N

    while (top>-1 && !found) {
        position = pop();
        row = position.row; col = position.col; dir = position.dir;

        while (dir < 4 && !found) {
            // move in direction dir
            nextRow = row + mv[dir].vert;
            nextCol = col + mv[dir].horiz;

            if (nextRow == EXIT_ROW && nextCol == EXIT_COL) found = true;
            else if (maze[nextRow][nextCol] == 0 && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row; position.col = col; position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            }
            else ++dir;
        }
    }
    //mvprintw(START_ROW+HEIGHT+1, START_COL, "%d %d", nextRow, nextCol);
    if( found ) {
        nptr ptmp=popCursor();
        for(;pHeader;ptmp=popCursor()) {
            mvprintw(START_ROW+ptmp->row, START_COL+ptmp->col, " ");
        }
        //printMaze(maze, HEIGHT, WIDTH);
        attron(A_REVERSE);
        for(i=0;i<=top;i++) {
            mvprintw(START_ROW+stck[i].row, START_COL+stck[i].col, " ");
            mvprintw(START_ROW, START_COL+1, " ");
            mvprintw(START_ROW+row, START_COL+col, " ");
            mvprintw(START_ROW+HEIGHT-2, START_COL+WIDTH-2, " ");
            mvprintw(START_ROW+HEIGHT-1, START_COL+WIDTH-2, " ");
            move(START_ROW+HEIGHT-1, START_COL+WIDTH-2);
        }
        attroff(A_REVERSE);
    }
}

void push(element item){
    if (top >= HEIGHT*WIDTH-1) fprintf(stderr, "Err message: Stack is full.\n");
    stck[++top] = item;
}

element pop(){ 
    if (top == -1)
        exit(-1);
    return stck[top--];
}
