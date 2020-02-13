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
#include "cards.h"
#include "decision.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>


int which_option_menu_town, shop_items = 4, which_option_shop, which_decision_option, shop_improvement = 0;
int *town_option = &which_option_menu_town;
int *shop_option = &which_option_shop;
int *improvement = &shop_improvement;
int *decision_option = &which_decision_option;
int id_task = 0;



void check_which_option_in_town(int *town)
{
  switch(*town)
  {
    case 1:
    print_shop_menu(shop_items,shop_option,improvement);
    break;
    case 2:
    print_current_main_task(id_task);
    break;
    case 3:
    print_stats();
    break;
  }
}

void town_sequence(int *town_option)
{
  while(*town_option != 4)
  {
    system("clear");
    print_town_menu(town_option,0);
    check_which_option_in_town(town_option);
  }
  *town_option = -1;
  clear();
}

void fight_system(int monster_id)
{
int player_alive = 2;
int which_option_fight, quen, igni_attack = 0;
int *fight_option = &which_option_fight;
int if_enemy_alive = 1;
int *enemy_alive = &if_enemy_alive;
int *quen_def = &quen;
int *igni_next_round = &igni_attack;
// TU BEDA DO ZAPAMIETANIA WARTOSCI ZYCIA ITD

int hp_to_remember = player1.hp;
int vigor_to_remember = player1.vigor;
int enemy_hp_to_remember = enemy.hp[monster_id];
int deaths = 0;

do {
    while(true)
      {
        fight(fight_option,monster_id,enemy_alive,quen_def,igni_next_round);
        if(*enemy_alive == 0)
        {
            player_alive = 1;
            clear();
            result_screen(1);
            clear();
            break;
        }
        if(player1.hp <= 0)
          {
            deaths++;
            if(deaths % 3 == 0)
              player1.hp = player1.hp_max;
            else
              player1.hp = hp_to_remember;

            enemy.hp[monster_id] = enemy_hp_to_remember;
            player1.vigor = vigor_to_remember;
            clear();
            result_screen(0);
            clear();
            break;
          }
        *quen_def = 0;

      }
    } while(player_alive != 1);

player1.vigor = vigor_to_remember;
player1.monsters_killed += 1;
clear();
system("clear");
}

void card_system(int money)
{
  //give_cards();
  int power1=1,power2=1,power3=1;
  int round_counter_plr = 0, round_counter_enm  = 0;
  int *rounds_player = &round_counter_plr, *rounds_enemy = &round_counter_enm;
  int *power1_left = &power1,*power2_left = &power2, *power3_left = &power3;
  int which_option, enemy_power = 1;
  int *card_option = &which_option;
  int *enemy_powers_used = &enemy_power;
  int plr_pts = 0,enm_pts = 0,boost_plr = 0,boost_enm = 0;

  int card_iterator = 11, *player_points = &plr_pts, *enemy_points = &enm_pts, *start_boost_plr = &boost_plr, *start_boost_enemy = &boost_enm;
  main_war(1,enemy_powers_used,power1_left,power2_left,power3_left,card_option,card_iterator,player_points,enemy_points,start_boost_plr,start_boost_enemy,rounds_player,rounds_enemy);

  while(card_iterator != -1)
  {
    main_war(2,enemy_powers_used, power1_left, power2_left, power3_left, card_option, card_iterator, player_points, enemy_points, start_boost_plr, start_boost_enemy,rounds_player,rounds_enemy);
    player_cards.card_id[card_iterator] = ' ';
    card_iterator--;
    if(*start_boost_enemy == 1)
    {
      *enemy_points = 2;
      *start_boost_enemy = 0;
    }
    else
      *enemy_points = 0;

    if(*start_boost_plr == 1)
    {
      *player_points = 2;
      *start_boost_plr = 0;
    }
    else
      *player_points = 0;
  }
  if(*rounds_player > *rounds_enemy)
  {
    clear();
    player1.money += money;
    player1.money_gained += money;
    printf("Wygrywasz gratulacje zdobywasz %d koron. \n",money);
  }
  else if(*rounds_player == *rounds_enemy)
  {
    clear();
    printf("Remisujesz rozgrywke, nic nie tracisz i nic nie zyskujesz...");
  }
  else if(*rounds_player < *rounds_enemy)
  {
    clear();
    printf("A mowili ze Lambert taki dobry w karty... Przegrywasz i tracisz %d koron.",money);
    player1.money -= money;
  }
}

