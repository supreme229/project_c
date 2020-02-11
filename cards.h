#ifndef CARDS_H
#define CARDS_H

#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "texts.h"

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
            mvprintw(yMax+7+iter,0,"Dodanie 2 pkt twojej karcie. Numer mocy: %d\n",iter+1);
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
        //mvprintw(yMax+5,place,"%c ",enemy_cards.card_id[i]);
        pause1(1.0);
        refresh();
        place+=2;
     }

     for(int i=6;i<12;i++)
     {
       mvprintw(yMax+4,place-12,"%c ",player_cards.card_id[i]);
      // mvprintw(yMax+6,place-12,"%c ",enemy_cards.card_id[i]);
       pause1(1.0);
       refresh();
       place+=2;
     }

     attron(A_BOLD);
     mvprintw(yMax+6,0,"Twoje moce:");
     attroff(A_BOLD);

     int iter = 0;

     for(int i=0;i<3;i++)
     {
      what_powers(player_cards.powers[i],iter,yMax);
      //what_powers(enemy_cards.powers[i],iter+3,yMax);
      pause1(1.0);
      iter++;
    }
}

void plr_power_points(char id,int *player_points, int *enemy_points, int *start_boost_plr, int *power1_left, int *power2_left, int *power3_left)
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
    *player_points += 2;
    break;

    case '5':
    *player_points += 3;
    break;

    case '6':
    *enemy_points /= 2;
    break;
  }
}

void enm_power_points(char id,int *player_points, int *enemy_points, int *start_boost_enm, int *enemy_powers_used)
{
  switch(id)
  {
    case '1':
    *enemy_points *= 2;
    break;

    case '2':
    *player_points -= 2;
    break;

    case '3':
    *enemy_points = 100;
    *start_boost_enm = 1;
    break;

    case '4':
    *enemy_points += 2;
    break;

    case '5':
    *enemy_points += 3;
    break;

    case '6':
    *player_points /= 2;
    break;
  }
  *enemy_powers_used = *enemy_powers_used + 1;
}

void plr_card_points(char id,int *player_points, int *enemy_points)
{
  switch(id)
  {
   case 'T':
      *player_points += 5;
      break;

    case '9':
      *player_points += 3;
      break;

    case 'Q':
      *player_points  += 6;
      break;

    case 'K':
      *player_points += 8;
      break;

    case 'A':
      *player_points += 12;
      break;

    case 'J':
      *player_points += 0;
      *enemy_points -= 5;
      break;
 }
}

void enm_card_points(char id,int *enemy_points, int *player_points)
{
  switch(id)
  {
   case 'T':
      *enemy_points += 5;
      break;

    case '9':
      *enemy_points += 3;
      break;

    case 'Q':
      *enemy_points += 6;
      break;

    case 'K':
      *enemy_points += 8;
      break;

    case 'A':
      *enemy_points += 12;
      break;

    case 'J':
      *enemy_points += 0;
      *player_points -= 5;
      break;
 }
}

