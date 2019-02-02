/**************************************************
 * Move Cursor
 * reverse the color on which passed
 * save the visited path in the stack for flexible manipulation
 **************************************************/
#include "maze_project.h"

int moveCursor(int** m){
    int row=0, col=1, flag;
    int prow, pcol;
    pHeader = NULL;
    pushCursor(0, 1);
    pushCursor(1, 1);
    noecho();
    while (1) {
        flag=0;
        prow=row, pcol=col;
        switch( wgetch(stdscr) ){
            case KEY_UP:
                if (row==0) break;
                else if (m[row-1][col]==1) break;
                else row--; flag=1; break;
            case KEY_DOWN:
                if (m[row+1][col]==1) break;
                else row++; flag=1; break;
            case KEY_LEFT:
                if (m[row][col-1]==1) break;
                else col--; flag=1; break;
            case KEY_RIGHT:
                if (m[row][col+1]==1) break;
                else col++; flag=1; break;
            case 'q':case 'Q':
                mvprintw(START_ROW+HEIGHT/2, START_COL+WIDTH/2, "Quit");
                return 0;
            case 'f': case 'F':
                findPath(); return 0;
        }
        if( flag ){
                if ( (pHeader->link->row==row && pHeader->link->col==col) ){
                    mvprintw(START_ROW+prow, START_COL+pcol, " ");      // back tracking
                    free(popCursor());
                }
                else {
                    pushCursor(row, col);
                    attron(A_REVERSE);
                    mvprintw(START_ROW+prow, START_COL+pcol, " ");
                    attroff(A_REVERSE);
                }
        }
        move(START_ROW+row, START_COL+col);
        if( row == HEIGHT-1 && col == WIDTH-2 ) {
            attron(A_REVERSE);
            mvprintw(START_ROW+row, START_COL+col, " ");
            attroff(A_REVERSE);
            mvprintw(START_ROW+HEIGHT-1, START_COL+WIDTH+1, "maze cleared!");
            return 1;
        }
    }
}

void pushCursor(int row, int col){
    nptr pNew;
    pNew = (nptr)malloc(sizeof(CursorNode));
    pNew->row = row; pNew->col = col; pNew->link = NULL;

    if ( !pHeader )
        pHeader = pNew;
    else {
        pNew->link = pHeader;
        pHeader = pNew;
    }
}
nptr popCursor(){
    nptr pret;

    if ( !pHeader->link ) {
        pret = pHeader;
        pHeader = NULL;
    }
    else {
        pret = pHeader;
        pHeader = pHeader->link;
    }
    return pret;
}
