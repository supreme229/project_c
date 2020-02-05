#include "texts.h"
#include "city_menu.h"
#include "shop_menu.h"
#include "file_read.h"
#include "structures.h"
#include "player.h"
#include "main_task.h"
#include "texts.h"
#include "fight.h"
#include "fight_result_screen.h"

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

int which_option_menu_town, shop_items = 4, which_option_shop;
int *town_option = &which_option_menu_town;
int *shop_option = &which_option_shop;
int id_task = 0;

void check_which_option_in_town(int *town)
{
  switch(*town)
  {
    case 1:
    print_shop_menu(shop_items,shop_option);
    break;
    case 2:
    print_current_main_task(id_task);
    break;
    case 3:
    print_stats();
    break;
  }
}

void fight_system()
{
int player_alive = 2;
int which_option_fight;
int *fight_option = &which_option_fight;
int if_enemy_alive = 1;
int *enemy_alive = &if_enemy_alive;

do {
    while(true)
      {
        fight(fight_option,1,enemy_alive);
        if(*enemy_alive == 0)
        {
            player_alive = 1;
            clear();
            result_screen(1);
            break;
        }
      }

    } while(player_alive != 1);
}

int main()
{
  system("clear");
  FILE *shop_file, *enemy_info;
  read_from_file_shop_items(shop_file);
  read_from_file_enemy_info(enemy_info);


  player1.sword_pow = 2;
  fight_system();

  system("clear");

  /*
  print_introduction();
  pause2(3);
  system("clear");

  while(*town_option != 1)
  {
    system("clear");
    print_town_menu(town_option,1);
    clear();
  }
  system("clear");
  print_shop_menu(shop_items,shop_option);

  system("clear");
  while(*town_option!=4)
  {
    system("clear");
    print_town_menu(town_option,0);
    check_which_option_in_town(town_option);
  }
  print_dialogue(dialogue1,7);

  */
  system("clear");

}