int main()
{
  
  noecho();

  system("clear");

  FILE *shop_file, *enemy_info;
  shop_file = fopen("info.txt","r");
  enemy_info = fopen("list.txt","r");
  read_from_file_shop_items(shop_file);
  read_from_file_enemy_info(enemy_info);

  system("clear");
  print_introduction();
  pause1(3);
  system("clear");

  while(*town_option != 1)
  {
    system("clear");
    print_town_menu(town_option,1);
    clear();
  }
  system("clear");
  print_shop_menu(shop_items,shop_option,improvement);

  system("clear");
  town_sequence(town_option);
  print_dialogue1();
  id_task = 1;
  pause1(1.0);
  system("clear");
  print_dialogue1_2();
  pause1(1.0);
  system("clear");
  town_sequence(town_option);


  print_monster_story1();
  pause1(1.5);
  system("clear");
  print_dialogue2();
  system("clear");
  fight_system(1);
  clear();
  system("clear");
  print_dialogue3();
  refresh();
  decision(1,decision1,decision_option);
  system("clear");
  int future_help;
  if(*decision_option == 1 || *decision_option == 2)
  {
    print_dialogue3_12();
    future_help = 1;
  }
  else
  {
  print_dialogue3_3();
  future_help = 0;
}

  pause1(1.0);
  system("clear");
  print_dialogue4();
  system("clear");
  player1.money += enemy.reward_int[id_task];
  player1.money_gained += enemy.reward_int[id_task];
  id_task = 0;
  print_dialogue5();
  system("clear");
  printf("Zagrasz teraz w gre karciana z Geraltem, spokojnie ta rozgrywka jest towarzyska i nie stracisz zadnych monet ale nauczy cie grac, kazda pozniejsza gra bedzie toczyc sie o okreslona stawke.\n\n");
  pause1(1.0);
  printf("Nacisnij dowolny przycisk by kontynuowac.");
  getchar();
  system("clear");
  print_card_introduction();
  getchar();
  system("clear");

  card_system(0);
  pause1(3.5);
  print_dialogue6();
  id_task = 2;
  pause1(2.0);

  *improvement = *improvement+1;
  town_sequence(town_option);
  pause1(1.0);
  print_dialogue7();
  fight_system(2);
  player1.money += enemy.reward_int[id_task];
  player1.money_gained += enemy.reward_int[id_task];
  pause1(0.5);
  print_dialogue8();
  id_task = 0;
  town_sequence(town_option);
  pause1(0.5);
  print_dialogue9();
  int game;
  if(player1.money < 30)
    printf("Nie masz wystarczajaca ilosc monet, odmawiasz o'Dimowi a ten odchodzi.\n");
  else
    {
    printf("Masz wystarczajaca ilosc monet, czy chcesz zagrac jezeli tak nacisnij t oraz Enter jezeli nie dowolny inny przycisk i Enter.\n");
    game = getchar();
    if(game == 'T' || game == 't')
      card_system(30);
    }
  town_sequence(town_option);
  print_dialogue10();
  system("clear");
  refresh();
  decision(2,decision2,decision_option);
  if(*decision_option == 1)
    printf("Lambert pomogl babci dostal od niej 10 koron, lecz jego miecz stracil 2 pkt mocy.");
  else if(*decision_option == 2)
    printf("Lambert pomogl babci lecz ta nie byla do konca zadowolona i nie dala mu zadnych monet, za to jego miecz stracil 1 pkt mocy.");
  else
  {
    printf("Lambert nie pomogl babci a ta nie byla zadowolona i uszkodzila mu miecz, stracil 1 pkt mocy.");
    player1.sword_pow -=1;
  }
  *improvement += 1;
  pause1(3.5);
  system("clear");
  printf("Lambert zlapal ogloszenie na pobliskie utopce, czas na jakas latwiejsza walke... ale najpierw udal sie do miasta.\n");
  id_task = 3;
  pause1(3.5);
  town_sequence(town_option);
  system("clear");
  printf("Lambert udal sie na pobliskie bagna i rozpoczal walke z utopcami...\n");
  pause1(3.5);
  fight_system(3);
  printf("Lambert odebral nagrode w wysokosci 60 koron i udal sie do wsi Gajowo.\n");
  player1.money += enemy.reward_int[id_task];
  player1.money_gained += enemy.reward_int[id_task];
  id_task = 0;
  town_sequence(town_option);
  printf("Po dluzszym pobycie w Bialym Sadzie Lambert udal sie do Kaer Morhen, po drodze spotkal dziewczynke ktora widzial przy polu bitwy przy zleceniu na Ghule.\n");
  pause1(3.5);
  if(future_help == 1)
  {
    printf("Dziewczyna podziekowala za poprzednia pomoc ponownie, babcia wyzdrowiala a dziewczynka podarowala Lambertowi rune z miecza jej ojca co dodalo 1 pkt mocy mieczowi Lamberta.\n");
    pause1(3.5);
    player1.sword_pow += 1;
  }
  else
    {
      printf("Dziewczynka byla wychudzona, a w reku trzymala pojemnik z prochami, pewnie jej babci...\n");
      pause1(3.5);
    }
    player1.sword_pow += 2;
    system("clear");
    printf("W poblizu Kaer Morhen Lambert natknal sie na atakowanego przez Zgnilce mezczyzne, czy mu pomoze?\n");
    pause1(3.5);
    system("clear");
    refresh();
    decision(3,decision3,decision_option);
    if(*decision_option == 1)
    {
      id_task = 4;
      player1.reputation_points += 2;
      fight_system(4);
      player1.money += enemy.reward_int[id_task];
      player1.money_gained += enemy.reward_int[id_task];
    }
    id_task = 0;
    pause1(0.5);

    player1.sword_pow = 25;
    print_dialogue11();
    if(player1.money < 50)
      {
      printf("Nie masz wystarczajaca ilosc monet, odmawiasz Vesemirowi pyta zato Ciri chce zagrac o 30 koron.\n");
      pause1(3.5);
      if(player1.money < 30)
          {
        printf("Nie masz wystarczajacej ilosc monet, odmawiasz Ciri.\n");
        pause1(3.0);
          }
      else
          {
        printf("Masz wystarczajaca ilosc monet, czy chcesz zagrac jezeli tak nacisnij t oraz Enter jezeli nie dowolny inny przycisk i Enter.\n");
        game = getchar();
        if(game == 'T' || game == 't')
          card_system(30);
          }
      }
    else
        {
      printf("Masz wystarczajaca ilosc monet, czy chcesz zagrac jezeli tak nacisnij t oraz Enter jezeli nie dowolny inny przycisk i Enter.\n");
      game = getchar();
      if(game == 'T' || game == 't')
        card_system(50);
        }
        pause1(0.5);

        printf("Wieczorem udajesz sie do pobliskiej wsi.");
        pause1(3.5);
        system("clear");
        town_sequence(town_option);
        pause1(0.5);
        print_dialogue12();
        id_task = 5;
        fight_system(5);
        printf("Niesamowita to byla walka... Smok pokonany, ale...\n");
        pause1(3.5);
        if(player1.reputation_points >= 5)
          {
            printf("Na szczescie przezyli wszyscy... Bylo blisko.");
          }
        else if(player1.reputation_points >= 3)
        {
          printf("Przezyli wszyscy... oprocz Vesemira, zapewnimy mu godny pochowek, zasluzyl na to.");
        }
        else
        {
          printf("Wszyscy zgineli a Cirilla zniknela, Lambert sie zalamal jak do tego moglo dojsc?");
        }
        printf("Tu nastepuje koniec przygod Lamberta, wiedzmin wyjechal z Kaer Morhen by dalej zwiedzac swiat i robic co robi najlepiej... zabijac potwory.");
        id_task = 0;
        return 0;
}
