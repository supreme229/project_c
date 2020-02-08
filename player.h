#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

struct player{
  int hp_max;
  int hp;
  int money;
  int vigor;
  int sword_pow;
  int monsters_killed;
  int money_spent;
  int money_gained;
}player1 = {100,1,110,2,0,0,0,0};

void print_stats()
{
  initscr();
  noecho();

  //DEKLARACJA OKNA
  WINDOW * menu = newwin(12,35,1,0);

  int yMax, xMax, yBeg, xBeg;
  getbegyx(menu,yBeg,xBeg);
  getmaxyx(menu,yMax,xMax);

  //WPISY INFORMACYJNE
  //POCZATEK
  attron(A_BOLD);
  mvprintw(yBeg-1,xBeg,"Statystyki rozgrywki:\n");
  attroff(A_BOLD);

  refresh();

  wattron(menu,A_BOLD);
  box(menu,32,0);
  wattroff(menu,A_BOLD);

//  wattron(menu,A_BOLD);
  wattron(menu,A_UNDERLINE);
  wattron(menu,A_BOLD);
  mvwprintw(menu,yBeg,xBeg+1,"Statystyki postaci i ekwipunku:");
  wattroff(menu,A_BOLD);
  wattroff(menu,A_UNDERLINE);

  mvwprintw(menu,yBeg+1,xBeg+1,"Ilosc pieniedzy: %d koron\n",player1.money);
  mvwprintw(menu,yBeg+2,xBeg+1,"Maksymalna ilosc zycia: %d HP\n",player1.hp_max);
  mvwprintw(menu,yBeg+3,xBeg+1,"Obecna ilosc zycia: %d HP\n",player1.hp);
  mvwprintw(menu,yBeg+4,xBeg+1,"Zadawane obrazenia mieczem: %d DMG\n\n",player1.sword_pow);

  wattron(menu,A_UNDERLINE);
  wattron(menu,A_BOLD);
  mvwprintw(menu,yBeg+6,xBeg+1,"Statystyki rozgrywki:");
  wattroff(menu,A_BOLD);
  wattroff(menu,A_UNDERLINE);

  mvwprintw(menu,yBeg+7,xBeg+1,"Ilosc zabitych potworow: %d \n",player1.monsters_killed);
  mvwprintw(menu,yBeg+8,xBeg+1,"Wydane pieniadze: %d koron\n",player1.money_spent);
  mvwprintw(menu,yBeg+9,xBeg+1,"Zarobione pieniadze: %d koron\n",player1.money_gained);

  wrefresh(menu);
  //wattroff(menu,A_BOLD);


  getch();
  endwin();
  clear();
  //KONIEC

}

#endif
