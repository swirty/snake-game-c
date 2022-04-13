#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>

int headX,headY,width,height,gameOver=0,direction=2,size=4,score=0,speed=100000;
int bodyX[30],bodyY[30];

void updateSnake(void);
void setupGame(void);
void inputCheck(void);
void moveSnake(void);
void exitGame(int);

int main(){
  initscr();
  clear();
  width = COLS-1;
  height = LINES-1;
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  noecho();
  setupGame();
  while(!gameOver){
    inputCheck();
    moveSnake();
    updateSnake();
    refresh();
    usleep(speed);
    signal(SIGINT, exitGame);
  }
}

void setupGame()
{
  headX=5;
  headY=2;

  int i,j;
  addch('#');
  hline('-', width-1);
  move(0, width);
  addch('#');
  move(1,0);
  vline('|', height-1);
  move(1, width);
  vline('|', height-1);
  move(height,0);
  addch('#');
  hline('-', width-1);
  move(height, width);
  addch('#');
  refresh();
}

void inputCheck(){
  switch (getch()){
    case 'w':
    case KEY_UP:
      direction=1;
      break;

    case 'd':
    case KEY_RIGHT:
      direction=2;
      break;

    case 's':
    case KEY_DOWN:
      direction=3;
      break;

    case 'a':
    case KEY_LEFT:
      direction=4;
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
   for(int i=1; i<width; i++){
     move(1,i);
     vline(' ', height-1);
   }

   for(int i=0; i<size; i++){
     move(bodyY[i], bodyX[i]);
     printw("%i", i);
   }
   move(headY, headX);
   addch('@');
 }

 void exitGame(int a){
   char *endtext = "Exiting";
   move(height/2, (width - strlen(endtext)) / 2);
   printw("%s", endtext);
   refresh();
   usleep(speed * 4);
   endwin();
   exit(a);
 }
