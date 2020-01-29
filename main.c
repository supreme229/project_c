#include "introduction.h"
#include "city_menu.h"
#include "shop_menu.h"
#include "file_read.h"
#include "structures.h"
#include "player.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

void pause2(int time)
{
  fflush(stdout);
  usleep(time * 1000000);
}

int which_option_menu_town, shop_items = 4;
int *temp = &which_option_menu_town;

void check_which_option_in_town(int *temp)
{
  switch(*temp)
  {
    case 1:
    print_shop_menu(shop_items,temp);
    case 3:
    print_stats();
  }
}

int main()
{
  system("clear");
  FILE *shop_file;
  read_from_file(shop_file);
  print_introduction();
  pause2(3);
  system("clear");

  while(*temp != 1)
  {
    system("clear");
    print_town_menu(temp,1);
    clear();
  }
  system("clear");
  print_shop_menu(shop_items,temp);
  system("clear");
  while(true)
  {
    system("clear");
    print_town_menu(temp,0);
    check_which_option_in_town(temp);
  }

  system("clear");

}
