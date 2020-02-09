#ifndef CARDS_H
#define CARDS_H

#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

//zamiana wartosci
void swap(char *a, char *b)
{
char temp = *a;
*a = *b;
*b = temp;
}
void what_powers(char id,int iter,int yMax)
{
  switch(id)
  {
        case '1':
            mvprintw(yMax+6+iter,0,"Podwojenie punktow twojej karty. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '2':
            mvprintw(yMax+6+iter,0,"Oslabienie mocy karty przeciwnika o 2pkt. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '3':
            mvprintw(yMax+6+iter,0,"Automatyczne wygranie rundy i 2 pkt. dodatkowe na start w nastepnej rundzie. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '4':
            mvprintw(yMax+6+iter,0,"Blokada jopka, traci wlasciowsc bicia asa u przeciwnika w rundzie. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '5':
            mvprintw(yMax+6+iter,0,"Dodanie 3 pkt twojej karcie. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '6':
            mvprintw(yMax+6+iter,0,"Dzieli punkty rywala w rundzie na pol. Numer mocy: %d\n",iter+1);
            refresh();
            break;
  }
}
//rozdanie kart
void give_cards_and_powers(int yMax)
{
    char war_cards_code[24] = {'T','T','T','T','9','9','9','9','K','K','K','K','Q','Q','Q','Q','A','A','A','A','J','J','J','J'};
    char all_powers[6]= {'1','2','3','4','5','6'};

    srand((unsigned)time(NULL));

    for(int i = 5; i > 0; i--)
    {
      int j = rand() % (i+1);
      swap(&all_powers[i],&all_powers[j]);
    }

    for(int i = 23; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(&war_cards_code[i],&war_cards_code[j]);
    }


    int place = 0;
    int remaining_cards = 24, power_counter = 0, card_counter = 0,remaining_powers = 6;

    while(remaining_powers != 3)
    {
      player_cards.powers[power_counter] = all_powers[power_counter];
      power_counter++;
      remaining_powers--;
    }

    while(remaining_powers != 0)
    {
      enemy_cards.powers[power_counter-3] = all_powers[power_counter];
      power_counter++;
      remaining_powers--;
    }

    while(remaining_cards != 12)
    {
      player_cards.card_id[card_counter] = war_cards_code[card_counter];
      card_counter++;
      remaining_cards--;
    }

    while(remaining_cards!=0)
    {
      enemy_cards.card_id[card_counter - 11] = war_cards_code[card_counter];
      card_counter++;
      remaining_cards--;
    }

     for(int i=0;i<6;i++)
     {
        mvprintw(yMax+2,place,"%c ",player_cards.card_id[i]);
        pause1(1.0);
        refresh();
        place+=2;
     }

     for(int i=6;i<12;i++)
     {
       mvprintw(yMax+3,place-12,"%c ",player_cards.card_id[i]);
       pause1(1.0);
       refresh();
       place+=2;
     }

     attron(A_BOLD);
     mvprintw(yMax+5,0,"Twoje moce:");
     attroff(A_BOLD);

     int iter = 0;

     for(int i=0;i<3;i++)
     {
      what_powers(player_cards.powers[i],iter,yMax);
      pause1(1.0);
      iter++;
     }
}

void main_war(int intro)
{
    initscr();
    noecho();

    int yMax, xMax, yBeg, xBeg;
    //DEKLARACJA OKNA
    WINDOW * menu = newwin(9,30,1,0);

    //POBRANIE POCZATKU OKNA I KONIEC (JEGO GRANIC)
    getbegyx(menu,yBeg,xBeg);
    getmaxyx(menu,yMax,xMax);
    refresh();

    wattron(menu,A_BOLD);
    box(menu,0,0);
    wrefresh(menu);

    //POCZATEK
    attron(A_BOLD);
    mvprintw(yBeg-1,xBeg,"Menu gry:\n");
    attroff(A_BOLD);

    refresh();
    pause1(1.0);

    if(intro == 1)
    {

    mvwprintw(menu,yBeg,1,"Czas na rozdanie kart...");
    wrefresh(menu);

    //refresh();

    pause1(1.0);

    attron(A_BOLD);
    mvprintw(yMax+1,xBeg,"Twoja talia: ");
    attroff(A_BOLD);

    give_cards_and_powers(yMax);
    wrefresh(menu);

    pause1(1.0);
    refresh();

    attron(A_BOLD);
    mvprintw(yBeg,32,"Przypomnienie oznaczen kart:");
    attroff(A_BOLD);
    mvprintw(yBeg + 1, 32,"A - as");
    mvprintw(yBeg + 2, 32,"K - krol");
    mvprintw(yBeg + 3, 32,"Q - dama");
    mvprintw(yBeg + 4, 32,"T - dziesiatka");
    mvprintw(yBeg + 5, 32,"9 - dziewiatka");
    mvprintw(yBeg + 6, 32,"J - jopek");

    refresh();

  }
else
{
  keypad(menu,true);

  int show = 0;
  char *options[] = {
    "Uzyj mocy.",
    "Rzuc kolejna karte.",
  };

while(true)
  {
    for(int i = 0; i < 2; i++)
      {
          //GDY OPCJA ZNALEZIONA PODSWIETLAMY JA
          if(i == show)
              wattron(menu, A_REVERSE);

          //A TU WYPISUJEMY I WYLACZAMY PODSWIETLENIE
          mvwprintw(menu,i+1,1,options[i]);
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
          if(show == 2)
            show = 1;
          break;
        default:
          break;
      }
      //10 - "ENTER" GDY UZTYKOWNIK GO WCISNIE MENU ZNIKA I IDZIEMY DALEJ
      /*if(key == 10)
      {
        *chosen = show + 1;
        if(*chosen == 1)
          break;
        else

      }*/
  }
//  *chosen = show + 1;
}

    endwin();
}
#endif
