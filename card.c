#include "cards.h"

int main()
{
  //give_cards();
  int power1=1,power2=1,power3=1;
  int *power1_left = &power1,*power2_left = &power2, *power3_left = &power3;
  int which_option;
  int *card_option = &which_option;

  int plr_pts = 0,enm_pts = 0,boost_plr = 0,boost_enm = 0,ace_nblock = 0;

  int card_iterator = 11, *player_points = &plr_pts, *enemy_points = &enm_pts, *start_boost_plr = &boost_plr, *start_boost_enemy = &boost_enm, *ace_not_blocked = &ace_nblock;
  main_war(1,power1_left,power2_left,power3_left,card_option,card_iterator,player_points,enemy_points,start_boost_plr,start_boost_enemy,ace_not_blocked);

  while(card_iterator != -1)
  {
    main_war(2, power1_left, power2_left, power3_left, card_option, card_iterator, player_points, enemy_points, start_boost_plr, start_boost_enemy,ace_not_blocked);
    card_iterator--;
/*
    if(*start_boost_enemy == 1)
    *enemy_points = 2;
    else *enemy_points = 0;

    if(*start_boost_plr == 1)
      *player_points = 2;
    else *player_points = 0;
    */
  }

}
