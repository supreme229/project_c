#ifndef STRUCTURES_H
#define STRUCTURES_H

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
  char reward[10][5];
  char name[10][50];
} enemy;

#endif
