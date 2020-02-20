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
    int degatsBase;
    int defense;
    int haineNecessaire;
    int volDeVie;
};
typedef struct Capacites_t capacites;


struct Perso_t{
  char nom[20];
  int pv;
  int pvMax;
  int exp;
  int levelup;
  int niveau;
  capacites **capacites_list;
  int haine;
  int statut;
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
  int pvMax;
  int expDonnee;
  int max;
  int min;
  capacites **capacites_list;
  int statut;
  int index;
  int actionM;
};
typedef struct Ennemis_t ennemis;

int main(int argc, char const *argv[]) {

//variables
int newGame;
int finPartie = 0;
int finCombat = 0;
int etage = 21;
int choixDirection;
int nbreEnnemis;
int ennemisRdm; int ennemisRdm1; int ennemisRdm2;
int MAXRDM; int MINRDM;

capacites trancher = {"Trancher", 15, 15, 0, 0};
capacites defendre = {"Defendre", 0, 0, 5, 0};
capacites attaquer = {"Attaquer", 5, 5};
capacites sucer = {"Sucer le sang", 3, 3, 0, 0, 3};
capacites counter = {"Contre-Attaque"};
capacites morsure = {"Morsure", 10, 10, 0, 0};
capacites aboiement = {"Aboiement"};
capacites coudepoing = {"Coup de Poing", 3, 3, 0, 10};
capacites appel = {"Appel de l'ombre", 0, 0, 0, 0};
capacites frappe = {"Frappe", 15, 15, 0, 0};
capacites soin = {"Soin"};

ennemis monstre1; ennemis monstre2; ennemis monstre3; ennemis monstre4; ennemis monstre5; ennemis monstre6;
ennemis engeanceM = {"Engeance-Mineure", 20, 20, 15, 1, 0,NULL, 0, 1};
ennemis sangsueG = {"Sangsue", 15, 15, 10, 1, 0,NULL, 0, 2};
ennemis apotre1 = {"Apotroph", 60, 60, 30, 2, 0, NULL, 0, 3};
ennemis chien = {"Chien Possede", 25, 25, 15, 1, 0, NULL, 0, 4};
ennemis apotre2 = {"L'invocant", 70, 70, 40, 1, 0, NULL, 0, 5};
ennemis invocation = {"Invocation", 10, 10, 0, 0, 0, NULL, 0, 6};
perso pp = {"", 1135, 1135, 0, 50, 1, NULL, 0, 0};


// Liste des capacites pp
pp.capacites_list = malloc(20* sizeof(capacites*));
pp.capacites_list[0]= &trancher;
pp.capacites_list[1]= &defendre;
pp.capacites_list[2]= &coudepoing;

// Liste des capacites Ennemis
engeanceM.capacites_list = malloc(5* sizeof(capacites*));
engeanceM.capacites_list[0]= &attaquer;
engeanceM.capacites_list[1]= &defendre;
sangsueG.capacites_list = malloc(5* sizeof(capacites*));
sangsueG.capacites_list[0]= &attaquer;
sangsueG.capacites_list[1]= &sucer;
apotre1.capacites_list = malloc(5* sizeof(capacites*));
apotre1.capacites_list[0]= &attaquer;
apotre1.capacites_list[1]= &defendre;
apotre1.capacites_list[2]= &counter;
chien.capacites_list = malloc(5* sizeof(capacites*));
chien.capacites_list[0]= &morsure;
chien.capacites_list[1]= &aboiement;
apotre2.capacites_list = malloc(5* sizeof(capacites*));
apotre2.capacites_list[0]= &frappe;
apotre2.capacites_list[1]= &appel;
invocation.capacites_list = malloc(2* sizeof(capacites*));
invocation.capacites_list[0]= &soin;

int repos = pp.pvMax*0.5;

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
  printf("Seul l'avenir nous le dira. Je vous souhaiterai bien bonne chance, mais dans ce monde, la chance n'a pas sa place.\n");

Sleep (12000);
system("cls");
// Debut ascension
Color(15,0);
while (finPartie == 0) {

  // Gestion haine
    if (pp.haine >= 10 && pp.haine < 20) {
        pp.capacites_list[0]->degatsBase = 15 *1.10;
        pp.capacites_list[2]->degatsBase = 3 *1.10;
    } else if (pp.haine >= 20 && pp.haine < 30) {
        pp.capacites_list[0]->degatsBase = 15 *1.20;
        pp.capacites_list[2]->degatsBase = 3 *1.20;
    } else if (pp.haine >= 30 && pp.haine < 40) {
        pp.capacites_list[0]->degatsBase = 15 *1.30;
        pp.capacites_list[2]->degatsBase = 3 *1.30;
    } else if (pp.haine >= 40 && pp.haine < 50) {
        pp.capacites_list[0]->degatsBase = 15 *1.40;
        pp.capacites_list[2]->degatsBase = 3 *1.40;
    } else if (pp.haine >= 50 && pp.haine < 60) {
        pp.capacites_list[0]->degatsBase = 15 *1.50;
        pp.capacites_list[2]->degatsBase = 3 *1.50;
    } else if (pp.haine >= 60 && pp.haine < 70) {
        pp.capacites_list[0]->degatsBase = 15 *1.60;
        pp.capacites_list[2]->degatsBase = 3 *1.60;
    } else if (pp.haine >= 70 && pp.haine < 80) {
        pp.capacites_list[0]->degatsBase = 15 *1.70;
        pp.capacites_list[2]->degatsBase = 3 *1.70;
    } else if (pp.haine >= 80 && pp.haine < 90) {
        pp.capacites_list[0]->degatsBase = 15 *1.80;
        pp.capacites_list[2]->degatsBase = 3 *1.80;
    } else if (pp.haine >= 90 && pp.haine < 100) {
        pp.capacites_list[0]->degatsBase = 15 *1.90;
        pp.capacites_list[2]->degatsBase = 3 *1.90;
    } else if (pp.haine == 100) {
        pp.capacites_list[0]->degatsBase = 15 *2;
        pp.capacites_list[2]->degatsBase = 3 *2;
    }



  finCombat = 0;
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
               MAXRDM = 1; MINRDM = 0;
                ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                if (ennemisRdm == 0) {
                    monstre1 = sangsueG;
                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                } else if (ennemisRdm == 1) {
                    monstre1 = engeanceM;
                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                }
            } else if (nbreEnnemis == 2) {
              MAXRDM = 1; MINRDM = 0;
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
                    } else if (ennemisRdm1 == 1) {
                        monstre2 = engeanceM;
                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                    }
            } else if (nbreEnnemis == 3) {
                     MAXRDM = 1; MINRDM = 0;
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
                          } else if (ennemisRdm1 == 1) {
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
                else if (etage == 10) {
                      finCombat = 1;
Color(15,0);          printf("Un lieu de repit, en ces terres souillees. Profitez en pour vous reposer.\n");
                      printf("Que souhaitez-vous faire ?\n\n");
                      printf("Se reposer [0], Partir [1]\n");
                      scanf("%d", &choixDirection);
                          if (choixDirection == 0) {
                              printf("Vous decidez de faire une pause, en ne fermant qu'un oeil, evidemment.\n");
                              printf("Vous recuperez %d PV !\n", repos);
                              pp.pv = pp.pv + repos;
                              pp.haine = 0;
                                  if (pp.pv > pp.pvMax) {
                                      pp.pv = pp.pvMax;
                                  }
                              while (choixDirection != 1) {
                                printf("Que souhaitez-vous faire ?\n\n");
                                printf("Partir [1]\n");
                                scanf("%d", &choixDirection);
                                  if (choixDirection == 1) {
                                      printf("Vous vous enfoncez plus profondemment, au coeur des tenebres.\n");
                                      etage++;
                                  }
                              }
                          } else if (choixDirection == 1) {
                              printf("Vous vous enfoncez plus profondemment, au creux des tenebres.\n");
                              etage++;
                          }
                  } // accolade fin etage 10
                    else if (etage == 11) {
Color(4,0);             printf("Vous ressentez une presence, une aura plus forte.\n");
                        nbreEnnemis = 1;
                        monstre1 = apotre1;
                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                    } // accolade fin etage 11
                      else if (etage > 11 && etage < 20) {
                        srand(time(NULL));
                      int MAX = 3, MIN = 1;
                      nbreEnnemis = (rand() %(MAX - MIN + 1)) + MIN;
                        if (nbreEnnemis == 1) {
                          pp.cible = 0;
                           MAXRDM = 2; MINRDM = 0;
                            ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                            if (ennemisRdm == 0) {
                                monstre1 = sangsueG;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                            } else if (ennemisRdm == 1) {
                                monstre1 = engeanceM;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                            } else if (ennemisRdm == 2) {
                                monstre1 = chien;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                            }
                        } else if (nbreEnnemis == 2) {
                            MAXRDM = 2; MINRDM = 0;
                            ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                            ennemisRdm1 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                            if (ennemisRdm == 0) {
                                monstre1 = sangsueG;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                            } else if (ennemisRdm == 1) {
                                monstre1 = engeanceM;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                            } else if (ennemisRdm == 2) {
                                monstre1 = chien;
                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                            }
                                if (ennemisRdm1 == 0) {
                                    monstre2 = sangsueG;
                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                } else if (ennemisRdm1 == 1) {
                                    monstre2 = engeanceM;
                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                } else if (ennemisRdm1 == 2) {
                                    monstre2 = chien;
                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                }
                        } else if (nbreEnnemis == 3) {
                                  MAXRDM = 2; MINRDM = 0;
                                  ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                  ennemisRdm1 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                  ennemisRdm2 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                  if (ennemisRdm == 0) {
                                      monstre1 = sangsueG;
                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                  } else if (ennemisRdm == 1) {
                                      monstre1 = engeanceM;
                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                  } else if (ennemisRdm == 2) {
                                      monstre1 = chien;
                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                  }
                                      if (ennemisRdm1 == 0) {
                                          monstre2 = sangsueG;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                      } else if (ennemisRdm1 == 1) {
                                          monstre2 = engeanceM;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                      } else if (ennemisRdm1 == 2) {
                                          monstre1 = chien;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                      }
                                          if (ennemisRdm2 == 0) {
                                            monstre3 = sangsueG;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                          } else if (ennemisRdm2 == 1) {
                                            monstre3 = engeanceM;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                          } else if (ennemisRdm2 == 2) {
                                              monstre1 = chien;
                                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                          }
                        }
                      } // accolade fin etage < 20
                        else if (etage == 20) {
                          finCombat = 1;
Color(15,0);                printf("Un lieu de repit, en ces terres souillees. Profitez en pour vous reposer.\n\n");
                            printf("Vous vous demandez, essoufle, la raison qui vous a pousse a revenir dans cet enfer ?\n");
                            printf("Demandez plutot a tout vos compagnons, dont l'ame erre en ces lieux. Eux, qui n'ont pas eu la chance de s'en sortir, massacres par des creatures que les cauchemars ne pourraient creer.\n");
                            printf("Demandez a celui, qui vous a offert en sacrifice pour son reve personnel, mais vous n'etes pas venu pour parler, n'est-ce pas ?\n");
                              printf("Que souhaitez-vous faire ?\n\n");
                              printf("Se reposer [0], Partir [1]\n");
                              scanf("%d", &choixDirection);
                                  if (choixDirection == 0) {
                                      printf("Vous decidez de faire une pause, en ne fermant qu'un oeil, evidemment.\n");
                                      printf("Vous recuperez %d PV !\n", repos);
                                      pp.pv = pp.pv + repos;
                                      pp.haine = 0;
                                          if (pp.pv > pp.pvMax) {
                                              pp.pv = pp.pvMax;
                                          }
                                      while (choixDirection != 1) {
                                        printf("Que souhaitez-vous faire ?\n\n");
                                        printf("Partir [1]\n");
                                        scanf("%d", &choixDirection);
                                          if (choixDirection == 1) {
                                              printf("Vous vous enfoncez plus profondemment, au coeur des tenebres.\n");
                                              etage++;
                                              printf("En partant, vous tombez sur une besace, elle pourra contenir des objets, utile je l'espere.\n");
                                          }
                                      }
                                  } else if (choixDirection == 1) {
                                      printf("Vous vous enfoncez plus profondemment, au creux des tenebres.\n");
                                      etage++;
                                      printf("En partant, vous tombez sur une besace, elle pourra contenir des objets, utile je l'espere.\n");
                                  }
                        } // accolade fin etage 20
                          else if (etage == 21) {
Color(4,0);                    printf("Vous ressentez une presence, une aura plus forte.\n");
                               nbreEnnemis = 1;
                               monstre1 = apotre2;
                               printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                          } // accolade fin etage 21


Color(15,0);    //Phase de combat
                while (finCombat == 0) { // Choix action pp
Color(15,0);      printf("\n");
                  printf("Que dois faire %s?\n\n", pp.nom);
                if (pp.niveau < 5) {
                  printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                } else if (pp.niveau >= 5) {
                    if (pp.haine < coudepoing.haineNecessaire) {
                      printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                    } else if (pp.haine >= coudepoing.haineNecessaire) {
                      printf("%s[0] | %s[1] | %s[2]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom);
                    }
                  }
                    scanf("%d", &pp.choixAction);
                        if ((pp.choixAction == 0 || pp.choixAction == 2) && (nbreEnnemis == 2)) {
                          printf("Sur quel ennemi souhaitez-vous utiliser %s ?\n", pp.capacites_list[0]->nom);
                          printf("[0] pour %s | [1] pour %s\n", monstre1.nom, monstre2.nom);
                          scanf("%d", &pp.cible);
                        } else if ((pp.choixAction == 0 || pp.choixAction == 2) && nbreEnnemis == 3) {
                          printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[0]->nom);
                          printf("[0] pour %s | [1] pour %s | [2] pour %s ?\n", monstre1.nom, monstre2.nom, monstre3.nom);
                          scanf("%d", &pp.cible);
                        }
                          if (pp.choixAction == 2 && pp.haine < 10) {
                              printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1]\n", pp.capacites_list[0], pp.capacites_list[1]);
                              scanf("%d", pp.choixAction);
                          }

                        // Action ennemis
                        if (nbreEnnemis == 1 && monstre1.pv > 0 && monstre1.statut == 0) {
                          srand(time(NULL));
                            monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                        } else if (nbreEnnemis == 2) {
                              if (monstre1.pv > 0 && monstre1.statut == 0){
                                srand(time(NULL));
                                monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                          }   if (monstre2.pv > 0 && monstre2.statut == 0){
                            srand(time(NULL));
                            monstre2.actionM = (rand() %(monstre2.max - monstre2.min + 1)) + monstre2.min;
                          }
                        } else if (nbreEnnemis == 3) {
                            if (monstre1.pv > 0 && monstre1.statut == 0){
                              srand(time(NULL));
                              monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                          } if (monstre2.pv > 0 && monstre2.statut == 0){
                              srand(time(NULL));
                              monstre2.actionM = (rand() %(monstre2.max - monstre2.min + 1)) + monstre2.min;
                          } if (monstre3.pv > 0 && monstre3.statut == 0){
                              srand(time(NULL));
                              monstre3.actionM = (rand() %(monstre3.max - monstre3.min + 1)) + monstre3.min;
                          }
                        }

                            // Repercussion action pp
                              if (pp.choixAction == 0) {
                                  printf("%s utilise %s.\n", pp.nom, pp.capacites_list[0]->nom);
                              } else if (pp.choixAction == 1) {
                                  printf("%s utilise %s.\n", pp.nom, pp.capacites_list[1]->nom);
                                      if (nbreEnnemis == 1) {
                                        monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        if (monstre1.max >= 2) {
                                          monstre1.capacites_list[2]->degats = monstre1.capacites_list[2]->degats - pp.capacites_list[1]->defense;
                                        }
                                      } else if (nbreEnnemis == 2) {
                                        monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                      } else if (nbreEnnemis == 3) {
                                        monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        monstre3.capacites_list[0]->degats = monstre3.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre3.capacites_list[1]->degats = monstre3.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                      }
                              } else if (pp.choixAction == 2) {
                                printf("%s utilise %s.\n", pp.nom, pp.capacites_list[2]->nom);
                                pp.haine = pp.haine - pp.capacites_list[2]->haineNecessaire;
                              }
          Color(4,0);                        // Repercussion action ennemis
                                    if (monstre1.actionM == 0 && monstre1.pv > 0 && monstre1.statut == 0) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[0]->nom);
                                          if (pp.cible == 0) {
                                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre1.capacites_list[0]->defense;
                                          }
                                    } else if (monstre1.actionM == 1 && monstre1.pv > 0 && monstre1.statut == 0) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[1]->nom);
                                        if (pp.cible == 0) {
                                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre1.capacites_list[1]->defense;
                                        }
                                    } else if (monstre1.actionM == 2 && monstre1.pv > 0 && monstre1.statut == 0) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[2]->nom);
                                        if (pp.cible == 0) {
                                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre1.capacites_list[2]->defense;
                                              if (pp.choixAction == 0) {
                                                  monstre1.capacites_list[2]->degats = pp.capacites_list[0]->degats;
                                              }
                                        }
                                    }
                                        if (nbreEnnemis >= 2){
                                          if (monstre2.actionM == 0 && monstre2.pv > 0 && monstre2.statut == 0) {
                                              printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[0]->nom);
                                              if (pp.cible == 1) {
                                                pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre2.capacites_list[0]->defense;
                                              }
                                          } else if (monstre2.actionM == 1 && monstre2.pv > 0 && monstre2.statut == 0) {
                                              printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[1]->nom);
                                              if (pp.cible == 1) {
                                                pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre2.capacites_list[1]->defense;
                                              }
                                          }
                                        }
                                            if (nbreEnnemis >= 3){
                                              if (monstre3.actionM == 0 && monstre3.pv > 0 && monstre3.statut == 0) {
                                                  printf("%s utilise %s.\n", monstre3.nom, monstre3.capacites_list[0]->nom);
                                                    if (pp.cible == 2) {
                                                      pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre3.capacites_list[0]->defense;
                                                    }
                                              } else if (monstre3.actionM == 1 && monstre3.pv > 0 && monstre3.statut == 0) {
                                                  printf("%s utilise %s.\n", monstre3.nom, monstre3.capacites_list[1]->nom);
                                                    if (pp.cible == 2) {
                                                      pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre3.capacites_list[1]->defense;
                                                    }
                                              }
                                          }

                      // Repercussion moves spe.
                      if (monstre1.actionM == 1){
                        if (monstre1.index == 4){ // chien
                          printf("%s augmente ses degats.\n", monstre1.nom);
                          monstre1.capacites_list[0]->degatsBase = monstre1.capacites_list[0]->degatsBase*1.5;
                        } else if (monstre1.index == 5) { // apotre2
                          printf("%s invoque une creature !\n", monstre1.nom);
                            if (nbreEnnemis == 1) {
                              nbreEnnemis = 2;
                              monstre2 = invocation;
                            } else if (nbreEnnemis == 2){
                              nbreEnnemis = 3;
                              monstre3 = invocation;
                            }
                        }
                      }
                          // Soin invocation
                      if (monstre2.actionM == 0) {
                        if (monstre2.index == 6) {
                          printf("%s soigne ses allies !\n", monstre2.nom);
                            if (nbreEnnemis == 2) {
                                if (monstre1.pv > 0){
                              monstre1.pv = monstre1.pv + 8;
                                    }
                                if (monstre2.pv > 0){
                              monstre2.pv = monstre2.pv + 8;
                                    }
                                if (monstre1.pv > monstre1.pvMax) {
                                  monstre1.pv = monstre1.pvMax;
                                }
                                if (monstre2.pv > monstre2.pvMax) {
                                  monstre2.pv = monstre2.pvMax;
                                }
                            } else if (nbreEnnemis == 3) {
                                if (monstre1.pv > 0){
                              monstre1.pv = monstre1.pv + 8;
                                    }
                                if (monstre2.pv > 0){
                              monstre2.pv = monstre2.pv + 8;
                                    }
                                if (monstre3.pv > 0){
                              monstre3.pv = monstre3.pv + 8;
                                    }
                                if (monstre1.pv > monstre1.pvMax) {
                                  monstre1.pv = monstre1.pvMax;
                                }
                                if (monstre2.pv > monstre2.pvMax) {
                                  monstre2.pv = monstre2.pvMax;
                                }
                                if (monstre3.pv > monstre3.pvMax) {
                                  monstre3.pv = monstre3.pvMax;
                                }
                            }
                        }
                      }

                      if (monstre2.actionM == 1) {
                        if (monstre2.index == 4){
                          printf("%s augmente ses degats.\n", monstre1.nom);
                          monstre2.capacites_list[0]->degatsBase = monstre2.capacites_list[0]->degatsBase*1.5;
                        }
                      }
                      if (monstre3.actionM == 1) {
                        if (monstre3.index == 4){
                          printf("%s augmente ses degats.\n", monstre1.nom);
                          monstre3.capacites_list[0]->degatsBase = monstre2.capacites_list[0]->degatsBase*1.5;
                        }
                      }


              // Specificite invocation
                if (monstre2.index == 6) {
                  if (monstre2.pv <= 0) {
                      if (monstre3.pv > 0) {
                        monstre2 = monstre3;
                        nbreEnnemis = 2;
                      }
                  }
                }
                  if (monstre3.index == 6) {
                    if (monstre3.pv <= 0) {
                          nbreEnnemis = 2;
                    }
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
                                    if (pp.choixAction == 2) {
                                        if (pp.cible == 0) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre1.nom, pp.capacites_list[2]->degats);
                                          monstre1.pv = monstre1.pv - pp.capacites_list[2]->degats;
                                          monstre1.statut = 1;
                                        } else if (pp.cible == 1) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre2.nom, pp.capacites_list[0]->degats);
                                          monstre2.pv = monstre2.pv - pp.capacites_list[0]->degats;
                                          monstre2.statut = 1;
                                        } else if (pp.cible == 2) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre3.nom, pp.capacites_list[0]->degats);
                                          monstre3.pv = monstre3.pv - pp.capacites_list[0]->degats;
                                          monstre3.statut = 1;
                                        }
                                    }

                                          if (monstre1.statut == 0){
    Color (4,0);                           if (monstre1.actionM == 0 && monstre1.pv > 0) {
                                                if (monstre1.capacites_list[0]->degats > 0) {
                                                  printf("%s perd %d PV !\n", pp.nom, monstre1.capacites_list[0]->degats);
                                                  pp.pv = pp.pv - monstre1.capacites_list[0]->degats;
                                                } else if (monstre1.capacites_list[0]->defense > 0) {
                                                  printf("%s se defend.\n", monstre1.nom);
                                                }
                                          } else if (monstre1.actionM == 1 && monstre1.pv > 0) {
                                            if (monstre1.capacites_list[1]->degats > 0) {
                                              printf("%s perd %d PV !\n", pp.nom, monstre1.capacites_list[1]->degats);
                                              pp.pv = pp.pv - monstre1.capacites_list[1]->degats;
                                            } else if (monstre1.capacites_list[1]->defense > 0) {
                                              printf("%s se defend.\n", monstre1.nom);
                                            }
                                          } else if (monstre1.actionM == 2 && monstre1.pv > 0 && monstre1.max >= 2) {
                                                if (pp.choixAction == 0) {
                                                  printf("%s renvoie %d degats !\n", monstre1.nom, monstre1.capacites_list[2]->degats);
                                                  pp.pv = pp.pv - monstre1.capacites_list[2]->degats;
                                                } else if (pp.choixAction == 1) {
                                                    printf("Rien ne se passe.\n");
                                                }
                                          }
                                        }
                                            if (nbreEnnemis >= 2){
                                                if (monstre2.statut == 0){
                                                    if (monstre2.actionM == 0 && monstre2.pv > 0) {
                                                          if (monstre2.capacites_list[0]->degats > 0) {
                                                            printf("%s perd %d PV !\n", pp.nom, monstre2.capacites_list[0]->degats);
                                                            pp.pv = pp.pv - monstre2.capacites_list[0]->degats;
                                                          } else if (monstre2.capacites_list[0]->defense > 0) {
                                                            printf("%s se defend.\n", monstre2.nom);
                                                          }
                                                    } else if (monstre2.actionM == 1 && monstre2.pv > 0) {
                                                      if (monstre2.capacites_list[1]->degats > 0) {
                                                        printf("%s perd %d PV !\n", pp.nom, monstre2.capacites_list[1]->degats);
                                                        pp.pv = pp.pv - monstre2.capacites_list[1]->degats;
                                                      } else if (monstre2.capacites_list[1]->defense > 0) {
                                                        printf("%s se defend.\n", monstre2.nom);
                                                      }
                                                    }
                                                  }
                                                }
                                                      if (nbreEnnemis >= 3){
                                                        if (monstre3.statut == 0){
                                                            if (monstre3.actionM == 0 && monstre3.pv > 0) {
                                                                  if (monstre3.capacites_list[0]->degats > 0) {
                                                                    printf("%s perd %d PV !\n", pp.nom, monstre3.capacites_list[0]->degats);
                                                                    pp.pv = pp.pv - monstre3.capacites_list[0]->degats;
                                                                  } else if (monstre3.capacites_list[0]->defense > 0) {
                                                                    printf("%s se defend.\n", monstre3.nom);
                                                                  }
                                                            } else if (monstre3.actionM == 1 && monstre3.pv > 0) {
                                                              if (monstre3.capacites_list[1]->degats > 0) {
                                                                printf("%s perd %d PV !\n", pp.nom, monstre3.capacites_list[1]->degats);
                                                                pp.pv = pp.pv - monstre3.capacites_list[1]->degats;
                                                              } else if (monstre3.capacites_list[1]->defense > 0) {
                                                                printf("%s se defend.\n", monstre3.nom);
                                                              }
                                                            }
                                                          }
                                                        }

                                    //Vérificatio vol de vie pp
                                      if (pp.choixAction == 0 && pp.capacites_list[0]->volDeVie > 0) {
                                          pp.pv = pp.pv + pp.capacites_list[0]->volDeVie;
                                            if (pp.pv > pp.pvMax) {
                                                pp.pv = pp.pvMax;
                                            }
                                          printf("%s recupere %d PV !\n", pp.nom, pp.capacites_list[0]->volDeVie);
                                      } else if (pp.choixAction == 1 && pp.capacites_list[1]->volDeVie > 0) {
                                        pp.pv = pp.pv + pp.capacites_list[1]->volDeVie;
                                          printf("%s recupere %d PV !\n", pp.nom, pp.capacites_list[0]->volDeVie);
                                            if (pp.pv > pp.pvMax) {
                                                pp.pv = pp.pvMax;
                                            }
                                      }

                                              //Verif vol de vie ennemis
                                              if (monstre1.statut == 0){
                                                if (monstre1.actionM == 0 && monstre1.capacites_list[0]->volDeVie > 0 && monstre1.pv > 0) {
                                                  monstre1.pv = monstre1.pv + monstre1.capacites_list[0]->volDeVie;
                                                      if (monstre1.pv > monstre1.pvMax) {
                                                          monstre1.pv = monstre1.pvMax;
                                                      }
                                                  printf("%s recupere %d PV !\n", monstre1.nom, monstre1.capacites_list[0]->volDeVie);
                                                } else if (monstre1.actionM == 1 && monstre1.capacites_list[1]->volDeVie > 0 && monstre1.pv > 0) {
                                                      monstre1.pv = monstre1.pv + monstre1.capacites_list[1]->volDeVie;
                                                          if (monstre1.pv > monstre1.pvMax) {
                                                              monstre1.pv = monstre1.pvMax;
                                                          }
                                                      printf("%s recupere %d PV !\n", monstre1.nom, monstre1.capacites_list[1]->volDeVie);
                                                }
                                              }
                                                  if (monstre2.statut == 0){
                                                      if (monstre2.actionM == 0 && monstre2.capacites_list[0]->volDeVie > 0 && monstre2.pv > 0) {
                                                        monstre2.pv = monstre2.pv + monstre2.capacites_list[0]->volDeVie;
                                                            if (monstre2.pv > monstre2.pvMax) {
                                                                monstre2.pv = monstre2.pvMax;
                                                            }
                                                        printf("%s recupere %d PV !\n", monstre2.nom, monstre2.capacites_list[0]->volDeVie);
                                                      } else if (monstre2.actionM == 1 && monstre2.capacites_list[1]->volDeVie > 0 && monstre2.pv > 0) {
                                                            monstre2.pv = monstre2.pv + monstre2.capacites_list[1]->volDeVie;
                                                                if (monstre2.pv > monstre2.pvMax) {
                                                                    monstre2.pv = monstre2.pvMax;
                                                                }
                                                            printf("%s recupere %d PV !\n", monstre2.nom, monstre2.capacites_list[1]->volDeVie);
                                                      }
                                                    }
                                                        if (monstre3.statut == 0){
                                                            if (monstre3.actionM == 0 && monstre3.capacites_list[0]->volDeVie > 0 && monstre3.pv > 0) {
                                                              monstre3.pv = monstre3.pv + monstre3.capacites_list[0]->volDeVie;
                                                                  if (monstre3.pv > monstre3.pvMax) {
                                                                      monstre3.pv = monstre3.pvMax;
                                                                  }
                                                              printf("%s recupere %d PV !\n", monstre3.nom, monstre3.capacites_list[0]->volDeVie);
                                                            } else if (monstre3.actionM == 1 && monstre3.capacites_list[1]->volDeVie > 0 && monstre3.pv > 0) {
                                                                  monstre3.pv = monstre3.pv + monstre3.capacites_list[1]->volDeVie;
                                                                      if (monstre3.pv > monstre3.pvMax) {
                                                                          monstre3.pv = monstre3.pvMax;
                                                                      }
                                                                  printf("%s recupere %d PV !\n", monstre3.nom, monstre3.capacites_list[1]->volDeVie);
                                                            }
                                                          }

                                        // Condition de victoire/défaite
