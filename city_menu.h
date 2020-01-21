#ifndef CITY_MENU_H
#define CITY_MENU_H

#include <ncurses.h>

void print_town_menu(int *chosen)
{

  initscr();
  noecho();

  int yMax, xMax, yBeg, xBeg;
  //DEKLARACJA OKNA
  WINDOW * menu = newwin(7,40,1,0);

  //POBRANIE POCZATKU OKNA I KONIEC (JEGO GRANIC)
  getbegyx(menu,yBeg,xBeg);
  getmaxyx(menu,yMax,xMax);

  //WPISY INFORMACYJNE
  //POCZATEK
  attron(A_BOLD);
  mvprintw(yBeg-1,xBeg,"Menu miasta:\n");
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
  mvwprintw(menu,1,1,"Mozliwe aktywnosci:");
  wattroff(menu,A_BOLD);
  //KONIEC

  //MOZLIWOSCI
  char *activities[] = {
    "Udaj sie do sklepu.",
    "Przejrzyj obecne zlecenie.",
    "Zobacz statystyki postaci.",
    "Idz dalej."
  };

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
          mvwprintw(menu,i+2,1,activities[i]);
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
          if(show == 4)
            show = 3;
          break;
        default:
          break;
      }
      //10 - "ENTER" GDY UZTYKOWNIK GO WCISNIE MENU ZNIKA I IDZIEMY DALEJ
      if(key == 10)
        break;
  }
  getch();
  //ZAMYKAMY OKNO
  endwin();
  //TU ZDOBEDZIEMY INFORMACJE ZWROTNA JAKA OPCJE SPOSROD 4 WYBRAL GRACZ
  *chosen = show + 1;
}

#endif
