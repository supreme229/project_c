#ifndef TEXTS_H
#define TEXTS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "structures.h"
#include "player.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



char intro_story[3][100] =
{
  "Witaj w mojej grze! ",
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

char dialogue1_2[10][125] =
{
  ".Lambert: Zajrze jeszcze do miasta moze warto sie przygotowac na te ghule."
};

char monster1_story[10][150] =
{
  "W obecnych czasach wiedzmini nie zarabiaja duzo.",
  "Bieda w Bialym Sadzie bije po oczach i Lambertowi jak i innym wiedzminom ciezko zdobyc chociaz jakiekolwiek korony.",
  "Zlecenie na ghule bylo pierwszym zleceniem Lamberta od dluzszego czasu dlatego nie chcial brac sobie za przeciwnika bardzo wymagajacego potwora."
};

char dialogue2[10][125] =
{
  ".Lambert: To chyba te miejsce bitwy o ktorym mowil lokalny, rozejrzyjmy sie.",
  "Po chwili Lambert dostrzega ghule, rozrywajace na strzepy cialo pewnego Nilfgardczyka.",
  ".Lambert: Przypomnijmy sobie jak to wygladalo, obcinac wam lby..."
};

char dialogue3[10][125] =
{
  "Niosac w worku glowe jednego z ghuli, Lambert natknal sie na placzace dziecko, postanowil przyjrzec sie sprawie.",
  ".Lambert: Czesc mala, co sie stalo? Co tu robisz? Tu jest niebezpiecznie.",
  "*Dziecko: Moj tata zginal tutaj, a ja tylko widzialam jak jego cialo zabiera jakis stwor.",
  "Powiedzialo dziecko z trudem przez placz.",
  ".Lambert: Gdzie twoj dom?",
  "*Dziecko: Blisko, lecz nie mam pieniedzy na jedzenie i leki dla mojej babci, jest jedyna osoba ktora mi zostala...",
  "Lambert musi podjac decyzje, czy chce podarowac dziecku pieniadze na jedzenie i leki, czy moze zachowac je dla siebie"
};

char decision1[3][125] =
{
  "Oddaj dziecku 30 monet",
  "Oddaj dziecku 15 monet",
  "Nie pomagaj"
};

char dialogue3_12[10][125] =
{
  ".Lambert: Masz mala wiem ze to nie duzo, ale moze pozwoli pomoc tobie i babci.",
  "*Dziecko: Naprawde? Dziekuje ci, jestes super, ratujesz nam zycie!",
  "Lambert odchodzi od dziecka, to byl naprawde dobry uczynek a mowia ze dobro wraca..."
};

char dialogue3_3[10][125] =
{
  ".Lambert: No to wierze ze sobie jakos poradzicie, bywaj.",
  "*Dziecko: Bywaj...",
  "Lambert odchodzi od zalamanego dziecka, czy postapil na pewno slusznie?"
};

char dialogue4[10][125] =
{
  "Lambert wrocil do lokalnego ktory obiecal mu zaplate za ghule.",
  ".Lambert: Sprawa zalatwiona dla dowodu ucialem jednemu leb.",
  "*Lokalny: Dziekuje ci wiedzminie. Oto twoja obiecana zaplata co do korony.",
  ".Lambert: Bywaj."
};

char dialogue5[10][125] =
{
  "Lambert po drodze do wsi Roztoczna spotkal swojego przyjaciela Geralta.",
  ".Lambert: Czy mnie oczy myla, Geralt z Rivii tu w Bialym Sadzie?",
  "*Geralt: Kope lat Lambert, gdzie zes sie podziewal?",
  ".Lambert: To chyba ciebie powinienem o tym zapytac, Vesemir nie widzial cie w Kaer Morhen od dawna...",
  "*Geralt: To przez Ciri, ona wrocila ale goni ja Dziki Gon i musze sie tym zajac.",
  ".Lambert: Czemu nie powiedziales papie Vesemirowi o tym?",
  "*Geralt: To skomplikowane, nie chce o tym teraz gadac, potrzebuje odpoczynku, nie chcesz moze zagrac w karty?",
  ".Lambert: W sumie moze warto sie rozluznic. Rozdawaj."
};


char dialogue6[10][150] =
{
  "Po rozgrywce Geralt i Lambert rozeszli sie w swoje strony. Lambert po drodze przyjal kolejne zlecenie tym razem specjalne na potwora z bagien.",
  ".Lambert: Ten potwor wyglada groznie przejrze bestiariusz w miescie i sie doposaze."
};

char dialogue7[10][150] =
{
  "Lambert dotarl na bagna, poczatkowo nie zauwazyl nic dziwnego, az tu nagle...",
  "Jakby z nikad zaczela powstawac mgla, Lambert zaczal sie dusic, musial uciekac.",
  "Szybka ucieczka pozwolila mu sie wydostac z pulapki potwora, Lambert wypil odwar z Mglaka, ktory specjalnie przygotowal i ruszyl do walki..."
};

char dialogue8[10][150] =
{
  "Odglosc rykniecia zabitego mglaka bylo slychac na kilometry... To byla ciezka walka.",
  "Lambert odebral nagrode i ruszyl do miasta zdobyl w koncu troche koron"
};

char dialogue9[10][150] =
{
  "Lambert udal sie do miejscowej karczmy by opic zwycieska walke. Podczas saczenia krasnoludzkiego spirytusu zagadal do niego pewien czlowiek.",
  "*Gaunter o'Dim: Witaj wiedzminie... Masz moze ochote na partyjke kart?",
  ".Lambert: Cos ty za jeden?",
  "*Gaunter o'Dim: Jestem Gaunter o'Dim choc mowia na mnie Pan Lusterko. To jak zagramy? O 30 koron.",
  ".Lambert: Sprawdze czy mam tyle w kieszeni"
};

char dialogue10[10][150] =
{
  "Lambert wychodzi z karczmy, zagaduje do niego jakas starsza babcia",
  "*Babcia: Witaj slonko, wygladasz na kogos kto moze mi pomoc, potrzebuje by ktos mi powybijal male szkodniki w ogrodku pomoglbys mi?",
  "Lambert musi podjac decyzje czy pomoze babci."
};

char decision2[3][125] =
{
  "Pomoz babci (twoj miecz moze sie lekko uszkodzic)",
  "Pomoz babci lecz z mniejszym zaangazowaniem",
  "Odmow pomocy"
};

char decision3[3][125] =
{
  "Pomoz mezczyznie (stocz walke) dostaniesz 10 koron",
  "Zwolaj pobliskich chlopow by pomogli mezczyznie",
  "Odjedz dalej"
};

char dialogue11[10][150] =
{
  "Lambert wszedl do zamku i przywital sie z kazdym, okazalo sie ze dotarli tez Cirilla oraz Geralt.",
  "*Vesemir: To co Lambert, jak za dawnych czasow partyjka kart, ale musimy podbic stawke 50 koron!",
  ".Lambert: Hmm..."
};

char dialogue12[10][150] =
{
  "Wracajac do Kaer Morhen slyszysz ryk, i ujawnia sie wielka luna swiatla.",
  ".Lambert: To zloty smok, musze pedzic na pomoc reszcie!",
  "Lambert dociera na miejsce, smok zdolal powalic wszystkich, lecz Lambert staje z nim w szranki, czy uratuje innych?"
};

void print_introduction()
{
  for(int i = 0; i < 3; i++)
  {
      printf(ANSI_COLOR_RED "%s \n" ANSI_COLOR_RESET, intro_story[i]);
      pause1(3.5);
  }
}

void print_dialogue1()
{
  for(int i=0; i<7;i++)
  {
    if(dialogue1[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue1[i]);
    else
      printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,dialogue1[i]);
    pause1(3.5);
  }
}

void print_dialogue1_2()
{
  for(int i=0; i<1;i++)
  {
    if(dialogue1_2[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue1_2[i]);
    else
      printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,dialogue1_2[i]);
    pause1(3.5);
  }
}

void print_monster_story1()
{
  for(int i=0; i<3;i++)
  {
    printf("%s\n",monster1_story[i]);
    pause1(3.5);
  }
}

void print_dialogue2()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue2[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue2[i]);
    else
      printf("%s\n",dialogue2[i]);
    pause1(3.5);
  }
}

