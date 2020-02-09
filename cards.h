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
            mvprintw(yMax+7+iter,0,"Podwojenie punktow twojej karty. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '2':
            mvprintw(yMax+7+iter,0,"Oslabienie mocy karty przeciwnika o 2pkt. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '3':
            mvprintw(yMax+7+iter,0,"Automatyczne wygranie rundy i 2 pkt. dodatkowe na start w nastepnej rundzie. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '4':
            mvprintw(yMax+7+iter,0,"Blokada jopka, traci wlasciowsc bicia asa u przeciwnika w rundzie. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '5':
            mvprintw(yMax+7+iter,0,"Dodanie 3 pkt twojej karcie. Numer mocy: %d\n",iter+1);
            refresh();
            break;
        case '6':
            mvprintw(yMax+7+iter,0,"Podzielenie mocy karty przeciwnika przez 2. Numer mocy: %d\n",iter+1);
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

    while(remaining_cards != 0)
    {
      enemy_cards.card_id[card_counter - 12] = war_cards_code[card_counter];
      card_counter++;
      remaining_cards--;
    }

     for(int i=0;i<6;i++)
     {
        mvprintw(yMax+3,place,"%c ",player_cards.card_id[i]);
        mvprintw(yMax+5,place,"%c ",enemy_cards.card_id[i]);
        pause1(1.0);
        refresh();
        place+=2;
     }

     for(int i=6;i<12;i++)
     {
       mvprintw(yMax+4,place-12,"%c ",player_cards.card_id[i]);
       mvprintw(yMax+6,place-12,"%c ",enemy_cards.card_id[i]);
       pause1(1.0);
       refresh();
       place+=2;
     }

     attron(A_BOLD);
    // mvprintw(yMax+6,0,"Twoje moce:");
     attroff(A_BOLD);

     int iter = 0;

     for(int i=0;i<3;i++)
     {
      what_powers(player_cards.powers[i],iter,yMax);
      pause1(1.0);
      iter++;
     }
}

void plr_power_points(char id,int *player_points, int *enemy_points, int *start_boost_plr, int *ace_not_blocked, int *power1_left, int *power2_left, int *power3_left)
{
  switch(id)
  {
    case '1':
    *player_points *= 2;
    break;

    case '2':
    *enemy_points -= 2;
    break;

    case '3':
    *player_points = 100;
    *start_boost_plr = 1;
    break;

    case '4':
    *ace_not_blocked = 1;
    break;

    case '5':
    *player_points += 3;
    break;

    case '6':
    *enemy_points /= 2;
    break;
  }
}

void plr_card_points(char id,int *player_points)
{
  switch(id)
  {
   case 'T':
      *player_points = 5;
      break;

    case '9':
      *player_points = 3;
      break;

    case 'Q':
      *player_points  = 6;
      break;

    case 'K':
      *player_points = 8;
      break;

    case 'A':
      *player_points = 12;
      break;

    case 'J':
      *player_points = 0;
      break;
 }
}

void enm_card_points(char id,int *enemy_points)
{
  switch(id)
  {
   case 'T':
      *enemy_points = 5;
      break;

    case '9':
      *enemy_points = 3;
      break;

    case 'Q':
      *enemy_points  = 6;
      break;

    case 'K':
      *enemy_points = 8;
      break;

    case 'A':
      *enemy_points = 12;
      break;

    case 'J':
      *enemy_points = 0;
      break;
 }
}

void what_chosen(int *chosen, WINDOW *menu, int card_iterator, int yMax, int *player_points, int *enemy_points, int *start_boost_plr, int *ace_not_blocked, int *power1_left, int *power2_left, int *power3_left)
{
  switch(*chosen)
    {
    case 1:
      //nastepna karta po prostu
      mvwprintw(menu,yMax-9,1,"Twoja karta to: %c",player_cards.card_id[card_iterator]);
      mvwprintw(menu,yMax-8,1,"Nr uzytej mocy: Nie uzyto mocy!");
      plr_card_points(player_cards.card_id[card_iterator],player_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points);
      mvwprintw(menu,yMax-7,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-6,1,"Ilosc pkt rywala: %d",*enemy_points);

      break;
    case 2:
      //uzycie mocy1 i nastepna karta
      mvwprintw(menu,yMax-9,1,"Twoja karta to: %c",player_cards.card_id[card_iterator]);
      mvwprintw(menu,yMax-8,1,"Nr uzytej mocy: 1");
      plr_card_points(player_cards.card_id[card_iterator],player_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points);
      plr_power_points(player_cards.powers[0],player_points,enemy_points,ace_not_blocked,start_boost_plr,power1_left, power2_left, power3_left);
      mvwprintw(menu,yMax-7,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-6,1,"Ilosc pkt rywala: %d",*enemy_points);
      move(yMax+7,0);
      clrtoeol();
      *power1_left = *power1_left - 1;
      break;
    case 3:
      //uzcie mocy2 i nastepna karta
      mvwprintw(menu,yMax-9,1,"Twoja karta to: %c",player_cards.card_id[card_iterator]);
      mvwprintw(menu,yMax-8,1,"Nr uzytej mocy: 2");
      plr_card_points(player_cards.card_id[card_iterator],player_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points);
      plr_power_points(player_cards.powers[1],player_points,enemy_points,ace_not_blocked,start_boost_plr,power1_left, power2_left, power3_left);
      mvwprintw(menu,yMax-7,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-6,1,"Ilosc pkt rywala: %d",*enemy_points);
      move(yMax+8,0);
      clrtoeol();
      *power2_left = *power2_left - 1;
      break;
    case 4:
      //uzycie mocy3 i nastepna karta
      mvwprintw(menu,yMax-9,1,"Twoja karta to: %c",player_cards.card_id[card_iterator]);
      mvwprintw(menu,yMax-8,1,"Nr uzytej mocy: 3");
      plr_card_points(player_cards.card_id[card_iterator],player_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points);
      plr_power_points(player_cards.powers[2],player_points,enemy_points,ace_not_blocked,start_boost_plr,power1_left, power2_left, power3_left);
      mvwprintw(menu,yMax-7,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-6,1,"Ilosc pkt rywala: %d",*enemy_points);
      move(yMax+9,0);
      clrtoeol();
      *power3_left = *power3_left - 1;
      break;
    }
    wrefresh(menu);
}

void main_war(int intro,int *power1_left, int *power2_left, int *power3_left, int *chosen,int card_iterator, int *player_points, int *enemy_points, int *start_boost_plr, int *start_boost_enemy,int *ace_not_blocked)
{
  initscr();
  noecho();

  int yMax, xMax, yBeg, xBeg;
  //DEKLARACJA OKNA
  WINDOW * menu = newwin(15,35,1,0);
  box(menu,0,0);

    if(intro == 1)
    {


    //POBRANIE POCZATKU OKNA I KONIEC (JEGO GRANIC)
    getbegyx(menu,yBeg,xBeg);
    getmaxyx(menu,yMax,xMax);
    refresh();

    wattron(menu,A_BOLD);
    wrefresh(menu);

    //POCZATEK
    attron(A_BOLD);
    mvprintw(yBeg-1,xBeg,"Menu gry:\n");
    attroff(A_BOLD);

    refresh();
    pause1(1.0);

    mvwprintw(menu,yBeg,1,"Czas na rozdanie kart...");
    wrefresh(menu);

    pause1(0.5);

    attron(A_BOLD);
    mvprintw(yMax+2,xBeg,"Twoja talia: ");
    attroff(A_BOLD);

    give_cards_and_powers(yMax);
    wrefresh(menu);

    pause1(1.0);
    refresh();

    attron(A_BOLD);
    mvprintw(yBeg,32,"Przypomnienie oznaczen kart:");
    attroff(A_BOLD);
    mvprintw(yBeg + 1, 37,"A - as");
    mvprintw(yBeg + 2, 37,"K - krol");
    mvprintw(yBeg + 3, 37,"Q - dama");
    mvprintw(yBeg + 4, 37,"T - dziesiatka");
    mvprintw(yBeg + 5, 37,"9 - dziewiatka");
    mvprintw(yBeg + 6, 37,"J - jopek");

    refresh();

  }
else
{
  keypad(menu,true);

  int show = 0;
  char *options[] = {
    "Rzuc kolejna karte.",
    "Uzyj mocy 1",
    "Uzyj mocy 2",
    "Uzyj mocy 3"
  };

while(true)
  {
    for(int i = 0; i < 4; i++)
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
          if(show == 4)
            show = 3;
          break;
        default:
          break;
      }
      //10 - "ENTER" GDY UZTYKOWNIK GO WCISNIE MENU ZNIKA I IDZIEMY DALEJ
      if(key == 10)
      {
        *chosen = show + 1;
          if(*chosen == 1 || (*chosen == 2 && *power1_left != 0) || (*chosen == 3 && *power2_left != 0) || (*chosen == 4 && *power3_left != 0) )
            {
            move(yMax+1,0);
            clrtoeol();
            break;
            }
          else
            if((*chosen == 2 && *power1_left == 0) || (*chosen == 3 && *power2_left == 0) || (*chosen == 4 && *power3_left == 0))
            {
              attron(A_BLINK);
              mvprintw(yMax+1,0,"Brak tej mocy!");
              attroff(A_BLINK);
              refresh();
            }
      }
  }
  what_chosen(chosen,menu,card_iterator,yMax,player_points,enemy_points,start_boost_plr,ace_not_blocked,power1_left,power2_left,power3_left);
  pause1(1.0);
  if(*power1_left == 0 && *power2_left == 0 && *power3_left == 0)
    {
      move(yMax+6,0);
      clrtoeol();
    }
  getch();
}

endwin();
}
#endif
