#ifndef SHOP_MENU_H
#define SHOP_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "structures.h"
#include "player.h"

int check (int rand_id, int id_tab[], int size)
{
  for(int i = 0; i < size; i++)
  {
    if(rand_id == id_tab[i])
      return 0;
  }
  return 1;
}

void which_bought(int id)
{
  switch(id)
    {
      case 0:
        player1.sword_pow += item.attribute[id];
        break;
      case 1:
        player1.sword_pow += item.attribute[id];
        break;
      case 2:
        player1.hp_max += item.attribute[id];
        player1.hp = player1.hp_max;
        break;
      case 3:
        if(player1.hp_max - player1.hp < item.attribute[id])
            player1.hp = player1.hp_max;
        else
            player1.hp += item.attribute[id];
        break;
      case 4:
        player1.sword_pow += item.attribute[id];
        break;
      case 5:
        player1.vigor++;
        break;
    }
}

void print_shop_menu(int shop_level, int *chosen, int *improvement)
{
  initscr();
  noecho();

  int yMax, xMax, yBeg, xBeg;
  //DEKLARACJA OKNA
  WINDOW * menu = newwin(9,60,1,0);

  //POBRANIE POCZATKU OKNA I KONIEC (JEGO GRANIC)
  getbegyx(menu,yBeg,xBeg);
  getmaxyx(menu,yMax,xMax);

  //WPISY INFORMACYJNE
  //POCZATEK
  attron(A_BOLD);
  mvprintw(yBeg-1,xBeg,"Menu sklepu:\n");
  attroff(A_BOLD);

  attron(A_BOLD);
  mvprintw(yMax+1,xBeg,"Przypomnienie: poruszamy sie po menu strzalkami gora, dol.\n");
  attroff(A_BOLD);
  refresh();

  wattron(menu,A_BOLD);
  box(menu,0,0);
  wrefresh(menu);
  wattroff(menu,A_BOLD);

  wattron(menu,A_BOLD);
  mvwprintw(menu,1,1,"Dostepne przedmioty:");
  mvwprintw(menu,yMax-2,xBeg+1,"Fundusze : %d",player1.money);
  mvwprintw(menu,1,xMax-10,"Cena:");
  wattroff(menu,A_BOLD);
  //KONIEC

  //MOZLIWOSCI
  //char *shop_items[];
  int randomized_id, check_id = 0,id_tab[4] = {10,10,10,10}, iter = 0;
  srand( time( NULL ) );

  while(id_tab[3] == 10)
  {
    randomized_id = rand() % shop_level + *improvement;

    check_id = check(randomized_id, id_tab, 4);
    if(check_id == 1)
    {
      id_tab[iter] = randomized_id;
      iter++;
    }
  }


  //WLACZENIE WCZYTYWANIA ZNAKOW Z KLAWIATURY (KEY_UP ITD.)
  keypad(menu,true);

  //ZMIENNA OKRESLAJACA JAKA OPCJE WSKAZUJEMY
  int show = 0;

while(true)
  {
    for(int i = 0; i < 4; i++)
      {
          //GDY OPCJA ZNALEZIONA PODSWIETLAMY JA
          if(i == show)
              wattron(menu, A_REVERSE);

          //A TU WYPISUJEMY I WYLACZAMY PODSWIETLENIE
          mvwprintw(menu,i+2,1,item.name[id_tab[i]]);
          wattroff(menu,A_REVERSE);
          mvwprintw(menu,i+2,xMax-10,item.price_str[id_tab[i]]);
          wattron(menu, A_REVERSE);
          wattroff(menu,A_REVERSE);
      }
      //POBIERAMY ZNAK CZYLI GORA STRZALKA ALBO DOL
      int key = wgetch(menu);

      //BEDZIEMY TU PRZESUWAC SHOW CZYLI MIEJSCE KTORE BEDZIEMY PODSWIETLAC
      switch(key)
      {
        case KEY_UP:
          show--;
          if(show == -1)
            show = 0;
          break;
        case KEY_DOWN:
          show++;
          if(show == 5)
            show = 4;
          break;
        default:
          break;
      }
      move(11,0);
      clrtoeol();
      refresh();
      //10 - "ENTER" GDY UZYTKOWNIK GO WCISNIE MENU ZNIKA I IDZIEMY DALEJ
      if(key == 10 && player1.money - item.price[item.id[id_tab[show]] ] >= 0)
      {
        player1.money -= item.price[item.id[id_tab[show]]];
        player1.money_spent += item.price[item.id[id_tab[show]]];
        *chosen = item.id[id_tab[show]];
        which_bought(id_tab[show]);
        break;
      }
      if(key == KEY_LEFT)
      {
        break;
      }
      if(key == 10 && player1.money - item.price[item.id[id_tab[show]]] < 0)
      {
        attron(A_BLINK);
        mvprintw(11,0,"Twoje fundusze sa nie wystarczajace!");
        attroff(A_BLINK);
        refresh();
      }
  }
  //ZAMYKAMY OKNO
  clear();
  endwin();
}

#endif