Color (15,0);                        if (pp.pv <= 0) {
                                          printf("Les demons ont eu raison de vous. La vengeance attendra.\n");
                                          printf("GAME OVER\n");
                                          finCombat = 1;
                                          return 0;
                                        }
                                              if (nbreEnnemis == 1) {
                                                  if (monstre1.pv <= 0) {
                                                      printf("Vous vous en sortez bien, pour cette fois.\n");
                                                      finCombat = 1;
                                                        pp.exp = pp.exp + monstre1.expDonnee;
                                                        etage++;
                                                  }
                                              } else if (nbreEnnemis == 2) {
                                                    if (monstre1.pv <= 0 && monstre2.pv <= 0) {
                                                      printf("Vous vous en sortez bien, pour cette fois.\n");
                                                      finCombat = 1;
                                                        pp.exp = pp.exp + monstre1.expDonnee + monstre2.expDonnee;
                                                        etage++;
                                                    }
                                              } else if (nbreEnnemis == 3) {
                                                    if (monstre1.pv <= 0 && monstre2.pv <= 0 && monstre3.pv <= 0) {
                                                      printf("Vous vous en sortez bien, pour cette fois.\n");
                                                      finCombat = 1;
                                                      pp.exp = pp.exp + monstre1.expDonnee + monstre2.expDonnee + monstre3.expDonnee;
                                                      etage++;
                                                    }
                                              }

                                //Calcul levelup
                                  if (pp.exp >= pp.levelup) {
                                    pp.niveau++;
                                    printf("Vous passez au niveau %d !\n", pp.niveau);
                                    pp.levelup = pp.levelup*2.5;
                                    pp.pvMax = pp.pvMax*1.2;
                                    pp.capacites_list[0]->degatsBase = pp.capacites_list[0]->degatsBase*1.2;
                                    printf("Vos PV, vos attaques et votre defense deviennent plus efficaces.\n");
                                    pp.capacites_list[1]->defense = pp.capacites_list[1]->defense*1.2;
                                    pp.exp = pp.levelup - pp.exp;
                                        if (pp.niveau == 5) {
                                            pp.capacites_list[2] = &coudepoing;
                                            printf("\nVous etes maintenant niveau %d, vous avez acces a la haine et vous pouvez utiliser %s\n", pp.niveau, coudepoing.nom);
                                            printf("La haine, qui vous anime et vous pousse a vous venger, vous permet d'infliger plus de degats et d'utiliser certaines capacites si vous en possedez suffisamment.\n");
                                            printf("Au contraire, si vous vous reposez, vous perdrez la totalite de cette haine.\n");
                                              Sleep(10000);
                                        }
                                  }




          //Remise stat à leur base
            pp.capacites_list[0]->degats = pp.capacites_list[0]->degatsBase;
            pp.capacites_list[1]->degats = pp.capacites_list[1]->degatsBase;
              if (pp.niveau >= 5) {
                pp.capacites_list[2]->degats = pp.capacites_list[2]->degatsBase;
              }
            monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degatsBase;
            monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degatsBase;
                if (monstre1.max >= 2) {
                  monstre1.capacites_list[2]->degats = monstre1.capacites_list[2]->degatsBase;
                }
            if (nbreEnnemis == 2) {
              monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degatsBase;
              monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degatsBase;
            }
            if (nbreEnnemis == 3) {
              monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degatsBase;
              monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degatsBase;
              monstre3.capacites_list[0]->degats = monstre3.capacites_list[0]->degatsBase;
              monstre3.capacites_list[1]->degats = monstre3.capacites_list[1]->degatsBase;
            }

              if (monstre1.statut == 1) {
                  monstre1.statut = 0;
              }
                if (monstre2.statut == 1) {
                    monstre2.statut = 0;
                }
                  if (monstre3.statut == 1) {
                      monstre3.statut = 0;
                  }
                                // Affichage PV
                    if (pp.niveau < 5){            printf("\n%s | PV : %d / %d", pp.nom, pp.pv, pp.pvMax);} else if (pp.niveau >= 5){printf("\n%s | PV : %d / %d | Haine : %d", pp.nom, pp.pv, pp.pvMax, pp.haine);} Color(4,0); printf("           %s | PV : %d / %d\n", monstre1.nom, monstre1.pv, monstre1.pvMax);
                                                                                                  if (nbreEnnemis > 1){printf("                                          %s | PV : %d / %d\n", monstre2.nom, monstre2.pv, monstre2.pvMax);}
                                                                                                   if (nbreEnnemis > 2){printf("                                         %s | PV : %d / %d\n", monstre3.nom, monstre3.pv, monstre3.pvMax);}
                } // Accolade fin combat

              //Gain de haine
              if (pp.niveau >= 5) {
                pp.haine = pp.haine + (5*nbreEnnemis);
                  if (pp.haine > 100) {
                    pp.haine = 100;
                  }
              }


                  // Remise PV (au cas ou)
                    monstre1.pv = monstre1.pvMax;
                      if (nbreEnnemis >= 2) {
                        monstre2.pv = monstre2.pvMax;
                      }
                      if (nbreEnnemis >= 3) {
                        monstre3.pv = monstre3.pvMax;
                      }
Sleep(5000);
system("cls");
 }



  return 0;
} // accolade fin de programme