void print_dialogue3()
{
  for(int i=0; i<7;i++)
  {
    if(dialogue3[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue3[i]);
    else
      if(dialogue3[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue3[i]);
    else printf("%s\n",dialogue3[i]);

    pause1(3.5);
  }
}

void print_dialogue3_12()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue3_12[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue3_12[i]);
    else
      if(dialogue3_12[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue3_12[i]);
    else printf("%s\n",dialogue3_12[i]);

    pause1(3.5);
  }
}

void print_dialogue3_3()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue3_3[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue3_3[i]);
    else
      if(dialogue3_3[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue3_3[i]);
    else printf("%s\n",dialogue3_3[i]);

    pause1(3.5);
  }
}

void print_dialogue4()
{
  for(int i=0; i<4;i++)
  {
    if(dialogue4[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue4[i]);
    else
      if(dialogue4[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue4[i]);
    else printf("%s\n",dialogue4[i]);

    pause1(3.5);
  }
}

void print_dialogue5()
{
  for(int i=0; i<8;i++)
  {
    if(dialogue5[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue5[i]);
    else
      if(dialogue5[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue5[i]);
    else printf("%s\n",dialogue5[i]);

    pause1(3.5);
  }
}

void print_dialogue6()
{
  for(int i=0; i<2;i++)
  {
    if(dialogue6[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue6[i]);
    else
      printf("%s\n",dialogue6[i]);
    pause1(3.5);
  }
}

void print_dialogue7()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue7[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue7[i]);
    else
      if(dialogue7[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue7[i]);
    else printf("%s\n",dialogue7[i]);

    pause1(3.5);
  }
}

void print_dialogue8()
{
  for(int i=0; i<2;i++)
  {
    if(dialogue8[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue8[i]);
    else
      if(dialogue8[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue8[i]);
    else printf("%s\n",dialogue8[i]);

    pause1(3.5);
  }
}

void print_dialogue9()
{
  for(int i=0; i<5;i++)
  {
    if(dialogue9[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue9[i]);
    else
      if(dialogue9[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue9[i]);
    else printf("%s\n",dialogue9[i]);

    pause1(3.5);
  }
}

void print_dialogue10()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue10[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue10[i]);
    else
      if(dialogue10[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue10[i]);
    else printf("%s\n",dialogue10[i]);

    pause1(3.5);
  }
}

void print_dialogue11()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue11[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue11[i]);
    else
      if(dialogue11[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue11[i]);
    else printf("%s\n",dialogue11[i]);

    pause1(3.5);
  }
}

void print_dialogue12()
{
  for(int i=0; i<3;i++)
  {
    if(dialogue12[i][0] == '.')
      printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dialogue12[i]);
    else
      if(dialogue12[i][0] == '*')
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,dialogue12[i]);
    else printf("%s\n",dialogue12[i]);

    pause1(3.5);
  }
}

#endif
