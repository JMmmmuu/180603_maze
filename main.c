/*************************************************
 ***************** maze project ******************
 ******************** Yuseok *********************
 ******************** 180000 *********************
 *************************************************/
#include "maze_project.h"

int main(){
    clear();
    initscr();
    keypad(stdscr, TRUE);
    
    makeMaze();
    moveCursor(maze);
    getch();

    endwin();
    return 0;
}
