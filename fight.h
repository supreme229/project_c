#include "structures.h"
#include "player.h"

#include <ncurses.h>
#include <time.h>

int igni = 2, quen = 2;
int *number_of_igni_left = &igni, *number_of_quen_left = &quen;


void what_chosen(int *chosen,int monster_id)
{
  srand( time( NULL ) );

  int amount_of_damage_player, if_hard_attack_success;

  switch(*chosen)
  {
    case 1:
      if(rand() % 4 == 0)
        if_hard_attack_success = 0;
      else
        if_hard_attack_success = 1;

      amount_of_damage_player = player1.sword_pow * 2 * if_hard_attack_success;
      enemy.hp[monster_id] -= amount_of_damage_player;
      break;
    case 2:
      amount_of_damage_player = player1.sword_pow;
      enemy.hp[monster_id] -= amount_of_damage_player;
      break;
    case 3:
      *number_of_igni_left = 2;
      break;
    case 4:
      *number_of_quen_left = 2;
      break;
  }
}

void fight(int *chosen,int monster_id)
{
  initscr();
  noecho();

  int yMax, xMax, yBeg, xBeg;

  //DEKLARACJA OKNA
  WINDOW * menu = newwin(13,40,1,0);

  //POBRANIE POCZATKU OKNA I KONIEC (JEGO GRANIC)
  getbegyx(menu,yBeg,xBeg);
  getmaxyx(menu,yMax,xMax);

  //WPISY INFORMACYJNE
  //POCZATEK
  attron(A_BOLD);
  mvprintw(yBeg-1,xBeg,"Menu walki:\n");
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
    "Zaatakuj mocnym atakiem.",
    "Zaatakuj szybkim atakiem.",
    "Uzyj Igni",
    "Uzyj Quen"
  };

  //WLACZENIE WCZYTYWANIA ZNAKOW Z KLAWIATURY (KEY_UP ITD.)
  keypad(menu,true);

  //ZMIENNA OKRESLAJACA JAKA OPCJE WSKAZUJEMY
  int show = 0;

  wattron(menu, A_UNDERLINE);
  wattron(menu, A_BOLD);
  mvwprintw(menu,yMax-6,1,"Informacje o graczu i przeciwniku:");
  wattroff(menu, A_BOLD);
  wattroff(menu, A_UNDERLINE);

  wattron(menu,A_BOLD);
  wattron(menu,A_UNDERLINE);
  mvwprintw(menu,yMax-4,1,"Lambert:");
  wattroff(menu,A_BOLD);
  wattroff(menu,A_UNDERLINE);
  mvwprintw(menu,yMax-3,1,"Ilosc HP: %d",player1.hp);
  mvwprintw(menu,yMax-2,1,"Moc miecza: %d",player1.sword_pow);
  wattron(menu,A_BOLD);
  wattron(menu,A_UNDERLINE);
  mvwprintw(menu,yMax-4,23,"%s",enemy.name[monster_id]);
  wattroff(menu,A_BOLD);
  wattroff(menu,A_UNDERLINE);
  mvwprintw(menu,yMax-3,23,"Ilosc HP: %d",enemy.hp[monster_id]);
  mvwprintw(menu,yMax-2,23,"Zadawany DMG: %d",enemy.damage[monster_id]);

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
  *chosen = show + 1;

  if((*chosen == 3 && number_of_igni_left == 0) || (*chosen == 4 && number_of_quen_left == 0))
  {
    printw("Nie masz wystarczajacej mocy!"); //NIE WYPISUJE SIE
    refresh();
  }



  if(*chosen == 1 || *chosen == 2)
  {
  move(yMax+2,0);
  clrtoeol();
  }
  //ZAMYKAMY OKNO
  endwin();

}
