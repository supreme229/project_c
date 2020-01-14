#include "introduction.h"
#include <stdio.h>

int main()
{
  int key;

  do
  {
      print_introduction();
      scanf("%d",&key);
  } while(key);
}
