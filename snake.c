/**
Main executable source
**/

#include <ncurses.h>

void main(void){
  initscr();
  cbreak();
  noecho();

  endwin();
}
