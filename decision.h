#ifndef DECISION_H
#define DECISION_H

#include "texts.h"
#include "player.h"


void which_decision(int id,int *chosen, int *error)
{
  switch(id)
  {
    case 1:
    if(*chosen == 1)
    {
      if(player1.money < 30)
      {
        *error = 1;
        attron(A_BLINK);
        mvprintw(5,0,"Nie masz tyle pieniedzy...");
        attroff(A_BLINK);
        refresh();
      }
      else
      {
        player1.money -= 30;
        player1.money_spent -= 30;
        player1.reputation_points+=2;
      }
    }
    else
    if(*chosen == 2)
    {
      if(player1.money < 15)
      {
        *error = 1;
        attron(A_BLINK);
        mvprintw(5,0,"Nie masz tyle pieniedzy...");
        attroff(A_BLINK);
        refresh();
      }
      else
      {
        player1.money -= 15;
        player1.money_spent -= 15;
        player1.reputation_points++;
      }
    }
    break;
    case 2:
      if(*chosen == 1)
        {
          player1.sword_pow -= 2;
          player1.money += 10;
          player1.money_gained += 10;
          player1.reputation_points += 2;
        }
      else if (*chosen == 2)
        {
          player1.sword_pow -= 1;
          player1.reputation_points += 1;
        }
      break;
    case 3:
      if(*chosen == 2)
      {
        player1.reputation_points += 1;
      }
      break;
  }
}

void decision(int id, char decision[3][125], int *chosen)
{
initscr();
noecho();

int yMax, xMax, yBeg, xBeg;
//DEKLARACJA OKNA
WINDOW * menu = newwin(3,60,0,0);

keypad(menu,true);


int show = 0;

while(true)
  {


    for(int i = 0; i < 4; i++)
      {
          //GDY OPCJA ZNALEZIONA PODSWIETLAMY JA
          if(i == show)
              wattron(menu, A_REVERSE);

          //A TU WYPISUJEMY I WYLACZAMY PODSWIETLENIE
          mvwprintw(menu,i,0,"%s",decision[i]);
          wattroff(menu,A_REVERSE);

      }
      //POBIERAMY ZNAK CZYLI GORA STRZALKA ALBO DOL
      int key = wgetch(menu);

      //BEDZIEMY TU PRZESUWAC SHOW CZYLI MIEJSCE KTORE BEDZIEMY PODSWIETLAC
      switch(key)
      {
        case KEY_UP:
          move(5,0);
          clrtoeol();
          refresh();
          show--;
          if(show == -1)
            show = 0;
          break;
        case KEY_DOWN:
          move(5,0);
          clrtoeol();
          refresh();
          show++;
          if(show == 3)
            show = 2;
          break;
        default:
          break;
      }
      if(key == 10)
      {
        *chosen = show + 1;
        int if_error = 0;
        int *error = &if_error;
        which_decision(id,chosen,error);
        if(*error != 1)
          break;
      }


}
clear();
endwin();
}

#endif
