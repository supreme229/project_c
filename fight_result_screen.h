#ifndef FIGHT_RESULT_SCREEN_H
#define FIGHT_RESULT_SCREEN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

void result_screen(int result)
{
  initscr();
  noecho();

  int yMax, xMax, yBeg, xBeg;

  //DEKLARACJA OKNA
  WINDOW * menu = newwin(7,50,1,0);

  refresh();

  box(menu,0,0);
  wrefresh(menu);

  if(result == 1)
  {
  wattron(menu,A_BOLD);
  mvwprintw(menu,2,10,"Gratulacje wygrales walke!");
  wattroff(menu,A_BOLD);

  wattron(menu,A_BLINK);
  mvwprintw(menu,4,4,"Nacisnij dowolny przycisk, by kontynuowac.");
  wattroff(menu,A_BLINK);
  wrefresh(menu);
  }
  else
  {
    wattron(menu,A_BOLD);
    mvwprintw(menu,2,17,"Nie zyjesz...");
    wattroff(menu,A_BOLD);

    wattron(menu,A_BLINK);
    mvwprintw(menu,4,3,"Nacisnij dowolny przycisk, by ponowic walke.");
    wattroff(menu,A_BLINK);
    wrefresh(menu);
  }

  getch();
  endwin();
}

#endif
