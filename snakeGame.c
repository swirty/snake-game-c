#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>

int headX,headY,xMax, yMax,gameOver=0,direction=2,size=4,score=0,speed=140000;
int bodyX[30],bodyY[30];

#define BOARD_HEIGHT (LINES - 2)
#define BOARD_WIDTH (COLS - 1)

void updateSnake(void);
void setupGame(void);
void inputCheck(void);
void moveSnake(void);
void detectColision(int,int);
void displayMessage(char*);
void exitGame(int);


int main(){
  initscr();
  clear();
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  noecho();
  setupGame();
  while(!gameOver){
    box(stdscr, 0, 0);
    inputCheck();
    moveSnake();
    updateSnake();
    refresh();
    usleep(speed);
    signal(SIGINT, exitGame);
  }
}

WINDOW * boardWin;
void setupGame() {
    headX=5;
    headY=2;
    getmaxyx(stdscr, yMax, xMax); //get dimentions of terminal
    box(stdscr, 0, 0); //box representing the border
    refresh();
}

void inputCheck(){
  switch (getch()){
    case 'w':
    case KEY_UP:
      direction=1;
      speed = 190000;
      break;

    case 'd':
    case KEY_RIGHT:
      direction=2;
      speed = 140000;
      break;

    case 's':
    case KEY_DOWN:
      direction=3;
      speed = 190000;
      break;

    case 'a':
    case KEY_LEFT:
      direction=4;
      speed = 140000;
      break;

    case ERR:
      break;
  }
}

void moveSnake()
{
 int x1,x2,y1,y2,i;

  x1=headX;
  y1=headY;
  for(i=0;i<size;i++)
  {
   x2=bodyX[i];
   y2=bodyY[i];
   bodyX[i]=x1;
   bodyY[i]=y1;
   x1=x2;
   y1=y2;
  }

  
 switch (direction)
 {
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

 void updateSnake(void){
   for(int i=1; i<BOARD_WIDTH; i++){
     move(1,i);
     vline(' ', BOARD_HEIGHT-1);
   }

   for(int i=0; i<size; i++){
     move(bodyY[i], bodyX[i]);
     printw("%i", i);
   }
   move(headY, headX);
   addch('@');
   detectColision(headY, headX);
 }

 void detectColision(int y,int x) {
     if (y >= yMax-1 || x >= xMax-1 || y <= 0 || x <= 0) {
         displayMessage("Game Over");
     }
 }

 void exitGame(){
     displayMessage("Exiting");
 }

 void displayMessage(char* str) {
     move(BOARD_HEIGHT/2, (BOARD_WIDTH - strlen(str)) / 2);
     printw("%s", str);
     refresh();
     usleep(1300000);
     endwin();
     exit(0);
 }