/**************************************************
 * used Eller's Algorithm to make a perfect maze
 * with my perfect maze, I broke some walls/ floor to make it imperfect
 * broke them randomly, without making rooms (4 spaces in square form)
 **************************************************/
#include "maze_project.h"

void makeMaze()
{
    int isPerfect;
    printw("Enter size of the maze (HEIGHT, WIDTH): ");
    scanw("%d %d", &HEIGHT, &WIDTH);
    printw("press 1 to make perfect maze, 2 to make imperfect maze: ");
    scanw("%d", &isPerfect);
    WIDTH=WIDTH*2+1;
    HEIGHT=HEIGHT*2+1;
    int row=0;
    maze = initMaze(maze, HEIGHT, WIDTH);
    srand(time(0));
    count = 0;
    
    for(row=1; row<HEIGHT-1; row++) {
        if(row%2==1) BreakWall(maze, row, isPerfect);
        else BreakFloor(maze,row);
    }

    printMaze(maze, HEIGHT, WIDTH);
    /*for(i=0;i<WIDTH;i++)
        for(j=0;j<HEIGHT;j++){
            move(START_ROW+j,START_COL+WIDTH+3+i);
            printw("%d",maze[j][i]);
        }*/
}

int** initMaze(int** m, int HEIGHT, int WIDTH){
    int i, j;
    m = (int**)malloc(HEIGHT * sizeof(int*));
    for(i=0;i<HEIGHT;i++)
        m[i] = (int*)malloc(WIDTH * sizeof(int));

    for(i=0;i<WIDTH;i++){       // margin
        m[0][i] = 1; //( i%2 == 0 ) ? '+' : '-';
        m[HEIGHT-1][i] = 1; //( i%2 == 0 ) ? '+' : '-';
    }
    for(i=1;i<HEIGHT-1;i++)     // margin
        m[i][0] = m[i][WIDTH-1] = 1; //( i%2 == 0 ) ? '+' : '|';

    for(i=1;i<HEIGHT-1;i++)
        for(j=1;j<WIDTH-1;j++)
            if (i%2 == 0) m[i][j] = 1;
            else m[i][j] = ( j%2 == 0 ) ? 1 : ' ';
    m[0][1] = 0;
    m[HEIGHT-1][WIDTH-2] = 0;


    return m;
}
void printMaze(int** m, int HEIGHT, int WIDTH){
    int i,j;
    char tmp;

    clear();
    move(START_ROW, START_COL);
    for(i=0;i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
            move(START_ROW+i, START_COL+j);
            if (i==0 || i==HEIGHT-1 )                       // margin
                ( j%2 == 0 ) ? printw("+") : printw("-");
            else if (j==0 || j==WIDTH-1)
                ( i%2 == 0 ) ? printw("+") : printw("|");   // margin
            else if (i%2==0) {      // boundary horizontal line
                if (m[i][j]) {        // there exist floor
                    tmp = (j%2==0) ? '+' : '-'; printw("%c", tmp);
                }
                else printw(" ");   // no floor
            }
            else {                  // room horizontal line
                if(j%2==0) {        // wall
                    if(m[i][j]) printw("|");    // there exist wall
                    else printw(" ");           // no wall
                }
                else {
                    m[i][j] = 0;
                    printw(" ");
                }
            }
            refresh();
        }
    }
    mvprintw(START_ROW, START_COL+1, " ");
    mvprintw(START_ROW+HEIGHT-1, START_COL+WIDTH-2, " ");
    move(START_ROW, START_COL+1);
}

void BreakWall(int** m, int row, int isPerfect){
    int i;
    int cnt, pre;

    for(i=1;i<WIDTH-1;i+=2) if (m[row][i] == ' ') m[row][i] = ++count;
    if (count == 0) {       // first line
        for(i=2;i<WIDTH-1;i+=2) {
            if( rand()%2 ) {
                m[row][i] = 0;
                m[row][i+1] = m[row][i-1];
            }
        }
    }
    else if (row == HEIGHT-2) {     // last line
        if ( isPerfect==1 ) {
            //------------------------------------- making perfect maze
            for(i=1;i<WIDTH-3;i+=2)
                if (m[row][i] != m[row][i+2]) {
                    m[row][i+1] = 0;            // break wall
                    if (m[row][i] > m[row][i+2]) {      // take smaller count
                            cnt = m[row][i];
                            pre = m[row][i+2];
                            m[row][i] = pre;
                        }
                    else {  // m[row][i] < m[row][i+2]
                        cnt = m[row][i+2];
                        pre = m[row][i];
                        m[row][i+2] = pre;
                    }
                    makeSame(m, row, cnt, pre);
                }
        }
        else {
            //------------------------------------- making imperfect maze
            int brWall[WIDTH/2];
            int idx = 0;
            for(i=1;i<WIDTH-3;i+=2)
            if (m[row][i] != m[row][i+2]) brWall[idx++] = i+1;      // save index of the wall will be broken

            makeImperfect(m);       // break wall between other groups

            for(i=0;i<idx;i++){
                m[row][brWall[i]] = 0;      // break wall
                if (m[row][brWall[i]-1] > m[row][brWall[i]+1]) {        // take smaller count
                    cnt = m[row][brWall[i]-1];
                    pre = m[row][brWall[i]+1];
                    m[row][brWall[i]-1] = pre;
                }
                else {  // m[row][brWall[i]-1] <= m[row][brWall[i]+1]
                    cnt = m[row][brWall[i]+1];
                    pre = m[row][brWall[i]-1];
                    m[row][brWall[i]-1] = pre;
                }
                makeSame(m, row, cnt, pre);
            }
        }
    }
    else {
        for(i=1;i<WIDTH-3;i+=2)
            if (m[row][i] != m[row][i+2])
                if( rand()%2 ) {
                    m[row][i+1] = 0;            // break wall
                    if (m[row][i] > m[row][i+2]) {      // take smaller count
                        cnt = m[row][i];
                        pre = m[row][i+2];
                        m[row][i] = pre;
                    }
                    else {  //m[row][i] < m[row][i+2]
                        cnt = m[row][i+2];
                        pre = m[row][i];
                        m[row][i+2] = pre;
                    }
                    makeSame(m, row, cnt, pre);
                }
    }
}

