#include "cards.h"

int main()
{
  //give_cards();
  int power1=0,power2=1,power3=1;
  int *power1_left = &power1,*power2_left = &power2, *power3_left = &power3;
  int which_option;
  int *card_option = &which_option;
  int card_count = 11;
  int *card_iterator = &card_count;
  main_war(1,power1_left,power2_left,power3_left,card_option,card_iterator);
  main_war(2,power1_left,power2_left,power3_left,card_option,card_iterator);
}
