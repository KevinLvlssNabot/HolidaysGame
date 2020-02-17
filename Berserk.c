#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

// Setup Couleur
void Color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

struct Capacites_t{
    char nom[20];
    int degats;
    int defense;
    int haineNecessaire;
    int volDeVie;
};
typedef struct Capacites_t capacites;


struct Perso_t{
  char nom[20];
  int pv;
  int exp;
  int levelup;
  int niveau;
  capacites **capacites_list;
  int haine;
  int cible;
  int choixAction;
};
typedef struct Perso_t perso;

struct Zone_t{
  char nom[30];
  int salleMax;
  char salle[100][30];
};
typedef struct Zone_t zone;

struct Ennemis_t{
  char nom[20];
  int pv;
  int expDonnee;
  int max;
  int min;
  capacites **capacites_list;
  int actionM;
};
typedef struct Ennemis_t ennemis;

int main(int argc, char const *argv[]) {

//variables
int newGame;
int finPartie = 0;
int finCombat = 0;
int etage = 1;
int nbreEnnemis;
int ennemisRdm; int ennemisRdm1; int ennemisRdm2;

capacites trancher = {"Trancher", 10, 0, 0};
capacites defendre = {"Defendre", 0, 5, 0};
capacites attaquer = {"Attaquer", 5};
capacites sucer = {"Sucer le sang", 7, 0, 0, 3};


ennemis monstre1; ennemis monstre2; ennemis monstre3; ennemis monstre4; ennemis monstre5; ennemis monstre6;
ennemis engeanceM = {"Engeance-Mineure", 20, 15, 1, 0,NULL};
ennemis sangsueG = {"Sangsue", 15, 10, 1, 0,NULL};
perso pp = {"", 25, 0, 50, 1,NULL, 0};

// Liste des capacites pp
pp.capacites_list = malloc(20* sizeof(capacites*));
pp.capacites_list[0]= &trancher;
pp.capacites_list[1]= &defendre;

// Liste des capacites Ennemis
engeanceM.capacites_list = malloc(5* sizeof(capacites*));
engeanceM.capacites_list[0]= &attaquer;
engeanceM.capacites_list[1]= &defendre;
sangsueG.capacites_list = malloc(5* sizeof(capacites*));
sangsueG.capacites_list[0]= &attaquer;
sangsueG.capacites_list[1]= &sucer;


Color(6,0);
// Ecran titre
    printf(" -----------------------------------\n\n");
    printf("|              BERSERK              |\n\n");
    printf(" -----------------------------------\n\n");

// Menu principal
Sleep (3000);
Color (15,0);
printf("Pour commencer une nouvelle partie, appuyer sur 0 puis sur Entree.\n");
printf("Faites cela pour chaque action au cours de la partie. Bon voyage.\n\n");
printf("Nouvelle Partie [0] | Quitter le jeu [1]\n");
scanf("%d", &newGame);
  if (newGame == 1) {
    return 0;
  }

system("cls");
// Debut du jeu
  printf("Entrez le nom de votre heros.\n");
  scanf("%s", pp.nom);
system("cls");
  printf("Bienvenue %s.\n", pp.nom);
Sleep (2000);
  printf("Vous vous appretez a vivre une epreuve difficile, voire insurmontable.\nPlongez dans les tenebres d'un sabbat sanguinaire, serez-vous assez fort et intelligent pour en sortir indemne et obtenir votre vengeance ?\n");
  printf("Seul l'avenir nous le dira. Je vous souhaiterez bien bonne chance, mais dans ce monde, la chance n'a pas sa place.\n");

Sleep (7000);
system("cls");
// Debut ascension
Color(15,0);
while (finPartie == 0) {
   printf(" -----------------------------------\n\n");
   printf("|              ETAGE %d              |\n\n", etage);
   printf(" -----------------------------------\n\n");
  if (pp.niveau < 5) {
      printf("%s | Lvl: %d | Exp : %d / %d\n", pp.nom, pp.niveau, pp.exp, pp.levelup);
  } else {
    printf("%s | Lvl : %d | Exp : %d / %d | Haine : %d\n", pp.nom, pp.niveau, pp.exp, pp.levelup, pp.haine);
  }
Sleep (2000);
Color (4,0);
      if (etage < 10) {
            srand(time(NULL));
          int MAX = 3, MIN = 1;
          nbreEnnemis = (rand() %(MAX - MIN + 1)) + MIN;
            if (nbreEnnemis == 1) {
              pp.cible = 0;
              int MAXRDM = 1, MINRDM = 0;
                ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                if (ennemisRdm == 0) {
                    monstre1 = sangsueG;
                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                } else if (ennemisRdm == 1) {
                    monstre1 = engeanceM;
                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                }
            } else if (nbreEnnemis == 2) {
               int MAXRDM = 1, MINRDM = 0;
                ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                ennemisRdm1 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                if (ennemisRdm == 0) {
                    monstre1 = sangsueG;
                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                } else if (ennemisRdm == 1) {
                    monstre1 = engeanceM;
                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                }
                    if (ennemisRdm1 == 0) {
                        monstre2 = sangsueG;
                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                    } else if (ennemisRdm2 == 1) {
                        monstre2 = engeanceM;
                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                    }
            } else if (nbreEnnemis == 3) {
                     int MAXRDM = 1, MINRDM = 0;
                      ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                      ennemisRdm1 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                      ennemisRdm2 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                      if (ennemisRdm == 0) {
                          monstre1 = sangsueG;
                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                      } else if (ennemisRdm == 1) {
                          monstre1 = engeanceM;
                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                      }
                          if (ennemisRdm1 == 0) {
                              monstre2 = sangsueG;
                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                          } else if (ennemisRdm2 == 1) {
                              monstre2 = engeanceM;
                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                          }
                              if (ennemisRdm2 == 0) {
                                monstre3 = sangsueG;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                              } else if (ennemisRdm2 == 1) {
                                monstre3 = engeanceM;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                              }
            }
      } // accolade fin etage < 10

Color(15,0);    //Phase de combat
                while (finCombat == 0) { // Choix action pp
                  printf("\n");
                  printf("Que dois faire %s?\n\n", pp.nom);
                if (pp.niveau < 5) {
                  printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                }
                    scanf("%d\n", pp.choixAction);
                        if (pp.choixAction == 0 && nbreEnnemis == 2) {
                          printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[0]->nom);
                          printf("[0] pour %s | [1] pour %s\n", monstre1.nom, monstre2.nom);
                          scanf("%d\n", pp.cible);
                        } else if (pp.choixAction == 0 && nbreEnnemis == 3) {
                          printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[0]->nom);
                          printf("[0] pour %s | [1] pour %s | [2] pour %s\n", monstre1.nom, monstre2.nom, monstre3.nom);
                          scanf("%d\n", pp.cible);
                        }
                        // Action ennemis
                        if (nbreEnnemis == 1) {
                            monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                        } else if (nbreEnnemis == 2) {
                            monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                            monstre2.actionM = (rand() %(monstre2.max - monstre2.min + 1)) + monstre2.min;
                        } else if (nbreEnnemis == 3) {
                          monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                          monstre2.actionM = (rand() %(monstre2.max - monstre2.min + 1)) + monstre2.min;
                          monstre3.actionM = (rand() %(monstre3.max - monstre3.min + 1)) + monstre3.min;
                        }

                            // Repercussion action pp
                              if (pp.choixAction == 0) {
                                  printf("%s utilise %s.\n", pp.nom, pp.capacites_list[0]->nom);
                              } else if (pp.choixAction == 1) {
                                  printf("%s utilise %s.\n", pp.nom, pp.capacites_list[1]->nom);
                                      if (nbreEnnemis == 1) {
                                        monstre1.capacites_list->degats = monstre1.capacites_list->degats - pp.capacites_list[1]->defense;
                                      } else if (nbreEnnemis == 2) {
                                        monstre1.capacites_list->degats = monstre1.capacites_list->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list->degats = monstre2.capacites_list->degats - pp.capacites_list[1]->defense;
                                      } else if (nbreEnnemis == 3) {
                                        monstre1.capacites_list->degats = monstre1.capacites_list->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list->degats = monstre2.capacites_list->degats - pp.capacites_list[1]->defense;
                                        monstre3.capacites_list->degats = monstre3.capacites_list->degats - pp.capacites_list[1]->defense;
                                      }
                              }
          Color(4,0);                        // Repercussion action ennemis
                                    if (monstre1.actionM == 0) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[0]->nom);
                                        pp.capacites_list->degats = pp.capacites_list->degats - monstre1.capacites_list[0]->defense;
                                    } else if (monstre1.actionM == 1) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[1]->nom);
                                        pp.capacites_list->degats = pp.capacites_list->degats - monstre1.capacites_list[1]->defense;
                                    }
                                          if (monstre2.actionM == 0) {
                                              printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[0]->nom);
                                              pp.capacites_list->degats = pp.capacites_list->degats - monstre2.capacites_list[0]->defense;
                                          } else if (monstre2.actionM == 1) {
                                              printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[1]->nom);
                                              pp.capacites_list->degats = pp.capacites_list->degats - monstre2.capacites_list[1]->defense;
                                          }
                                              if (monstre3.actionM == 0) {
                                                  printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[0]->nom);
                                                  pp.capacites_list->degats = pp.capacites_list->degats - monstre3.capacites_list[0]->defense;
                                              } else if (monstre3.actionM == 1) {
                                                  printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[1]->nom);
                                                  pp.capacites_list->degats = pp.capacites_list->degats - monstre3.capacites_list[1]->defense;
                                              }

                                  // Calcul degats
                                  if (pp.choixAction == 0) {
                                      if (pp.cible == 0) {
              Color (15,0);             printf("%s perd %d PV !\n", monstre1.nom, pp.capacites_list[0]->degats);
                                        monstre1.pv = monstre1.pv - pp.capacites_list[0]->degats;
                                      } else if (pp.cible == 1) {
                                        printf("%s perd %d PV !\n", monstre2.nom, pp.capacites_list[0]->degats);
                                        monstre2.pv = monstre2.pv - pp.capacites_list[0]->degats;
                                      } else if (pp.cible == 2) {
                                        printf("%s perd %d PV !\n", monstre3.nom, pp.capacites_list[0]->degats);
                                        monstre3.pv = monstre3.pv - pp.capacites_list[0]->degats;
                                      }
                                  }
                                          if (monstre1.actionM == 0) {
                                                if (monstre1.capacites_list[0]->degats > 0) {
                                                  printf("%s perd %d PV !\n", pp.nom, monstre1.capacites_list[0]->degats);
                                                  pp.pv = pp.pv - monstre1.capacites_list[0]->degats;
                                                } else if (monstre1.capacites_list[0]->defense > 0) {
                                                  printf("%s se defend.\n", monstre1.nom);
                                                }
                                          } else if (monstre1.actionM == 1) {
                                            if (monstre1.capacites_list[1]->degats > 0) {
                                              printf("%s perd %d PV !\n", pp.nom, monstre1.capacites_list[1]->degats);
                                              pp.pv = pp.pv - monstre1.capacites_list[1]->degats;
                                            } else if (monstre1.capacites_list[1]->defense > 0) {
                                              printf("%s se defend.\n", monstre1.nom);
                                            }
                                          }
                                                    if (monstre2.actionM == 0) {
                                                          if (monstre2.capacites_list[0]->degats > 0) {
                                                            printf("%s perd %d PV !\n", pp.nom, monstre2.capacites_list[0]->degats);
                                                            pp.pv = pp.pv - monstre2.capacites_list[0]->degats;
                                                          } else if (monstre2.capacites_list[0]->defense > 0) {
                                                            printf("%s se defend.\n", monstre2.nom);
                                                          }
                                                    } else if (monstre2.actionM == 1) {
                                                      if (monstre2.capacites_list[1]->degats > 0) {
                                                        printf("%s perd %d PV !\n", pp.nom, monstre2.capacites_list[1]->degats);
                                                        pp.pv = pp.pv - monstre2.capacites_list[1]->degats;
                                                      } else if (monstre2.capacites_list[1]->defense > 0) {
                                                        printf("%s se defend.\n", monstre2.nom);
                                                      }
                                                    }

                                                            if (monstre3.actionM == 0) {
                                                                  if (monstre3.capacites_list[0]->degats > 0) {
                                                                    printf("%s perd %d PV !\n", pp.nom, monstre3.capacites_list[0]->degats);
                                                                    pp.pv = pp.pv - monstre3.capacites_list[0]->degats;
                                                                  } else if (monstre3.capacites_list[0]->defense > 0) {
                                                                    printf("%s se defend.\n", monstre3.nom);
                                                                  }
                                                            } else if (monstre3.actionM == 1) {
                                                              if (monstre3.capacites_list[1]->degats > 0) {
                                                                printf("%s perd %d PV !\n", pp.nom, monstre3.capacites_list[1]->degats);
                                                                pp.pv = pp.pv - monstre3.capacites_list[1]->degats;
                                                              } else if (monstre3.capacites_list[1]->defense > 0) {
                                                                printf("%s se defend.\n", monstre3.nom);
                                                              }
                                                            }

                                        // Condition de victoire/défaite
                                        if (pp.pv <= 0) {
                                          printf("Les demons ont eu raison de vous. La vengeance attendra.\n");
                                          printf("GAME OVER\n");
                                          finCombat = 1;
                                        }
                                            

                } // Accolade fin combat


 }



  return 0;
} // accolade fin de programme
