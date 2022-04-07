#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include <ncurses.h>

int headX,headY,width=25,height=25,gameOver=0,direction=2,size=5,score=0,speed=100000;
int bodyX[30],bodyY[30];

void updateSnake(void);
void setupGame(void);
void inputCheck(void);
void moveSnake(void);

int main(){
  initscr();
  clear();
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  noecho();
  setupGame();
  while(!gameOver){
    inputCheck();
    moveSnake();
    updateSnake();
    refresh();
    usleep(speed);
  }
  usleep(speed);
  system("clear");
  endwin();
}

/*int kbhit(void) //kbhit is only on Windows, so I looked up the code to implement into Linux based C code
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}*/

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
   int i=0;

   for(i=1; i<width; i++){
     move(1,i);
     vline(' ', height-1);
   }

   for(i=0; i<size; i++){
     move(bodyY[i], bodyX[i]);
     addch('o');
   }
   move(bodyY[i], bodyX[i]);
   addch('@');
 }
