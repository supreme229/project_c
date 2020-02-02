#ifndef TEXTS_H
#define TEXTS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



char intro_story[3][100] =
{
  "Witaj w mojej grze!",
  "Twoja przygoda zaczyna sie tu w Bialym Sadzie.",
  "Wprowadzimy cie krotko do gry, podejdz do kupca i kup od niego ulepszenie miecza."
};

char dialogue1[10][125] =
{
  //DIALOG 1 START
  "Lokalny: Ej ty! Zaczekaj! Mam do ciebie sprawe.",
  ".Lambert.: O co sie rozchodzi? Nie mam czasu.",
  "Lokalny: W poblizu jakis czas temu miala miejsce bitwa i zalegly sie tam trupojady, moglbys cos z tym zrobic.",
  ".Lambert.: Ile placicie?",
  "Lokalny: 50 koron Panie, tylko prosze zrob cos z tym bo boimy sie ruszyc z domu.",
  ".Lambert.: Dobra, niedlugo wroce.",
  "Lokalny: Dzieki ci Wiedzminie!"
};

void pause3(double time)
{
  fflush(stdout);
  usleep(time * 1000000);
}

void print_introduction()
{
  for(int i = 0; i < 3; i++)
  {
      printf(ANSI_COLOR_RED "%s " ANSI_COLOR_RESET, intro_story[i]);
  }
}

void print_dialogue(char dialogue[][125],int lines)
{
  for(int i=0; i<lines;i++)
  {
    if(dialogue[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue[i]);
    else
      printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,dialogue[i]);
    pause3(2.5);
  }
}



#endif
