#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>

int headX,headY,xMax,yMax,gameOver=0,direction=2,size=4,score=0,tickDelay=140000;
int bodyX[30],bodyY[30];

#define BOARD_HEIGHT (LINES - 1)
#define BOARD_WIDTH (COLS - 1)

void updateSnake(void);
void setupGame(void);
void inputCheck(void);
void moveSnake(void);
void detectColision(int,int);
void displayMessage(char*);
void exitGame();

/**
Function: main()
Purpose: initialize the game, do the gameloop, and close the game neatly
Author: Corwin Van Deusen
**/
int main() {
    //boilerplate prep code
    initscr();
    clear();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    noecho();
    
    //game loop
    setupGame();
    while(!gameOver){
        box(stdscr, 0, 0);
        inputCheck();
        moveSnake();
        updateSnake();
        detectColision(headY, headX);
        refresh();
        usleep(tickDelay);
        signal(SIGINT, exitGame);
    }
    
    //end cleanly
    displayMessage("Game Over");
    usleep(10 * tickDelay);
    exitGame();
}

/**
Function: setupGame()
Purpose: places the snake head in the top left corner so when it automatically goes right from the start, it has space to move. 
         Also gets dimensions of terminal and draw the border.
Author: Tom & Moiz
**/
void setupGame() {
    headX=5;
    headY=2;
    getmaxyx(stdscr, yMax, xMax); //get dimentions of terminal
    box(stdscr, 0, 0); //box representing the border
    refresh();
}

/**
Function: inputCheck()
Purpose: checks if a key is being held and parses that into a variable
Author: Corwin & Tom
**/
void inputCheck() {
    switch (getch()){
        case 'w':
        case KEY_UP:
            direction=1;
            //tickDelay = 190000;
            break;
        
        case 'd':
        case KEY_RIGHT:
            direction=2;
            //tickDelay = 140000;
            break;
        
        case 's':
        case KEY_DOWN:
            direction=3;
            //tickDelay = 190000;
            break;
            
        case 'a':
        case KEY_LEFT:
            direction=4;
            //tickDelay = 140000;
            break;
            
        case ERR:
            break;
    }
}

/**
Function: moveSnake()
Purpose: moves the snake by replacing body with the head, giving the visual of every circle behind the head following the head
Author: Tom
**/
void moveSnake() {
    int x1,x2,y1,y2,i;
    x1=headX;
    y1=headY;
    for(i=0;i<size;i++){
        x2=bodyX[i];
        y2=bodyY[i];
        bodyX[i]=x1;
        bodyY[i]=y1;
        x1=x2;
        y1=y2;
    }
    switch (direction){
        case 1:
            headY--;
            break;
        case 2:
            headX++;
            break;
        case 3:
            headY++;
            break;
        case 4:
            headX--;
    }
}

/**
Function: updateSnake()
Purpose: blanks the playfield and redraws the snake
Author: Corwin Van Deusen
**/
void updateSnake(void) {
    //blank the play area
    for(int i=1; i<BOARD_WIDTH; i++){
        move(1,i);
        vline(' ', BOARD_HEIGHT-1);
    }

   //draw the snake segments
   for(int i=0; i<size; i++){
       move(bodyY[i], bodyX[i]);
       printw("%i", i);
    }

   //draw the head
   move(headY, headX);
   addch('@');
}

/**
Function: detectColision()
Purpose: detects collision with the wall and sets the gameOver flag
Author: Moiz
**/
void detectColision(int y,int x) {
    gameOver = (y >= yMax-1 || x >= xMax-1 || y <= 0 || x <= 0);
}

/**
Function: exitGame()
Purpose: exits the game cleanly
Author: Corwin Van Deusen
**/
void exitGame() {
    displayMessage("Exiting");
    usleep(1300000);
    endwin();
    exit(0);
}

/**
Function: displayMessage()
Purpose: blanks the row, then writes whatever message was passed
Author: Moiz
**/
void displayMessage(char* str) {
    move(BOARD_HEIGHT/2, 1);//goto the line
    hline(' ', BOARD_WIDTH-2);//blank the line
    move(BOARD_HEIGHT/2, (BOARD_WIDTH - strlen(str)) / 2);//goto the middle of the line -1/2 the string length
    printw("%s", str);
    refresh();
}
