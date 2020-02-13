#ifndef FIGHT_H
#define FIGHT_H

#include "structures.h"
#include "player.h"


#include <ncurses.h>
#include <time.h>
#include <unistd.h>

int cheat_attempt;

int damage_enemy;
int *amount_of_damage_enemy = &damage_enemy;

void pause4(int time)
{
  fflush(stdout);
  usleep(time * 1000000);
}

int igni_attack(int sword_power, int *igni_next_round)
{
  int igni_attack_pow = ((rand() % (sword_power * 2)) + 2);

  int if_igni_next_round = rand() % 3;

  if(if_igni_next_round == 1)
  {
    *igni_next_round = 1;
  }
  else
    *igni_next_round = 0;

  return igni_attack_pow;
}

int hard_attack(int sword_power)
{
  int if_hard_attack_success;

  if(rand() % 4 == 0)
    if_hard_attack_success = 0;
  else
    if_hard_attack_success = 1;

  return sword_power * 2 * if_hard_attack_success;
}

int quick_attack(int sword_power)
{
  return sword_power;
}

void what_chosen(int *chosen,int monster_id,int *enemy_alive,WINDOW *menu,int yMax, int *igni_next_round, int *quen_def)
{
  srand( time( NULL ) );

  int damage_plr = 0;
  int *amount_of_damage_player = &damage_plr, sword_power = player1.sword_pow;

  if(cheat_attempt !=1)
  {
  switch(*chosen)
  {
    case 1:
      if(*igni_next_round == 1)
        {
          refresh();
          *amount_of_damage_player = (rand() % ((sword_power * 2) - 2) + 2);
          *igni_next_round = 0;
        }
      *amount_of_damage_player += hard_attack(sword_power);
      enemy.hp[monster_id] -= *amount_of_damage_player;
      mvwprintw(menu,yMax-3,1,"Zadales: %d DMG",*amount_of_damage_player);
      break;
    case 2:
    if(*igni_next_round == 1)
      {
        refresh();
        *amount_of_damage_player = (rand() % ((sword_power * 2) - 2) + 2);
        *igni_next_round = 0;
      }
      *amount_of_damage_player += quick_attack(sword_power);
      enemy.hp[monster_id] -= *amount_of_damage_player;
      mvwprintw(menu,yMax-3,1,"Zadales: %d DMG",*amount_of_damage_player);
      break;
    case 3:
      if(*igni_next_round == 1)
        {
          refresh();
          *amount_of_damage_player = (rand() % ((sword_power * 2) - 2) + 2);
          *igni_next_round = 0;
        }
      player1.vigor--;
      *amount_of_damage_player += igni_attack(sword_power,igni_next_round);
      enemy.hp[monster_id] -= *amount_of_damage_player;
      mvwprintw(menu,yMax-3,1,"Zadales: %d DMG",*amount_of_damage_player);
      //
      break;
    case 4:
      if(*igni_next_round == 1)
        {
          refresh();
          *amount_of_damage_player = (rand() % ((sword_power * 2) - 2) + 2);
          *igni_next_round = 0;
        }
      *amount_of_damage_player += quick_attack(sword_power);
      enemy.hp[monster_id] -= *amount_of_damage_player;
      mvwprintw(menu,yMax-3,1,"Zadales: %d DMG",*amount_of_damage_player);
      *quen_def = 1;
      player1.vigor--;
      break;
  }
}
  else
    mvwprintw(menu,yMax-3,1,"Zadales: 0 DMG",0);

  *amount_of_damage_player = 0;

  if(enemy.hp[monster_id] <= 0)
    *enemy_alive = 0;
}

void enemy_attack(int monster_id)
{
  srand( time( NULL ) );
  *amount_of_damage_enemy = rand () % enemy.damage[monster_id] * enemy.lvl[monster_id];
  player1.hp -= *amount_of_damage_enemy;
}

void write_info(int yMax, WINDOW *menu, int monster_id)
{
wattron(menu, A_UNDERLINE);
wattron(menu, A_BOLD);
mvwprintw(menu,yMax-9,1,"Informacje o graczu i przeciwniku:");
wattroff(menu, A_BOLD);
wattroff(menu, A_UNDERLINE);

wattron(menu,A_BOLD);
wattron(menu,A_UNDERLINE);
mvwprintw(menu,yMax-7,1,"Lambert:");
wattroff(menu,A_BOLD);
wattroff(menu,A_UNDERLINE);
mvwprintw(menu,yMax-6,1,"Ilosc HP: %d ",player1.hp);
mvwprintw(menu,yMax-5,1,"Moc miecza: %d",player1.sword_pow);
wattron(menu,A_BOLD);
wattron(menu,A_UNDERLINE);
mvwprintw(menu,yMax-7,23,"%s",enemy.name[monster_id]);
wattroff(menu,A_BOLD);
wattroff(menu,A_UNDERLINE);
mvwprintw(menu,yMax-6,23,"Ilosc HP: %d ",enemy.hp[monster_id]);
mvwprintw(menu,yMax-5,23,"Zadawany DMG: %d",enemy.damage[monster_id]);

wrefresh(menu);
}

void fight(int *chosen,int monster_id,int *enemy_alive, int *quen_def, int *igni_next_round)
{
  initscr();
  noecho();

  *amount_of_damage_enemy = 0;
  cheat_attempt = 0;

  int yMax, yBeg, xBeg;

  //DEKLARACJA OKNA
  WINDOW * menu = newwin(16,40,1,0);

  //POBRANIE POCZATKU OKNA I KONIEC (JEGO GRANIC)
  getbegyx(menu,yBeg,xBeg);
  yMax = getmaxy(menu);

  move(yMax+3,0);
  clrtoeol();

  //WPISY INFORMACYJNE
  //POCZATEK
  attron(A_BOLD);
  mvprintw(yBeg-1,xBeg,"Menu walki:\n");
  attroff(A_BOLD);

  attron(A_BOLD);
  mvprintw(yMax+2,xBeg,"Przypomnienie: poruszamy sie po menu strzalkami gora, dol.\n");
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
  write_info(yMax,menu,monster_id);

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


  if((*chosen == 3 || *chosen == 4) && player1.vigor == 0)
    {
    attron(A_BLINK);
    mvprintw(yMax+1,0,"Nie masz wystarczajacych punktow vigoru na ta zagrywke! Omijasz ture!");
    attroff(A_BLINK);
    refresh();
    cheat_attempt = 1;
    pause1(1.5);
    refresh();
    }



  what_chosen(chosen,monster_id,enemy_alive,menu,yMax,igni_next_round,quen_def);

  write_info(yMax,menu,monster_id);

  pause1(1.5);

  if(*quen_def != 1)
    enemy_attack(monster_id);
  else
    {
      mvprintw(yMax+3,0,"Quen ochrania cie przed uderzeniem, nie dostajesz obrazen.");
      refresh();
    }
  move(yMax+1,0);
  clrtoeol();
  if(*enemy_alive <= 0 )
    mvwprintw(menu,yMax-2,1,"Twoj przeciwnik nie zyje");
  else
   mvwprintw(menu,yMax-2,1,"Otrzymales: %d DMG",*amount_of_damage_enemy);
  wrefresh(menu);

  pause1(2.5);
  refresh();
  //write_info(yMax,menu,monster_id);


  //ZAMYKAMY OKNO
  endwin();

}

#endif
