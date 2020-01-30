#ifndef MAIN_TASK_H
#define MAIN_TASK_H
#include "structures.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>



void print_current_main_task(int id_task)
{
  initscr();
  noecho();

  //DEKLARACJA OKNA
  WINDOW * menu = newwin(7,43,1,0);

  int yMax, xMax, yBeg, xBeg;
  getbegyx(menu,yBeg,xBeg);
  getmaxyx(menu,yMax,xMax);

  //WPISY INFORMACYJNE
  //POCZATEK
  attron(A_BOLD);
  mvprintw(yBeg-1,xBeg,"Obecne zlecenie:\n");
  attroff(A_BOLD);

  refresh();

  wattron(menu,A_BOLD);
  box(menu,32,0);
  wattroff(menu,A_BOLD);

//  wattron(menu,A_BOLD);
  if(id_task != 0)
  {
  mvwprintw(menu,yBeg+1,xBeg+1,"Nazwa potwora: %s\n",enemy.name[id_task]);
  mvwprintw(menu,yBeg+2,xBeg+1,"Nagroda za zabicie: %d Koron\n",enemy.reward_int[id_task]);
  mvwprintw(menu,yBeg+3,xBeg+1,"Zadawane obrazenia przez potwora: %d DMG\n",enemy.damage[id_task]);
  }
  else
  {
    mvwprintw(menu,yBeg+2,xBeg+8,"Brak aktywnego zlecenia!");
  }
  wrefresh(menu);
  //wattroff(menu,A_BOLD);


  getch();
  endwin();
  clear();
}
#endif
