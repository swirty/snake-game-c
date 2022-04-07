#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
int headX,headY,width=25,height=25,gameOver=0,direction=2,size=4,score=0,speed=100000;
int bodyX[30],bodyY[30];

int kbhit(void) //kbhit is only on Windows, so I looked up the code to implement into Linux based C code
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
}
char getch(void) //Also a Windows method, had to look up literal code to implement into this project, gets user inputs in terms of up,down,left,right keys
{
    char c;
    system("stty raw");
    c= getchar();
    system("stty sane");
    return(c);
}

void create()
{
 system("clear");
 int i,j,k,p;
 for(j=0;j<=height;j++)
 {
  for(i=0;i<=width;i++)
  {
    p=1;
    if(i==0||i==width)
      printf("|");
    else if(j==0||j==height)
        printf("-");
    else if(i==headX&&j==headY)
      printf("@");
    else
    {
     for(k=0;k<size;k++)
     {
      if(i==bodyX[k] && j==bodyY[k])
      {
       printf("o");
       p=0;
      }
     }
      if(p)
      printf(" ");
    }
  }
  printf("\n");
 }
 printf("Scored : %d",score);
}

void setupGame()
{
 headX=5;
 headY=2;
}

void inputCheck()
{
 if(kbhit())
 {
  char key=getch();
  switch (key)
  {
   case 'w':
    direction=1;
    break;
   case 'd':
    direction=2;
    break;
   case 's':
    direction=3;
    break;
   case 'a':
    direction=4;
  }
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

int main()
{
    setupGame();
    while(!gameOver){
        create();
        inputCheck();
        moveSnake();
        usleep(speed);
    }    
    usleep(speed);
    system("clear");
}