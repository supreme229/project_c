#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <stdio.h>

char intro_story[3][100] =
{
  "Witaj w mojej grze!",
  "Twoja przygoda zaczyna sie tu w Bialym Sadzie.",
  "Wprowadzimy cie krotko do gry, podejdz do kupca i kup od niego ulepszenie miecza."
};

void print_introduction()
{
  for(int i = 0; i < 3; i++)
  {
      printf("%s ",intro_story[i]);
  }
}

#endif
