#ifndef STRUCTURES_H
#define STRUCTURES_H
#define _BSD_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112

void pause1(double time)
{
  fflush(stdout);
  usleep(time * 1000000);
}

struct info{
  int id[12];
  char name[12][50];
  char price_str[12][5];
  int price[12];
  int attribute[12];
} item;

struct monster{
  int id[10];
  int reward_int[10];
  int damage[10];
  int lvl[10];
  int hp[10];
  char reward[10][5];
  char name[10][50];
} enemy;

struct players_cards{
  char card_id[12];
  char powers[3];
}player_cards, enemy_cards;

#endif
