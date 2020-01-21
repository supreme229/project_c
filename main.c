#include "introduction.h"
#include "city_menu.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int which_option_menu_town;
int *temp = &which_option_menu_town;

int main()
{
  print_introduction();

  fflush(stdout);
  usleep(4000000);

  system("clear");
  print_town_menu(temp);
}
