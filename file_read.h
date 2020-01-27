#ifndef FILE_READ_H
#define FILE_READ_H

#include <string.h>

#include "structures.h"

void read_from_file(FILE *file)
{
  file = fopen("test.txt","r");
  for(int i = 0; i < 2; i++)
  {
    int price, attr,id;
    char name[50];
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

    item.id[i] = id;
    item.price[i] = price;
    item.attribute[i] = attr;

  }
}

#endif