void makeSame(int** m, int row, int cnt, int pre){  // change room's number
    int i,j;
    for(i=1;i<=row;i+=2)
        for(j=1;j<WIDTH-1;j+=2)
            if(m[i][j] == cnt) m[i][j] = pre;
}

void BreakFloor(int** m, int row){
    int i, j, flag=0, idx = 0, ran;
    int tcnt;
    int *cnt, *flArr;
    cnt = (int*)calloc(WIDTH/2, sizeof(int));
    flArr = (int*)calloc(WIDTH/2, sizeof(int));
    
    for(i=1;i<WIDTH-1;i+=2) {
        tcnt = m[row-1][i];
        j=0; flag=0;

        while( cnt[j] ) {
            if(tcnt == cnt[j]) {       // room's count already appeared
                flag = 1;
                break;
            }
            j++;
        }
        ran = rand()%2;
        if( ran ) {      // go through!
            m[row][i] = 0;
            m[row+1][i] = tcnt;
        }
        
        if( !flag ) {  // room's count not appeared yet
            cnt[idx] = tcnt;
            if ( ran ) flArr[idx] = 1;
            idx++;
        }
        if( flag && ran ) flArr[j] = 1;
    } 
        
    for(i=0;cnt[i];i++) {       // break at least one floor in the same group
        if( !flArr[i] )
            for(j=WIDTH-2;j>0;j-=2)
                if (m[row-1][j] == cnt[i]) {
                    m[row][j] = 0;
                    m[row+1][j] = cnt[i];
                    break;
                }
    }
}

void makeImperfect(int** m){
    int brNum = (HEIGHT > WIDTH) ? WIDTH / 4 : HEIGHT / 4;      // number of walls to break;
    int row, col;
    int cnt, pre;
    int flag = 0;

    for (; brNum>0; brNum--) {
        row = rand() % (HEIGHT-1);
        if (row == 0) row++;

        if (row%2 == 0) {   // floor line
            for(col=1; col<WIDTH-1; col+=2) {
                if (m[row-1][col] != m[row+1][col]) {
                    if(col>=3) {        // not to make empty space (4 rooms)
                        if ( (!m[row][col-2] && !m[row-1][col-1] && !m[row+1][col-1]) ) break;
                    }
                    if(col<WIDTH-3) {
                        if ( (!m[row][col+2] && !m[row+1][col+1] && !m[row-1][col+1]) ) break;
                    }
                    m[row][col] = 0;            // break floor
                    if (m[row-1][col] > m[row+1][col]) {      // take smaller count
                        cnt = m[row-1][col];
                        pre = m[row+1][col];
                        m[row-1][col] = pre;
                    }
                    else {  //m[row-1][col] < m[row+1][col]
                        cnt = m[row+1][col];
                        pre = m[row-1][col];
                        m[row+1][col] = pre;
                    }
                    makeSame(m, HEIGHT-2, cnt, pre);
                    flag=1; break;
                }
            }
        }
        else {          // room & wall line
            for(col=2; col<WIDTH-2; col+=2){
                if (m[row][col-1] != m[row][col+1]) {
                    if(row>=3) {        // not to make empty space (4 rooms)
                        if( (!m[row-2][col] && !m[row-1][col-1] && !m[row-1][col+1]) ) break;
                    }
                    if(row<=HEIGHT-4) {
                        if( (!m[row+2][col] && !m[row+1][col-1] && !m[row+1][col+1]) ) break;
                    }

                    m[row][col] = 0;            // break wall
                    if (m[row][col-1] > m[row][col+1]) {      // take smaller count
                        cnt = m[row][col-1];
                        pre = m[row][col+1];
                        m[row][col-1] = pre;
                    }
                    else { // m[row][col-1] < m[row][col+1]
                        cnt = m[row][col+1];
                        pre = m[row][col-1];
                        m[row][col+1] = pre;
                    }
                    makeSame(m, HEIGHT-2, cnt, pre);
                    flag=1;
                }
            }
        }
        if(brNum == 1 && !flag) brNum++;        // break at least one wall/floor
    }
}
