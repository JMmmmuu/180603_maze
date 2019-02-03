MAZE Game
==========

> ###### Yuseok Jung
> ###### Maze Game using Data Structure Content
> ###### Made in 2018.06.03
-------------------------------------
> game을 compile 후 실행시키면, 미로의 사이즈(높이, 폭)와 perfect maze/ imperfect maze를 입력합니다.  
> 키보드 상하좌우 방향키로 경로를 그리며 미로 게임을 진행합니다.  
> f(F)를 누르면 경로를 찾아 화면에 표시합니다.  
> q(Q)를 누르면 게임을 종료합니다.  

----------------------------------------
----------------------------------------

* maze\_project.c
    - makefile의 용법을 잘 모를 때 처음으로 작성했던 원본 파일
    - 필요한 모든 code가 포함된 하나의 file
    - makefile에는 해당 코드를 link하지 않음.

* maze\_project.h
    - 사용된 header file
    - 각종 header file들과 contstants, functions, 그리고 structures 포함
    - 기존의 단일 파일에서 작성했던 mv[MAX\_DIR\_SIZE]의 선언 부분을 수정했습니다.
        + DFSSearch.c file로 이동했습니다.

* main.c
    - main 함수로, 필요한 세부 내용들은 각 함수로 정리하여 함수 호출만 담당합니다.
    - ncurses library를 활용하여 화면을 초기화하고 원하는 화면을 띄웁니다.
    - 처음에 미로의 높이와 폭을 입력받아 미로의 사이즈를 결정하고, perfect maze와 imperfect maze 중 build할 미로의 종류를 입력받습니다.

* buildMaze.c
    - Eller's Algorithm을 이용해 perfect maze를 build 합니다.
    - 만들어진 perfect maze를 활용해 imperfect maze를 build 했습니다.
        + 이 때 만들어진 maze가 room(square 모양)을 만들지 않도록 고려했습니다.
        + ~~시간복잡도는 infinity. but not such that case~~

* DFSSearch.c
    - DFS Search Algorithm을 이용해 미로의 경로를 탐색합니다.
    - 탐색 방향은 북, 동, 남, 서 방향 순
    - ncurses library의 attron(A\_REVERSE) 속성을 이용해 경로를 표시했습니다.

* cursor.c
    - 지나온 경로는 STACK에 저장했습니다.
    - 지나온 경로를 다시 돌아갈 때, 갈림길에서 다른 경로로 들어갈 때, 옳바른게 속성을 표시하도록 고려했습니다.

* makefile
    - 분할할 파일을 하나의 실행 파일로 compile 합니다.
    - maze\_project.c 파일을 제외한 모든 파일을 compile 합니다.
    - -Wall -W -g -lncurses 옵션을 붙였습니다.
    - make clean으로 생성된 object file들을 모두 삭제합니다.
