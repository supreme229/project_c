#include "introduction.h"
#include "city_menu.h"
#include "shop_menu.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int which_option_menu_town;
int *temp = &which_option_menu_town;

int main()
{
  system("clear");

  print_introduction();

  fflush(stdout);
  usleep(4000000);
  system("clear");

  while(*temp!=1)
  {
    system("clear");
    print_town_menu(temp,1);
  }
  system("clear");
  print_shop_menu();
  system("clear");

}