void what_chosen_option(int *enemy_powers_used, int *rounds_player, int *rounds_enemy,int *chosen, WINDOW *menu, int card_iterator, int yMax, int *player_points, int *enemy_points, int *start_boost_plr, int *power1_left, int *power2_left, int *power3_left, int *start_boost_enm)
{
  switch(*chosen)
    {
    case 1:
      //nastepna karta po prostu
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      mvwprintw(menu,yMax-14,1,"GRACZ:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-13,1,"Rzucona karta: %c",player_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-12,1,"Uzyto mocy: NIE");
      pause1(1.0);
      wrefresh(menu);
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      mvwprintw(menu,yMax-10,1,"PRZECIWNIK:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      plr_card_points(player_cards.card_id[card_iterator],player_points,enemy_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points,player_points);
      if(*rounds_player - *rounds_enemy >= 2 && *enemy_powers_used != 3)
        {
          enm_power_points(enemy_cards.powers[*enemy_powers_used - 1], player_points,enemy_points,start_boost_enm,enemy_powers_used);
          pause1(1.0);
          wrefresh(menu);
          mvwprintw(menu,yMax-8,1,"Uzyto mocy: TAK",enemy_cards.powers[*enemy_powers_used -1]);
        }
        else
        {
          pause1(1.0);
          wrefresh(menu);
          mvwprintw(menu,yMax-8,1,"Uzyto mocy: NIE",enemy_cards.powers[*enemy_powers_used -1]);
        }

      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-9,1,"Rzucona karta: %c",enemy_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-5,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-4,1,"Ilosc pkt rywala: %d",*enemy_points);
      break;
    case 2:
      //uzycie mocy1 i nastepna karta
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      mvwprintw(menu,yMax-14,1,"GRACZ:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-13,1,"Rzucona karta: %c",player_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-12,1,"Uzyto mocy: TAK");
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-10,1,"PRZECIWNIK:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      plr_card_points(player_cards.card_id[card_iterator],player_points,enemy_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points,player_points);
      plr_power_points(player_cards.powers[0],player_points,enemy_points,start_boost_plr,power1_left, power2_left, power3_left);
      if(*rounds_player - *rounds_enemy >= 2 && *enemy_powers_used != 3)
      {
        enm_power_points(enemy_cards.powers[*enemy_powers_used - 1], player_points,enemy_points,start_boost_enm,enemy_powers_used);
        pause1(1.0);
        wrefresh(menu);
        mvwprintw(menu,yMax-8,1,"Uzyto mocy: TAK",enemy_cards.powers[*enemy_powers_used -1]);
      }
      else
      {
        pause1(1.0);
        wrefresh(menu);
        mvwprintw(menu,yMax-8,1,"Uzyto mocy: NIE",enemy_cards.powers[*enemy_powers_used -1]);
      }

      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-9,1,"Rzucona karta: %c",enemy_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-5,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-4,1,"Ilosc pkt rywala: %d",*enemy_points);
      move(yMax+7,0);
      clrtoeol();
      *power1_left = *power1_left - 1;
      break;
    case 3:
      //uzcie mocy2 i nastepna karta
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      mvwprintw(menu,yMax-14,1,"GRACZ:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-13,1,"Rzucona karta: %c",player_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-12,1,"Uzyto mocy: TAK");
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-10,1,"PRZECIWNIK:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      plr_card_points(player_cards.card_id[card_iterator],player_points,enemy_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points,player_points);
      plr_power_points(player_cards.powers[1],player_points,enemy_points,start_boost_plr,power1_left, power2_left, power3_left);
      if(*rounds_player - *rounds_enemy >= 2 && *enemy_powers_used != 3)
      {
        enm_power_points(enemy_cards.powers[*enemy_powers_used - 1], player_points,enemy_points,start_boost_enm,enemy_powers_used);
        pause1(1.0);
        wrefresh(menu);
        mvwprintw(menu,yMax-8,1,"Uzyto mocy: TAK",enemy_cards.powers[*enemy_powers_used -1]);
      }
      else
      {
        pause1(1.0);
        wrefresh(menu);
        mvwprintw(menu,yMax-8,1,"Uzyto mocy: NIE",enemy_cards.powers[*enemy_powers_used -1]);
      }
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-9,1,"Rzucona karta: %c",enemy_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-5,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-4,1,"Ilosc pkt rywala: %d",*enemy_points);
      move(yMax+8,0);
      clrtoeol();
      *power2_left = *power2_left - 1;
      break;
    case 4:
      //uzycie mocy3 i nastepna karta
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      mvwprintw(menu,yMax-14,1,"GRACZ:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-13,1,"Rzucona karta: %c",player_cards.card_id[card_iterator]);
      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-12,1,"Uzyto mocy: TAK");
      pause1(1.0);
      wrefresh(menu);
      wattron(menu,A_UNDERLINE);
      wattron(menu,A_BOLD);
      mvwprintw(menu,yMax-10,1,"PRZECIWNIK:");
      wattroff(menu,A_UNDERLINE);
      wattroff(menu,A_BOLD);
      plr_card_points(player_cards.card_id[card_iterator],player_points,enemy_points);
      enm_card_points(enemy_cards.card_id[card_iterator],enemy_points,player_points);
      plr_power_points(player_cards.powers[2],player_points,enemy_points,start_boost_plr,power1_left, power2_left, power3_left);
      if(*rounds_player - *rounds_enemy >= 2 && *enemy_powers_used != 3)
      {
        enm_power_points(enemy_cards.powers[*enemy_powers_used - 1], player_points,enemy_points,start_boost_enm,enemy_powers_used);
        pause1(1.0);
        wrefresh(menu);
        mvwprintw(menu,yMax-8,1,"Uzyto mocy: TAK",enemy_cards.powers[*enemy_powers_used -1]);
      }
      else
      {
        pause1(1.0);
        wrefresh(menu);
        mvwprintw(menu,yMax-8,1,"Uzyto mocy: NIE",enemy_cards.powers[*enemy_powers_used -1]);
      }

      pause1(1.0);
      wrefresh(menu);
      mvwprintw(menu,yMax-9,1,"Rzucona karta: %c",enemy_cards.card_id[card_iterator]);

      pause1(1.0);
      wrefresh(menu);
      pause1(1.0);
      wrefresh(menu);

      mvwprintw(menu,yMax-5,1,"Ilosc twoich pkt: %d",*player_points);
      mvwprintw(menu,yMax-4,1,"Ilosc pkt rywala: %d",*enemy_points);
      move(yMax+9,0);
      clrtoeol();
      *power3_left = *power3_left - 1;
      break;
    }
    wrefresh(menu);
}

void write_cards(int yMax)
{

int place = 0;

  for(int i=0;i<6;i++)
  {
     mvprintw(yMax+3,place,"%c ",player_cards.card_id[i]);
     //mvprintw(yMax+5,place,"%c ",enemy_cards.card_id[i]);
     //pause1(1.0);
     refresh();
     place+=2;
  }

  for(int i=6;i<12;i++)
  {
    mvprintw(yMax+4,place-12,"%c ",player_cards.card_id[i]);
   // mvprintw(yMax+6,place-12,"%c ",enemy_cards.card_id[i]);
    //pause1(1.0);
    refresh();
    place+=2;
  }

}

void main_war(int intro, int *enemy_powers_used, int *power1_left, int *power2_left, int *power3_left, int *chosen,int card_iterator, int *player_points, int *enemy_points, int *start_boost_plr, int *start_boost_enm, int *rounds_player, int *rounds_enemy)
{
  initscr();
  noecho();

  int yMax, xMax, yBeg, xBeg;
  //DEKLARACJA OKNA
  WINDOW * menu = newwin(20,35,1,0);

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
    mvprintw(yBeg,37,"Przypomnienie oznaczen kart:");
    attroff(A_BOLD);
    mvprintw(yBeg + 1, 37,"A - as (12 pkt)");
    mvprintw(yBeg + 2, 37,"K - krol (8 pkt)");
    mvprintw(yBeg + 3, 37,"Q - dama (6 pkt)");
    mvprintw(yBeg + 4, 37,"T - dziesiatka (5 pkt)");
    mvprintw(yBeg + 5, 37,"9 - dziewiatka (3 pkt)");
    mvprintw(yBeg + 6, 37,"J - jopek (0 pkt ale przeciwnik -5 pkt)");

    refresh();

  }
else
{
  attron(A_BOLD);
  mvprintw(yMax+2,xBeg+15,"Nastepna karta: ",player_cards.card_id[card_iterator]);
  attroff(A_BOLD);
  mvprintw(yMax+3,xBeg+15,"%c",player_cards.card_id[card_iterator]);
  write_cards(yMax);


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
  what_chosen_option(enemy_powers_used,rounds_player,rounds_enemy,chosen,menu,card_iterator,yMax,player_points,enemy_points,start_boost_plr,power1_left,power2_left,power3_left,start_boost_enm);
  pause1(1.0);
  if(*power1_left == 0 && *power2_left == 0 && *power3_left == 0)
    {
      move(yMax+6,0);
      clrtoeol();
    }

  if(*player_points > *enemy_points)
  {
    *rounds_player = *rounds_player + 1;
    wattron(menu,A_BLINK);
    mvwprintw(menu,yMax-2,1,"Wygrywasz ta runde!");
    wattroff(menu,A_BLINK);
  }
  else
    if(*player_points < *enemy_points)
    {
      *rounds_enemy = *rounds_enemy + 1;
      wattron(menu,A_BLINK);
      mvwprintw(menu,yMax-2,1,"Przegrywasz ta runde...");
      wattroff(menu,A_BLINK);
    }
    else
     {
      wattron(menu,A_BLINK);
      mvwprintw(menu,yMax-2,1,"Remis!");
      wattroff(menu,A_BLINK);
    }
    wrefresh(menu);

    attron(A_BOLD);
    mvprintw(yBeg+9,41,"Ilosc rund wygranych:");
    attroff(A_BOLD);
    mvprintw(yBeg+10,37,"Lambert: %d      Przeciwnik: %d ",*rounds_player,*rounds_enemy);
    refresh();


  getch();
}

endwin();
}
#endif
