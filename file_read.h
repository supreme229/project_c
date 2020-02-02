#ifndef FILE_READ_H
#define FILE_READ_H

#include <string.h>

#include "structures.h"

void read_from_file_shop_items(FILE *file)
{
  file = fopen("info.txt","r");
  for(int i = 0; i < 12; i++)
  {
    int price, attr,id;
    char name[50], price_str[5];
    fscanf(file,"%s",price_str);
    fscanf(file,"%d",&id);
    fscanf(file,"%d",&price);
    fscanf(file,"%d",&attr);
    fscanf(file,"%s",name);
    strcat(item.name[i], name);
    strcat(item.name[i], " ");

    while(1)
    {
    fscanf(file,"%s",name);
    if(strcmp("aa",name) == 0)
      break;
    strcat(item.name[i], name);
    strcat(item.name[i], " ");
    }

    strcpy(item.price_str[i],price_str);
    item.id[i] = id;
    item.price[i] = price;
    item.attribute[i] = attr;
  }
}

void read_from_file_enemy_info(FILE *file)
{
  file = fopen("list.txt","r");
  for(int i = 0; i < 10; i++)
  {
    int id, reward_int, damage, hp;
    char name[50], reward[5];
    fscanf(file,"%d",&id);
    fscanf(file,"%s",reward);
    fscanf(file,"%d",&reward_int);
    fscanf(file,"%d",&hp);
    fscanf(file,"%d",&damage);
    fscanf(file,"%s",name);
    strcat(enemy.name[i], name);
    strcat(enemy.name[i], " ");

    while(1)
    {
    fscanf(file,"%s",name);
    //printf("%s ",name);
    if(strcmp("aa",name) == 0)
      break;
    strcat(enemy.name[i], name);
    strcat(enemy.name[i], " ");
    }

    strcpy(enemy.reward[i],reward);
    enemy.hp[i] = hp;
    enemy.id[i] = id;
    enemy.reward_int[i] = reward_int;
    enemy.damage[i] = damage;
    //printf("%d %d %d %s %s\n",enemy.id[i],enemy.reward_int[i],enemy.damage[i],enemy.reward[i],enemy.name[i]);
  }
}

#endif
