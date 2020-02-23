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
  int index;
  int cible;
  int choixAction;
};
typedef struct Perso_t perso;

struct Items_t{
  char nom[30];
  int quantiteJoueur;
  int index;
};
typedef struct Items_t items;

struct Besace_t{
  items **items_list;
};
typedef struct Besace_t besace;

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
int etage = 41;
int choixDirection;
int nbreEnnemis;
int ennemisRdm; int ennemisRdm1; int ennemisRdm2; int ennemisRdm3;
int MAXRDM; int MINRDM;
int objetRdm;
int maxObj = 100 ; int minObj = 0;
int choixObjet; int objetTotal = 0;
int nbreAllie; int choixAllie; int allieRdm;

capacites trancher = {"Trancher", 15, 15, 0, 0};
capacites defendre = {"Defendre", 0, 0, 5, 0};
capacites attaquer = {"Attaquer", 5, 5};
capacites sucer = {"Sucer le sang", 3, 3, 0, 0, 3};
capacites counter = {"Contre-Attaque"};
capacites morsure = {"Morsure", 10, 10, 0, 0};
capacites aboiement = {"Aboiement"};
capacites coudepoing = {"Coup de Poing", 3, 3, 0, 10}; // capacites lvl5
capacites appel = {"Appel de l'ombre", 0, 0, 0, 0};
capacites frappe = {"Frappe", 15, 15, 0, 0};
capacites soin = {"Soin"};
capacites balayage = {"Balayage", 10, 10, 0, 20}; // capacites lvl9
capacites lourde = {"Frappe Lourde", 30, 30, 0, 0};
capacites protection = {"Protection", 0, 0, 15, 0};
capacites lamelio = {"Lamelioration"};
capacites explosif = {"Explosif", 50, 50, 0, 40}; // capacites lvl15;
capacites estocade = {"Estocade", 30, 30, 0, 0};
capacites souvenirM = {"Souvenir", 20, 20, 0, 0};


ennemis monstre1; ennemis monstre2; ennemis monstre3; ennemis monstre4; ennemis monstre5; ennemis monstre6;
ennemis engeanceM = {"Engeance-Mineure", 20, 20, 15, 1, 0, NULL, 0, 1};
ennemis sangsueG = {"Sangsue", 15, 15, 10, 1, 0, NULL, 0, 2};
ennemis apotre1 = {"Apotroph", 120, 120, 30, 2, 0, NULL, 0, 3};
ennemis chien = {"Chien Possede", 25, 25, 15, 1, 0, NULL, 0, 4};
ennemis apotre2 = {"L'invocant", 70, 70, 40, 1, 0, NULL, 0, 5};
ennemis invocation = {"Invocation", 10, 10, 0, 0, 0, NULL, 0, 6};
ennemis protecteur = {"Protecteur", 70, 70, 35, 1, 0, NULL, 0, 7};
ennemis destructeur = {"Destructeur", 50, 50, 35, 0, 0, NULL, 0, 8};
ennemis griffith = {"Griffith", 500, 500, 200, 3, 0, NULL, 0, 9};
perso pp = {"", 100, 100, 0, 50, 1, NULL, 0, 0};
perso pipin ={"Pipin", 300, 300, 0, 0, 0, NULL, 0, 0, 1};
perso casca ={"Casca", 150, 150, 0, 0, 0, NULL, 0, 0, 2};
perso rickert ={"Rickert", 225, 225, 0, 0, 0, NULL, 0, 0, 3};
perso allie;

items poudrelfe = {"Poudre d'Elfe", 0, 1};
items souvenir = {"Souvenir", 0, 2};
items aiguisage = {"Pierre d'Aiguisage", 0, 3};
items renfort = {"Renfort", 0, 4};
items flasque = {"Flasque", 0, 5};

besace besace = {NULL};
besace.items_list = malloc(10* sizeof(capacites*));
besace.items_list[0] = &poudrelfe;
besace.items_list[1] = &souvenir;
besace.items_list[2] = &aiguisage;
besace.items_list[3] = &renfort;
besace.items_list[4] = &flasque;

// Liste des capacites pp
pp.capacites_list = malloc(10* sizeof(capacites*));
pp.capacites_list[0]= &trancher;
pp.capacites_list[1]= &defendre;
pp.capacites_list[2]= &coudepoing;
pp.capacites_list[3]= &balayage;
pp.capacites_list[4]= &explosif;
pipin.capacites_list = malloc(5* sizeof(capacites*));
pipin.capacites_list[0]= &lourde;
pipin.capacites_list[1]= &protection;
casca.capacites_list = malloc(5* sizeof(capacites*));
casca.capacites_list[0]= &attaquer;
casca.capacites_list[1]= &soin;
rickert.capacites_list = malloc(5* sizeof(capacites*));
rickert.capacites_list[0]= &attaquer;
rickert.capacites_list[1]= &lamelio;

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
destructeur.capacites_list = malloc(5* sizeof(capacites*));
destructeur.capacites_list[0]= &lourde;
protecteur.capacites_list = malloc(5* sizeof(capacites*));
protecteur.capacites_list[0]= &attaquer;
protecteur.capacites_list[1]= &protection;
griffith.capacites_list = malloc(5* sizeof(capacites*));
griffith.capacites_list[0]= &frappe;
griffith.capacites_list[1]= &protection;
griffith.capacites_list[2]= &estocade;
griffith.capacites_list[3]= &souvenirM;

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
        pp.capacites_list[3]->degatsBase = 10 *1.10;
        pp.capacites_list[4]->degatsBase = 50 *1.10;
    } else if (pp.haine >= 20 && pp.haine < 30) {
        pp.capacites_list[0]->degatsBase = 15 *1.20;
        pp.capacites_list[2]->degatsBase = 3 *1.20;
        pp.capacites_list[3]->degatsBase = 10 *1.20;
        pp.capacites_list[4]->degatsBase = 50 *1.20;
    } else if (pp.haine >= 30 && pp.haine < 40) {
        pp.capacites_list[0]->degatsBase = 15 *1.30;
        pp.capacites_list[2]->degatsBase = 3 *1.30;
        pp.capacites_list[3]->degatsBase = 10 *1.30;
        pp.capacites_list[4]->degatsBase = 50 *1.30;
    } else if (pp.haine >= 40 && pp.haine < 50) {
        pp.capacites_list[0]->degatsBase = 15 *1.40;
        pp.capacites_list[2]->degatsBase = 3 *1.40;
        pp.capacites_list[3]->degatsBase = 10 *1.40;
        pp.capacites_list[4]->degatsBase = 50 *1.40;
    } else if (pp.haine >= 50 && pp.haine < 60) {
        pp.capacites_list[0]->degatsBase = 15 *1.50;
        pp.capacites_list[2]->degatsBase = 3 *1.50;
        pp.capacites_list[3]->degatsBase = 10 *1.50;
        pp.capacites_list[4]->degatsBase = 50 *1.50;
    } else if (pp.haine >= 60 && pp.haine < 70) {
        pp.capacites_list[0]->degatsBase = 15 *1.60;
        pp.capacites_list[2]->degatsBase = 3 *1.60;
        pp.capacites_list[3]->degatsBase = 10 *1.60;
        pp.capacites_list[4]->degatsBase = 50 *1.60;
    } else if (pp.haine >= 70 && pp.haine < 80) {
        pp.capacites_list[0]->degatsBase = 15 *1.70;
        pp.capacites_list[2]->degatsBase = 3 *1.70;
        pp.capacites_list[3]->degatsBase = 10 *1.70;
        pp.capacites_list[4]->degatsBase = 50 *1.70;
    } else if (pp.haine >= 80 && pp.haine < 90) {
        pp.capacites_list[0]->degatsBase = 15 *1.80;
        pp.capacites_list[2]->degatsBase = 3 *1.80;
        pp.capacites_list[3]->degatsBase = 10 *1.80;
        pp.capacites_list[4]->degatsBase = 50 *1.80;
    } else if (pp.haine >= 90 && pp.haine < 100) {
        pp.capacites_list[0]->degatsBase = 15 *1.90;
        pp.capacites_list[2]->degatsBase = 3 *1.90;
        pp.capacites_list[3]->degatsBase = 10 *1.90;
        pp.capacites_list[4]->degatsBase = 50 *1.90;
    } else if (pp.haine == 100) {
        pp.capacites_list[0]->degatsBase = 15 *2;
        pp.capacites_list[2]->degatsBase = 3 *2;
        pp.capacites_list[3]->degatsBase = 10 *2;
        pp.capacites_list[4]->degatsBase = 50 *2;
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
                            printf("Vous vous demandez, essoufle, la raison qui vous a pousse a revenir dans cet enfer.\n");
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
                            else if (etage > 21 && etage < 30) { // accolade etage > 21
                                printf("Les ennemis, se nourrissant de la noirceur des lieux, deviennent plus forts.\n");
                                attaquer.degats = 10; attaquer.degatsBase = 10;
                                sucer.degats = 6; sucer.degatsBase = 6; sucer.volDeVie = 6;
                                morsure.degats = 20; morsure.degatsBase = 20;
                                engeanceM.pv = 40; engeanceM.pvMax = 40;
                                sangsueG.pv = 30; sangsueG.pvMax = 30;
                                chien.pv = 50; chien.pvMax = 50;
                                  srand(time(NULL));
                                  int MAX = 4, MIN = 1;
                                  nbreEnnemis = (rand() %(MAX - MIN + 1)) + MIN;
                                    if (nbreEnnemis == 1) {
                                      pp.cible = 0;
                                       MAXRDM = 4; MINRDM = 0;
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
                                        } else if (ennemisRdm == 3) {
                                            monstre1 = destructeur;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        } else if (ennemisRdm == 4){
                                            monstre1 = protecteur;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        }
                                    } else if (nbreEnnemis == 2) {
                                        MAXRDM = 4; MINRDM = 0;
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
                                        }  else if (ennemisRdm == 3) {
                                            monstre1 = destructeur;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        } else if (ennemisRdm == 4){
                                            monstre1 = protecteur;
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
                                            }  else if (ennemisRdm1 == 3) {
                                                monstre2 = destructeur;
                                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                            } else if (ennemisRdm1 == 4){
                                                monstre2 = protecteur;
                                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                            }
                                    } else if (nbreEnnemis == 3) {
                                              MAXRDM = 4; MINRDM = 0;
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
                                              }  else if (ennemisRdm == 3) {
                                                  monstre1 = destructeur;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                              } else if (ennemisRdm == 4){
                                                  monstre1 = protecteur;
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
                                                  }  else if (ennemisRdm1 == 3) {
                                                      monstre2 = destructeur;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                                  } else if (ennemisRdm1 == 4){
                                                      monstre2 = protecteur;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                                  }
                                                      if (ennemisRdm2 == 0) {
                                                        monstre3 = sangsueG;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                      } else if (ennemisRdm2 == 1) {
                                                        monstre3 = engeanceM;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                      } else if (ennemisRdm2 == 2) {
                                                          monstre3 = chien;
                                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                      }  else if (ennemisRdm2 == 3) {
                                                          monstre3 = destructeur;
                                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                      } else if (ennemisRdm2 == 4){
                                                          monstre3 = protecteur;
                                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                      }
                                    } else if (nbreEnnemis == 4) {
                                      MAXRDM = 4; MINRDM = 0;
                                      ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                      ennemisRdm1 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                      ennemisRdm2 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                      ennemisRdm3 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                      if (ennemisRdm == 0) {
                                          monstre1 = sangsueG;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                      } else if (ennemisRdm == 1) {
                                          monstre1 = engeanceM;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                      } else if (ennemisRdm == 2) {
                                          monstre1 = chien;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                      }  else if (ennemisRdm == 3) {
                                          monstre1 = destructeur;
                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                      } else if (ennemisRdm == 4){
                                          monstre1 = protecteur;
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
                                          }  else if (ennemisRdm1 == 3) {
                                              monstre2 = destructeur;
                                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                          } else if (ennemisRdm1 == 4){
                                              monstre2 = protecteur;
                                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                          }
                                              if (ennemisRdm2 == 0) {
                                                monstre3 = sangsueG;
                                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                              } else if (ennemisRdm2 == 1) {
                                                monstre3 = engeanceM;
                                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                              } else if (ennemisRdm2 == 2) {
                                                  monstre3 = chien;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                              }  else if (ennemisRdm2 == 3) {
                                                  monstre3 = destructeur;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                              } else if (ennemisRdm2 == 4){
                                                  monstre3 = protecteur;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                              }
                                                  if (ennemisRdm3 == 0) {
                                                      monstre4 = sangsueG;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                  } else if (ennemisRdm3 == 1) {
                                                      monstre4 = engeanceM;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                  } else if (ennemisRdm3 == 2) {
                                                      monstre4 = chien;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                  }  else if (ennemisRdm3 == 3) {
                                                      monstre4 = destructeur;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                  } else if (ennemisRdm3 == 4){
                                                      monstre4 = protecteur;
                                                      printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                  }
                                    }
                            } // accolade fin etage < 30
                              if (etage == 30) { // accolade 30
                                finCombat = 1;
      Color(15,0);                printf("Un lieu de repit, en ces terres souillees. Profitez en pour vous reposer.\n\n");
                                  printf("Quelle est cette voix que vous entendez ? Une voix qui vous est familiere.\n");
                                  printf("C'est un peu d'aide, qui du fond de cet enfer, vient vous pretez main forte.\n");
                                  printf("Mais prenez garde, etant des engeances de ce monde, ils perdent des forces apres chaque combat et s'ils perissent de nouveau, ils disparaitront a tout jamais.\n");
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
                                            }
                                                if (choixDirection == 1) {
                                                  printf("Choississez l'allie qui vous accompagnera vers la fin de ce periple.\n");
                                                  printf("[0]%s, le geant, fort et defensif, [1]%s, la soigneuse, [2]%s, le support-forgeron.\n", pipin.nom, casca.nom, rickert.nom);
                                                  scanf("%d", &choixAllie);
                                                  if (choixAllie == 0) {
                                                      nbreAllie = 1;
                                                      printf("Vous avez chosit %s, bon courage a vous.\n", pipin.nom);
                                                      allie = pipin;
                                                  } else if (choixAllie == 1) {
                                                    nbreAllie = 1;
                                                    printf("Vous avez chosit %s, bonnes retrouvailles.\n", casca.nom);
                                                    allie = casca;
                                                  } else if (choixAllie == 2) {
                                                    nbreAllie = 1;
                                                    printf("Vous avez chosit %s, votre epee ne peut que s'en rejouir.\n", rickert.nom);
                                                    allie = rickert;
                                                  }
                                                    printf("Vous vous enfoncez plus profondemment, au coeur des tenebres.\n");
                                                    etage++;
                                                  }
                                        } else if (choixDirection == 1) {
                                            printf("Choississez l'allie qui vous accompagnera vers la fin de ce periple.\n");
                                            printf("[0]%s, le geant, fort et defensif, [1]%s, la soigneuse, [2]%s, le support-forgeron.\n", pipin.nom, casca.nom, rickert.nom);
                                            scanf("%d", &choixAllie);
                                              if (choixAllie == 0) {
                                                  nbreAllie = 1;
                                                  printf("Vous avez chosit %s, bon courage a vous.\n", pipin.nom);
                                                  allie = pipin;
                                              } else if (choixAllie == 1) {
                                                nbreAllie = 1;
                                                printf("Vous avez chosit %s, bonnes retrouvailles.\n", casca.nom);
                                                allie = casca;
                                              } else if (choixAllie == 2) {
                                                nbreAllie = 1;
                                                printf("Vous avez chosit %s, votre epee ne peut que s'en rejouir.\n", rickert.nom);
                                                allie = rickert;
                                              }
                                            printf("Vous vous enfoncez plus profondemment, au creux des tenebres.\n");
                                            etage++;
                                        }
                              } //accolade fin 30
                                else if (etage > 30 && etage < 40) { // accolade < 40
                                  printf("Les ennemis, se nourrissant de la noirceur des lieux, deviennent encore plus forts.\n");
                                    attaquer.degats = 20; attaquer.degatsBase = 20;
                                    sucer.degats = 9; sucer.degatsBase = 9; sucer.volDeVie = 9;
                                    morsure.degats = 30; morsure.degatsBase = 30;
                                    engeanceM.pv = 80; engeanceM.pvMax = 80;
                                    sangsueG.pv = 60; sangsueG.pvMax = 60;
                                    chien.pv = 100; chien.pvMax = 100;
                                    protecteur.pv = 140; protecteur.pvMax = 140;
                                    destructeur.pv = 100; destructeur.pvMax = 100;
                                    srand(time(NULL));
                                    int MAX = 4, MIN = 1;
                                    nbreEnnemis = (rand() %(MAX - MIN + 1)) + MIN;
                                      if (nbreEnnemis == 1) {
                                        pp.cible = 0;
                                         MAXRDM = 4; MINRDM = 0;
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
                                          } else if (ennemisRdm == 3) {
                                              monstre1 = destructeur;
                                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                          } else if (ennemisRdm == 4){
                                              monstre1 = protecteur;
                                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                          }
                                      } else if (nbreEnnemis == 2) {
                                          MAXRDM = 4; MINRDM = 0;
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
                                          }  else if (ennemisRdm == 3) {
                                              monstre1 = destructeur;
                                              printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                          } else if (ennemisRdm == 4){
                                              monstre1 = protecteur;
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
                                              }  else if (ennemisRdm1 == 3) {
                                                  monstre2 = destructeur;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                              } else if (ennemisRdm1 == 4){
                                                  monstre2 = protecteur;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                              }
                                      } else if (nbreEnnemis == 3) {
                                                MAXRDM = 4; MINRDM = 0;
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
                                                }  else if (ennemisRdm == 3) {
                                                    monstre1 = destructeur;
                                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                                } else if (ennemisRdm == 4){
                                                    monstre1 = protecteur;
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
                                                    }  else if (ennemisRdm1 == 3) {
                                                        monstre2 = destructeur;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                                    } else if (ennemisRdm1 == 4){
                                                        monstre2 = protecteur;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                                    }
                                                        if (ennemisRdm2 == 0) {
                                                          monstre3 = sangsueG;
                                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                        } else if (ennemisRdm2 == 1) {
                                                          monstre3 = engeanceM;
                                                          printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                        } else if (ennemisRdm2 == 2) {
                                                            monstre3 = chien;
                                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                        }  else if (ennemisRdm2 == 3) {
                                                            monstre3 = destructeur;
                                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                        } else if (ennemisRdm2 == 4){
                                                            monstre3 = protecteur;
                                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                        }
                                      } else if (nbreEnnemis == 4) {
                                        MAXRDM = 4; MINRDM = 0;
                                        ennemisRdm = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                        ennemisRdm1 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                        ennemisRdm2 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                        ennemisRdm3 = (rand() %(MAXRDM - MINRDM + 1)) + MINRDM;
                                        if (ennemisRdm == 0) {
                                            monstre1 = sangsueG;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        } else if (ennemisRdm == 1) {
                                            monstre1 = engeanceM;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        } else if (ennemisRdm == 2) {
                                            monstre1 = chien;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        }  else if (ennemisRdm == 3) {
                                            monstre1 = destructeur;
                                            printf("%s a ete attire par votre marque sacrificielle.\n", monstre1.nom);
                                        } else if (ennemisRdm == 4){
                                            monstre1 = protecteur;
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
                                            }  else if (ennemisRdm1 == 3) {
                                                monstre2 = destructeur;
                                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                            } else if (ennemisRdm1 == 4){
                                                monstre2 = protecteur;
                                                printf("%s a ete attire par votre marque sacrificielle.\n", monstre2.nom);
                                            }
                                                if (ennemisRdm2 == 0) {
                                                  monstre3 = sangsueG;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                } else if (ennemisRdm2 == 1) {
                                                  monstre3 = engeanceM;
                                                  printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                } else if (ennemisRdm2 == 2) {
                                                    monstre3 = chien;
                                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                }  else if (ennemisRdm2 == 3) {
                                                    monstre3 = destructeur;
                                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                } else if (ennemisRdm2 == 4){
                                                    monstre3 = protecteur;
                                                    printf("%s a ete attire par votre marque sacrificielle.\n", monstre3.nom);
                                                }
                                                    if (ennemisRdm3 == 0) {
                                                        monstre4 = sangsueG;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                    } else if (ennemisRdm3 == 1) {
                                                        monstre4 = engeanceM;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                    } else if (ennemisRdm3 == 2) {
                                                        monstre4 = chien;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                    }  else if (ennemisRdm3 == 3) {
                                                        monstre4 = destructeur;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                    } else if (ennemisRdm3 == 4){
                                                        monstre4 = protecteur;
                                                        printf("%s a ete attire par votre marque sacrificielle.\n", monstre4.nom);
                                                    }
                                      }
                                } // accolade fin < 40
                                  else if (etage == 40) {
                                    finCombat = 1;
          Color(15,0);                printf("Un lieu de repit, en ces terres souillees. Profitez en pour vous reposer.\n\n");
                                      printf("Serait-ce son aura que vous ressentez ? Oui, rien ne vous est olus familier que ce sentiment.\n");
                                      printf("Melange de haine, de peur et de joie, votre vengeance touche a sa fin.\n");
                                      printf("Griffth, le faucon noir, celui qui a provoque votre quete, est tout proche.\n");
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
                                                }
                                                    if (choixDirection == 1) {
                                                        printf("Vous vous enfoncez plus profondemment, au coeur des tenebres, vers ce qui semble etre, votre derniere danse.\n");
                                                        etage++;
                                                      }
                                            } else if (choixDirection == 1) {
                                                printf("Vous vous enfoncez plus profondemment, au creux des tenebres, vers ce qui semble etre, votre derniere danse.\n");
                                                etage++;
                                            }
                                  } // accolade fin 40
                                    else if (etage == 41) { // accolade etage 41
Color(4,0);                             printf("%s, je savais que tu reviendrai, en ces lieux, qui representent pour toi le debut de ta propre guerre.\n", pp.nom);
                                        printf("J'espere que tu ne te sens pas trop seul, depuis ce jour ou j'ai accompli mon reve. Pour ma part, je n'ai aucun regret.\n");
                                        printf("Regarde-toi, cette haine qui te devore, cette haine qui t'as permi de rejoindre ces lieux, simplement pour me tuer, pour te venger.\n");
                                        printf("Tu n'as pas l'air d'etre la pour parler, mais es-tu bien pret a m'affronter ?\n");
                                        nbreEnnemis = 1;
                                        monstre1 = griffith;
                                            if (monstre1.pv <= 0) {
                                                printf("Je me doutais.. Que tu serais bien plus fort.. Que tu serais innaretable.. Comme a l'epoque.. Je te.. Felicite.. %s\n", pp.nom);
                                                printf(" ----------------------------------------------\n\n");
                                                printf("|              FELICITATIONS ! %s              |\n\n", pp.nom);
                                                printf(" ----------------------------------------------\n\n");
                                                  finPartie = 1;
                                            }
                                    } // accolade fin 41

Color(15,0);    //Phase de combat
                while (finCombat == 0) { // Choix action pp
Color(15,0);      printf("\n");
                  printf("Que dois faire %s?\n\n", pp.nom);
                if (pp.niveau < 5) {
                  printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                } else if (pp.niveau >= 5 && pp.niveau < 9) {
                    if (pp.haine < coudepoing.haineNecessaire) {
                      printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                    } else if (pp.haine >= coudepoing.haineNecessaire) {
                      printf("%s[0] | %s[1] | %s[2]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom);
                    }
                  } else if (pp.niveau >= 9 && pp.niveau < 15) {
                        if (pp.haine < balayage.haineNecessaire) {
                          printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                        } else if (pp.haine >= balayage.haineNecessaire) {
                          printf("%s[0] | %s[1] | %s[2] | %s[3]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom, pp.capacites_list[3]->nom);
                        }
                  } else if (pp.niveau > 15) {
                    if (pp.haine < balayage.haineNecessaire) {
                      printf("%s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                    } else if (pp.haine >= balayage.haineNecessaire && pp.haine < explosif.haineNecessaire) {
                      printf("%s[0] | %s[1] | %s[2] | %s[3]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom, pp.capacites_list[3]->nom);
                    } else if (pp.haine >= balayage.haineNecessaire && pp.haine < explosif.haineNecessaire) {
                      printf("%s[0] | %s[1] | %s[2] | %s[3] | %s[4]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom, pp.capacites_list[3]->nom, pp.capacites_list[4]->nom);
                    }
                  }
                    scanf("%d", &pp.choixAction);
                        if ((pp.choixAction == 0 || pp.choixAction == 2 || pp.choixAction == 4) && (nbreEnnemis == 2)) {
                          if (pp.choixAction == 0) {
                            printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[0]->nom);
                          } else if (pp.choixAction == 2) {
                            printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[2]->nom);
                          } else if (pp.choixAction == 4) {
                            printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[4]->nom);
                          }
                          printf("[0] pour %s | [1] pour %s\n", monstre1.nom, monstre2.nom);
                          scanf("%d", &pp.cible);
                        } else if ((pp.choixAction == 0 || pp.choixAction == 2 || pp.choixAction == 4) && nbreEnnemis == 3) {
                            if (pp.choixAction == 0) {
                              printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[0]->nom);
                            } else if (pp.choixAction == 2) {
                              printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[2]->nom);
                            } else if (pp.choixAction == 4) {
                              printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[4]->nom);
                            }
                          printf("[0] pour %s | [1] pour %s | [2] pour %s ?\n", monstre1.nom, monstre2.nom, monstre3.nom);
                          scanf("%d", &pp.cible);
                        } else if ((pp.choixAction == 0 || pp.choixAction == 2 || pp.choixAction == 4) && nbreEnnemis == 4) {
                            if (pp.choixAction == 0) {
                              printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[0]->nom);
                            } else if (pp.choixAction == 2) {
                              printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[2]->nom);
                            } else if (pp.choixAction == 4) {
                              printf("Sur quel ennemi souhaitez-vous utiliser %s\n", pp.capacites_list[4]->nom);
                            }
                          printf("[0] pour %s | [1] pour %s | [2] pour %s | [3] pour %s ?\n", monstre1.nom, monstre2.nom, monstre3.nom, monstre4.nom);
                          scanf("%d", &pp.cible);
                          if (pp.choixAction == 2 && pp.haine < coudepoing.haineNecessaire) {
                            printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                            while (pp.choixAction < 0 || pp.choixAction > 1) {
                              scanf("%d", &pp.choixAction);
                            }
                        }
                      }
                        if (pp.choixAction == 3 && pp.haine < balayage.haineNecessaire) {
                            if (pp.haine > coudepoing.haineNecessaire) {
                                printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1] | %[2]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom);
                                while (pp.choixAction < 0 || pp.choixAction > 2) {
                                  scanf("%d", &pp.choixAction);
                                }
                            } else if (pp.haine < coudepoing.haineNecessaire) {
                                printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                                while (pp.choixAction < 0 || pp.choixAction > 1) {
                                  scanf("%d", &pp.choixAction);
                                }
                            }
                        }
                          if (pp.choixAction == 4 && pp.haine < explosif.haineNecessaire) {
                              if (pp.haine > balayage.haineNecessaire) {
                                  printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1] | %[2] | %[3]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom, pp.capacites_list[3]->nom);
                                  while (pp.choixAction < 0 || pp.choixAction > 3) {
                                    scanf("%d", &pp.choixAction);
                                  }
                              } else if (pp.haine < balayage.haineNecessaire && pp.haine > coudepoing.haineNecessaire) {
                                  printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1] | %s[2]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom, pp.capacites_list[2]->nom);
                                  while (pp.choixAction < 0 || pp.choixAction > 2) {
                                    scanf("%d", &pp.choixAction);
                                  }
                              } else if (pp.haine < coudepoing.haineNecessaire) {
                                  printf("Vous n'etes pas suffisamment enrage pour faire cela. %s[0] | %s[1]\n", pp.capacites_list[0]->nom, pp.capacites_list[1]->nom);
                                  while (pp.choixAction < 0 || pp.choixAction > 1) {
                                    scanf("%d", &pp.choixAction);
                                  }
                              }
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
                        } else if (nbreEnnemis == 4) {
                            if (monstre1.pv > 0 && monstre1.statut == 0){
                              srand(time(NULL));
                              monstre1.actionM = (rand() %(monstre1.max - monstre1.min + 1)) + monstre1.min;
                          } if (monstre2.pv > 0 && monstre2.statut == 0){
                              srand(time(NULL));
                              monstre2.actionM = (rand() %(monstre2.max - monstre2.min + 1)) + monstre2.min;
                          } if (monstre3.pv > 0 && monstre3.statut == 0){
                              srand(time(NULL));
                              monstre3.actionM = (rand() %(monstre3.max - monstre3.min + 1)) + monstre3.min;
                          } if (monstre4.pv > 0 && monstre4.statut == 0){
                              srand(time(NULL));
                              monstre4.actionM = (rand() %(monstre4.max - monstre4.min + 1)) + monstre4.min;
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
                                      } else if (nbreEnnemis == 4) {
                                        monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        monstre3.capacites_list[0]->degats = monstre3.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre3.capacites_list[1]->degats = monstre3.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                        monstre4.capacites_list[0]->degats = monstre4.capacites_list[0]->degats - pp.capacites_list[1]->defense;
                                        monstre4.capacites_list[1]->degats = monstre4.capacites_list[1]->degats - pp.capacites_list[1]->defense;
                                      }
                              } else if (pp.choixAction == 2) {
                                printf("%s utilise %s.\n", pp.nom, pp.capacites_list[2]->nom);
                                pp.haine = pp.haine - pp.capacites_list[2]->haineNecessaire;
                              } else if (pp.choixAction == 3) {
                                printf("%s utilise %s.\n", pp.nom, pp.capacites_list[3]->nom);
                                pp.haine = pp.haine - pp.capacites_list[3]->haineNecessaire;
                              } else if (pp.choixAction == 4) {
                                printf("%s utilise %s.\n", pp.nom, pp.capacites_list[4]->nom);
                                pp.haine = pp.haine - pp.capacites_list[4]->haineNecessaire;
                              }

          Color(4,0);                        // Repercussion action ennemis
                                    if (monstre1.actionM == 0 && monstre1.pv > 0 && monstre1.statut == 0) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[0]->nom);
                                          if (pp.cible == 0) {
                                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre1.capacites_list[0]->defense;
                                            pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre1.capacites_list[0]->defense;
                                            pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre1.capacites_list[0]->defense;
                                          }
                                    } else if (monstre1.actionM == 1 && monstre1.pv > 0 && monstre1.statut == 0) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[1]->nom);
                                        if (pp.cible == 0) {
                                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre1.capacites_list[1]->defense;
                                            pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre1.capacites_list[1]->defense;
                                            pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre1.capacites_list[1]->defense;
                                        }
                                    } else if (monstre1.actionM == 2 && monstre1.pv > 0 && monstre1.statut == 0 && monstre1.index != 9) {
                                        printf("%s utilise %s.\n", monstre1.nom, monstre1.capacites_list[2]->nom);
                                        if (pp.cible == 0) {
                                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre1.capacites_list[2]->defense;
                                            pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre1.capacites_list[2]->defense;
                                            pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre1.capacites_list[2]->defense;
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
                                                pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre2.capacites_list[0]->defense;
                                                pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre2.capacites_list[0]->defense;
                                              }
                                          } else if (monstre2.actionM == 1 && monstre2.pv > 0 && monstre2.statut == 0) {
                                              printf("%s utilise %s.\n", monstre2.nom, monstre2.capacites_list[1]->nom);
                                              if (pp.cible == 1) {
                                                pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre2.capacites_list[1]->defense;
                                                pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre2.capacites_list[1]->defense;
                                                pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre2.capacites_list[1]->defense;
                                              }
                                          }
                                        }
                                            if (nbreEnnemis >= 3){
                                              if (monstre3.actionM == 0 && monstre3.pv > 0 && monstre3.statut == 0) {
                                                  printf("%s utilise %s.\n", monstre3.nom, monstre3.capacites_list[0]->nom);
                                                    if (pp.cible == 2) {
                                                      pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre3.capacites_list[0]->defense;
                                                      pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre3.capacites_list[0]->defense;
                                                      pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre3.capacites_list[0]->defense;
                                                    }
                                              } else if (monstre3.actionM == 1 && monstre3.pv > 0 && monstre3.statut == 0) {
                                                  printf("%s utilise %s.\n", monstre3.nom, monstre3.capacites_list[1]->nom);
                                                    if (pp.cible == 2) {
                                                      pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre3.capacites_list[1]->defense;
                                                      pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre3.capacites_list[1]->defense;
                                                      pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre3.capacites_list[1]->defense;
                                                    }
                                              }
                                          }
                                            if (nbreEnnemis >= 4) {
                                              if (monstre4.actionM == 0 && monstre4.pv > 0 && monstre4.statut == 0) {
                                                  printf("%s utilise %s.\n", monstre4.nom, monstre4.capacites_list[0]->nom);
                                                    if (pp.cible == 2) {
                                                      pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre4.capacites_list[0]->defense;
                                                      pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre4.capacites_list[0]->defense;
                                                      pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre4.capacites_list[0]->defense;
                                                    }
                                              } else if (monstre4.actionM == 1 && monstre4.pv > 0 && monstre4.statut == 0) {
                                                  printf("%s utilise %s.\n", monstre4.nom, monstre4.capacites_list[1]->nom);
                                                    if (pp.cible == 2) {
                                                      pp.capacites_list[0]->degats = pp.capacites_list[0]->degats - monstre4.capacites_list[1]->defense;
                                                      pp.capacites_list[2]->degats = pp.capacites_list[2]->degats - monstre4.capacites_list[1]->defense;
                                                      pp.capacites_list[3]->degats = pp.capacites_list[3]->degats - monstre4.capacites_list[1]->defense;
                                                    }
                                              }
                                            }

Color(15,0);              // gerer allies
                if (nbreAllie == 1) {
                  srand(time(NULL));
                  int allieMax = 1, allieMin = 0;
                  allieRdm = (rand() %(allieMax - allieMin + 1)) + allieMin;
                    if (allie.index == 1 || allie.index == 2 || allie.index == 3) {
                      if (allieRdm == 0) {
                        if (nbreEnnemis == 1) {
                            allie.cible == 0;
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre1.nom, allie.capacites_list[0]->degats);
                            monstre1.pv = monstre1.pv - allie.capacites_list[0]->degats;
                        } else if (nbreEnnemis == 2) {
                          srand(time(NULL));
                          allie.cible = (rand() %(1 - 0 + 1)) + 0;
                            if (allie.cible == 0) {
                              printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                              printf("%s perd %d PV !\n", monstre1.nom, allie.capacites_list[0]->degats);
                              monstre1.pv = monstre1.pv - allie.capacites_list[0]->degats;
                            } else if (allie.cible == 1) {
                              printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                              printf("%s perd %d PV !\n", monstre2.nom, allie.capacites_list[0]->degats);
                              monstre2.pv = monstre2.pv - allie.capacites_list[0]->degats;
                            }
                        } else if (nbreEnnemis == 3) {
                          srand(time(NULL));
                          allie.cible = (rand() %(2 - 0 + 1)) + 0;
                          if (allie.cible == 0) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre1.nom, allie.capacites_list[0]->degats);
                            monstre1.pv = monstre1.pv - allie.capacites_list[0]->degats;
                          } else if (allie.cible == 1) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre2.nom, allie.capacites_list[0]->degats);
                            monstre2.pv = monstre2.pv - allie.capacites_list[0]->degats;
                          } else if (allie.cible == 2) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre3.nom, allie.capacites_list[0]->degats);
                            monstre3.pv = monstre3.pv - allie.capacites_list[0]->degats;
                          }
                        } else if (nbreEnnemis == 4) {
                          srand(time(NULL));
                          allie.cible = (rand() %(3 - 0 + 1)) + 0;
                          if (allie.cible == 0) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre1.nom, allie.capacites_list[0]->degats);
                            monstre1.pv = monstre1.pv - allie.capacites_list[0]->degats;
                          } else if (allie.cible == 1) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre2.nom, allie.capacites_list[0]->degats);
                            monstre2.pv = monstre2.pv - allie.capacites_list[0]->degats;
                          } else if (allie.cible == 2) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre3.nom, allie.capacites_list[0]->degats);
                            monstre3.pv = monstre3.pv - allie.capacites_list[0]->degats;
                          } else if (allie.cible == 3) {
                            printf("%s utilise %s !\n", allie.nom, allie.capacites_list[0]->nom);
                            printf("%s perd %d PV !\n", monstre4.nom, allie.capacites_list[0]->degats);
                            monstre4.pv = monstre4.pv - allie.capacites_list[0]->degats;
                          }
                        }
                    }
                  }
                      if (allie.index == 1 && allieRdm == 1) {
                          printf("%s utilise %s\n", allie.nom, allie.capacites_list[1]->nom);
                          printf("%s vous protege avec vigueur.\n", allie.nom);
                          monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degats/1.5;
                          monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degats/1.5;
                            if (nbreEnnemis == 2) {
                              monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degats/1.5;
                              monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degats/1.5;
                            }
                            if (nbreEnnemis == 3) {
                              monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degats/1.5;
                              monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degats/1.5;
                              monstre3.capacites_list[0]->degats = monstre3.capacites_list[0]->degats/1.5;
                              monstre3.capacites_list[1]->degats = monstre3.capacites_list[1]->degats/1.5;
                            }
                            if (nbreEnnemis == 4) {
                              monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degats/1.5;
                              monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degats/1.5;
                              monstre3.capacites_list[0]->degats = monstre3.capacites_list[0]->degats/1.5;
                              monstre3.capacites_list[1]->degats = monstre3.capacites_list[1]->degats/1.5;
                              monstre4.capacites_list[0]->degats = monstre4.capacites_list[0]->degats/1.5;
                              monstre4.capacites_list[1]->degats = monstre4.capacites_list[1]->degats/1.5;
                            }
                      }
                          if (allie.index == 2 && allieRdm == 1) {
                            printf("%s vous soigne !\n", allie.nom);
                            pp.pv = pp.pv + 20;
                              if (pp.pv > pp.pvMax) {
                                  pp.pv = pp.pvMax;
                              }
                          }
                            if (allie.index == 3 && allieRdm == 1) {
                                printf("%s augmente vos degats.\n", allie.nom);
                                pp.capacites_list[0]->degats = pp.capacites_list[0]->degats*1.3;
                                pp.capacites_list[2]->degats = pp.capacites_list[2]->degats*1.3;
                                pp.capacites_list[3]->degats = pp.capacites_list[3]->degats*1.3;
                            }
              }
Color(4,0);                    // Repercussion moves spe.
                      if (monstre1.actionM == 1){
                        if (monstre1.index == 4 && monstre1.pv > 0){ // chien
                          printf("%s augmente ses degats.\n", monstre1.nom);
                          monstre1.capacites_list[0]->degatsBase = monstre1.capacites_list[0]->degatsBase*1.5;
                        } else if (monstre1.index == 5 && monstre1.pv > 0) { // apotre2
                          printf("%s invoque une creature !\n", monstre1.nom);
                            if (nbreEnnemis == 1) {
                              nbreEnnemis = 2;
                              monstre2 = invocation;
                            } else if (nbreEnnemis == 2){
                              nbreEnnemis = 3;
                              monstre3 = invocation;
                            }
                        } else if (monstre1.index == 7) {
                            printf("%s protege ses allies avec vigueur.\n", monstre1.nom);
                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats/1.5;
                            pp.capacites_list[2]->degats = pp.capacites_list[2]->degats/1.5;
                            pp.capacites_list[3]->degats = pp.capacites_list[3]->degats/1.5;
                            pp.capacites_list[4]->degats = pp.capacites_list[4]->degats/1.5;
                        } else if (monstre1.index == 9) {
                          printf("%s se protege avec vigueur.\n", monstre1.nom);
                          pp.capacites_list[0]->degats = pp.capacites_list[0]->degats /1.5;
                          pp.capacites_list[2]->degats = pp.capacites_list[2]->degats /1.5;
                          pp.capacites_list[3]->degats = pp.capacites_list[3]->degats /1.5;
                          pp.capacites_list[4]->degats = pp.capacites_list[4]->degats/1.5;
                        }
                      }

                      if (monstre1.actionM == 2) {
                          if (monstre1.index == 9) {
                              printf("%s utilise ses competences d'escrime !\n", monstre1.nom);
                                pp.pv = pp.pv - monstre1.capacites_list[2]->degats;
                          }
                      }

                      if (monstre1.actionM == 3) {
                          printf("%s utilise %s et vous montre des souvenirs douloureux !\n", monstre1.nom, monstre1.capacites_list[3]->nom);
                            if (nbreAllie == 1) {
                                printf("%s subit des degats !\n", allie.nom);
                                allie.pv = allie.pv - monstre1.capacites_list[3]->degats;
                            } else {
                                printf("%s perd des PV et voit sa haine se reduire !\n", pp.nom);
                                pp.pv = pp.pv - monstre1.capacites_list[3]->degats;
                                pp.haine = pp.haine - 10;
                            }
                      }
                          // Soin invocation
                      if (monstre2.actionM == 0) {
                        if (monstre2.index == 6 && monstre2.pv > 0) {
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
                          printf("%s augmente ses degats.\n", monstre2.nom);
                          monstre2.capacites_list[0]->degatsBase = monstre2.capacites_list[0]->degatsBase*1.5;
                        } else if (monstre2.index == 7) {
                            printf("%s protege ses allies avec vigueur.\n", monstre2.nom);
                            pp.capacites_list[0]->degats = pp.capacites_list[0]->degats /1.5;
                            pp.capacites_list[2]->degats = pp.capacites_list[2]->degats /1.5;
                            pp.capacites_list[3]->degats = pp.capacites_list[3]->degats /1.5;
                            pp.capacites_list[4]->degats = pp.capacites_list[4]->degats/1.5;
                        }
                      }
                          if (monstre3.actionM == 1) {
                            if (monstre3.index == 4){
                              printf("%s augmente ses degats.\n", monstre3.nom);
                              monstre3.capacites_list[0]->degatsBase = monstre3.capacites_list[0]->degatsBase*1.5;
                            } else if (monstre3.index == 6 && monstre3.pv > 0) {
                              printf("%s soigne ses allies !\n", monstre3.nom);
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
                            } else if (monstre3.index == 7) {
                                printf("%s protege ses allies avec vigueur.\n", monstre3.nom);
                                pp.capacites_list[0]->degats = pp.capacites_list[0]->degats /1.5;
                                pp.capacites_list[2]->degats = pp.capacites_list[2]->degats /1.5;
                                pp.capacites_list[3]->degats = pp.capacites_list[3]->degats /1.5;
                                pp.capacites_list[4]->degats = pp.capacites_list[4]->degats/1.5;
                            }
                          }
                              if (monstre4.actionM == 1) {
                                if (monstre4.index == 4){
                                  printf("%s augmente ses degats.\n", monstre4.nom);
                                  monstre4.capacites_list[0]->degatsBase = monstre4.capacites_list[0]->degatsBase*1.5;
                                } else if (monstre4.index == 7) {
                                    printf("%s protege ses allies avec vigueur.\n", monstre4.nom);
                                    pp.capacites_list[0]->degats = pp.capacites_list[0]->degats /1.5;
                                    pp.capacites_list[2]->degats = pp.capacites_list[2]->degats /1.5;
                                    pp.capacites_list[3]->degats = pp.capacites_list[3]->degats /1.5;
                                    pp.capacites_list[4]->degats = pp.capacites_list[4]->degats/1.5;
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
                                      } else if (pp.cible == 3) {
                                        printf("%s perd %d PV !\n", monstre4.nom, pp.capacites_list[0]->degats);
                                        monstre4.pv = monstre4.pv - pp.capacites_list[0]->degats;
                                      }
                                  }
                                    if (pp.choixAction == 2) {
                                        if (pp.cible == 0 && monstre1.index != 9) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre1.nom, pp.capacites_list[2]->degats);
                                          monstre1.pv = monstre1.pv - pp.capacites_list[2]->degats;
                                          monstre1.statut = 1;
                                        } else if (pp.cible == 1) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre2.nom, pp.capacites_list[2]->degats);
                                          monstre2.pv = monstre2.pv - pp.capacites_list[2]->degats;
                                          monstre2.statut = 1;
                                        } else if (pp.cible == 2) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre3.nom, pp.capacites_list[2]->degats);
                                          monstre3.pv = monstre3.pv - pp.capacites_list[2]->degats;
                                          monstre3.statut = 1;
                                        } else if (pp.cible == 3) {
                                          printf("%s perd %d PV et se retrouve paralyse !\n", monstre4.nom, pp.capacites_list[2]->degats);
                                          monstre4.pv = monstre4.pv - pp.capacites_list[2]->degats;
                                          monstre4.statut = 1;
                                        }
                                    }
                                      if (pp.choixAction == 3) {
                                          printf("%s perd %d PV !\n", monstre1.nom, pp.capacites_list[3]->degats);
                                          monstre1.pv = monstre1.pv - pp.capacites_list[3]->degats;
                                            if (nbreEnnemis == 2) {
                                              printf("%s perd %d PV !\n", monstre2.nom, pp.capacites_list[3]->degats);
                                              monstre2.pv = monstre2.pv - pp.capacites_list[3]->degats;
                                            } else if (nbreEnnemis == 3) {
                                              printf("%s perd %d PV !\n", monstre2.nom, pp.capacites_list[3]->degats);
                                              monstre2.pv = monstre2.pv - pp.capacites_list[3]->degats;
                                              printf("%s perd %d PV !\n", monstre3.nom, pp.capacites_list[3]->degats);
                                              monstre3.pv = monstre3.pv - pp.capacites_list[3]->degats;
                                            } else if (nbreEnnemis == 4) {
                                              printf("%s perd %d PV !\n", monstre2.nom, pp.capacites_list[3]->degats);
                                              monstre2.pv = monstre2.pv - pp.capacites_list[3]->degats;
                                              printf("%s perd %d PV !\n", monstre3.nom, pp.capacites_list[3]->degats);
                                              monstre3.pv = monstre3.pv - pp.capacites_list[3]->degats;
                                              printf("%s perd %d PV !\n", monstre4.nom, pp.capacites_list[3]->degats);
                                              monstre4.pv = monstre4.pv - pp.capacites_list[3]->degats;
                                            }
                                      }

                                          if (pp.choixAction == 4) {
                                              if (pp.cible == 0) {
                    Color (15,0);               printf("%s perd %d PV !\n", monstre1.nom, pp.capacites_list[4]->degats);
                                                monstre1.pv = monstre1.pv - pp.capacites_list[4]->degats;
                                              } else if (pp.cible == 1) {
                                                printf("%s perd %d PV !\n", monstre2.nom, pp.capacites_list[4]->degats);
                                                monstre2.pv = monstre2.pv - pp.capacites_list[4]->degats;
                                              } else if (pp.cible == 2) {
                                                printf("%s perd %d PV !\n", monstre3.nom, pp.capacites_list[4]->degats);
                                                monstre3.pv = monstre3.pv - pp.capacites_list[4]->degats;
                                              } else if (pp.cible == 3) {
                                                printf("%s perd %d PV !\n", monstre4.nom, pp.capacites_list[4]->degats);
                                                monstre4.pv = monstre4.pv - pp.capacites_list[4]->degats;
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
                                                            if (nbreEnnemis >= 4){
                                                              if (monstre4.statut == 0){
                                                                  if (monstre4.actionM == 0 && monstre4.pv > 0) {
                                                                        if (monstre4.capacites_list[0]->degats > 0) {
                                                                          printf("%s perd %d PV !\n", pp.nom, monstre4.capacites_list[0]->degats);
                                                                          pp.pv = pp.pv - monstre4.capacites_list[0]->degats;
                                                                        } else if (monstre4.capacites_list[0]->defense > 0) {
                                                                          printf("%s se defend.\n", monstre4.nom);
                                                                        }
                                                                  } else if (monstre4.actionM == 1 && monstre4.pv > 0) {
                                                                    if (monstre4.capacites_list[1]->degats > 0) {
                                                                      printf("%s perd %d PV !\n", pp.nom, monstre4.capacites_list[1]->degats);
                                                                      pp.pv = pp.pv - monstre4.capacites_list[1]->degats;
                                                                    } else if (monstre4.capacites_list[1]->defense > 0) {
                                                                      printf("%s se defend.\n", monstre4.nom);
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
                                                              if (monstre4.statut == 0){
                                                                  if (monstre4.actionM == 0 && monstre4.capacites_list[0]->volDeVie > 0 && monstre4.pv > 0) {
                                                                    monstre4.pv = monstre4.pv + monstre4.capacites_list[0]->volDeVie;
                                                                        if (monstre4.pv > monstre4.pvMax) {
                                                                            monstre4.pv = monstre4.pvMax;
                                                                        }
                                                                    printf("%s recupere %d PV !\n", monstre4.nom, monstre4.capacites_list[0]->volDeVie);
                                                                  } else if (monstre4.actionM == 1 && monstre4.capacites_list[1]->volDeVie > 0 && monstre4.pv > 0) {
                                                                        monstre4.pv = monstre4.pv + monstre4.capacites_list[1]->volDeVie;
                                                                            if (monstre4.pv > monstre4.pvMax) {
                                                                                monstre4.pv = monstre4.pvMax;
                                                                            }
                                                                        printf("%s recupere %d PV !\n", monstre4.nom, monstre4.capacites_list[1]->volDeVie);
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
                                              } else if (nbreEnnemis == 4) {
                                                    if (monstre1.pv <= 0 && monstre2.pv <= 0 && monstre3.pv <= 0 && monstre4.pv <= 0) {
                                                      printf("Vous vous en sortez bien, pour cette fois.\n");
                                                      finCombat = 1;
                                                      pp.exp = pp.exp + monstre1.expDonnee + monstre2.expDonnee + monstre3.expDonnee + monstre4.expDonnee;
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
                                        if (pp.niveau == 9) {
                                            printf("\nVous etes desormais niveau 9, vous pouvez maintenant utiliser %s, une attaque infligeant des degats a tout les ennemis.\n", balayage.nom);
                                            Sleep(5000);
                                        }
                                        if (pp.niveau == 15) {
                                          printf("\nVous etes desormais niveau 9, vous pouvez maintenant utiliser %s, une attaque infligeant de gros degats.\n", explosif.nom);
                                          Sleep(5000);

                                        }
                                  }




          //Remise stat à leur base
            pp.capacites_list[0]->degats = pp.capacites_list[0]->degatsBase;
            pp.capacites_list[1]->degats = pp.capacites_list[1]->degatsBase;
              if (pp.niveau >= 5) {
                pp.capacites_list[2]->degats = pp.capacites_list[2]->degatsBase;
              }
              if (pp.niveau >= 9) {
                pp.capacites_list[3]->degats = pp.capacites_list[3]->degatsBase;
              }
              if (pp.niveau >= 15) {
                pp.capacites_list[4]->degats = pp.capacites_list[4]->degatsBase;
              }
            monstre1.capacites_list[0]->degats = monstre1.capacites_list[0]->degatsBase;
            monstre1.capacites_list[1]->degats = monstre1.capacites_list[1]->degatsBase;
                if (monstre1.max >= 2) {
                  monstre1.capacites_list[2]->degats = monstre1.capacites_list[2]->degatsBase;
                }
                if (monstre1.max >= 3) {
                  monstre1.capacites_list[3]->degats = monstre1.capacites_list[3]->degatsBase;
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
            if (nbreEnnemis == 4) {
              monstre2.capacites_list[0]->degats = monstre2.capacites_list[0]->degatsBase;
              monstre2.capacites_list[1]->degats = monstre2.capacites_list[1]->degatsBase;
              monstre3.capacites_list[0]->degats = monstre3.capacites_list[0]->degatsBase;
              monstre3.capacites_list[1]->degats = monstre3.capacites_list[1]->degatsBase;
              monstre4.capacites_list[0]->degats = monstre4.capacites_list[0]->degatsBase;
              monstre4.capacites_list[1]->degats = monstre4.capacites_list[1]->degatsBase;
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
                    if (monstre4.statut == 1) {
                        monstre4.statut = 0;
                    }


                                // Affichage PV
                    if (pp.niveau < 5){            printf("\n%s | PV : %d / %d", pp.nom, pp.pv, pp.pvMax);} else if (pp.niveau >= 5){printf("\n%s | PV : %d / %d | Haine : %d", pp.nom, pp.pv, pp.pvMax, pp.haine);} Color(4,0); printf("           %s | PV : %d / %d\n", monstre1.nom, monstre1.pv, monstre1.pvMax);
                    if (nbreAllie ==1){            printf("%s | PV : %d / %d", allie.nom, allie.pv, allie.pvMax);} if (nbreEnnemis > 1){printf("                                          %s | PV : %d / %d\n", monstre2.nom, monstre2.pv, monstre2.pvMax);}
                                                                                                   if (nbreEnnemis > 2){printf("                                         %s | PV : %d / %d\n", monstre3.nom, monstre3.pv, monstre3.pvMax);}
                                                                                                   if (nbreEnnemis > 3){printf("                                         %s | PV : %d / %d\n", monstre4.nom, monstre4.pv, monstre4.pvMax);}

                } // Accolade fin combat


                // pv allies
                  allie.pv = allie.pv*0.90;
                    if (allie.pv <= 0) {
                        printf("Votre allie vous quitte, a jamais.\n");
                        nbreAllie = 0;
                    }


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
                      if (nbreEnnemis >= 4) {
                        monstre4.pv = monstre4.pvMax;
                      }

  Color(15,0);
              // Chance de trouver un objet
                if (etage > 21) {
                  srand(time(NULL));
                  objetRdm = (rand() %(maxObj - minObj + 1)) + minObj;
                    if (objetRdm <= 10) {
                      printf("Vous trouvez de la %s ! Utilisez la pour vous soigner avant de poursuivre votre ascension.\n", poudrelfe.nom);
                        poudrelfe.quantiteJoueur++;
                        objetTotal++;
                    } else if (objetRdm >= 11 && objetRdm <= 20) {
                        printf("Vous trouvez un %s de vos compagnons. Utilisez le pour augmenter votre rage avant un combat.\n", souvenir.nom);
                        souvenir.quantiteJoueur++;
                        objetTotal++;
                    } else if (objetRdm >= 21 && objetRdm <= 30) {
                        printf("Vous trouvez une %s ! Utilisez la pour augmenter les degats de vos attaques.\n", aiguisage.nom);
                        aiguisage.quantiteJoueur++;
                        objetTotal++;
                    } else if (objetRdm >= 31 && objetRdm <= 40) {
                        printf("Vous trouvez un %s ! Utilisez le pour renforcer vos competences defensives.\n", renfort.nom);
                        renfort.quantiteJoueur++;
                        objetTotal++;
                    } else if (objetRdm >= 41 && objetRdm <= 50) {
                        printf("Vous trouvez une %s d'alcool. De quoi oublier cet enfer et ameliorer vos points de vie maximum.\n", flasque.nom);
                        flasque.quantiteJoueur++;
                        objetTotal++;
                    }
                }

                //Demande utilisation objet
                    if (objetTotal > 0) {
                      printf("Souhaitez-vous utiliser un objet ? [0]Oui [1]Non\n");
                      scanf("%d", &choixDirection);
                        if (choixDirection == 0) {
                          printf("Quel objet voulez-vous utiliser ?\n");
                            if (poudrelfe.quantiteJoueur > 0) {
                                printf("[0]%s\n", poudrelfe.nom);
                                printf("%s | Quantite : %d |\n", poudrelfe.nom, poudrelfe.quantiteJoueur);
                            }
                            if (souvenir.quantiteJoueur > 0) {
                                printf("[1]%s\n", souvenir.nom);
                                printf("%s | Quantite : %d |\n", souvenir.nom, souvenir.quantiteJoueur);
                            }
                            if (aiguisage.quantiteJoueur > 0) {
                                printf("[2]%s\n", aiguisage.nom);
                                printf("%s | Quantite : %d |\n", aiguisage.nom, aiguisage.quantiteJoueur);
                            }
                            if (renfort.quantiteJoueur > 0) {
                                printf("[3]%s\n", renfort.nom);
                                printf("%s | Quantite : %d |\n", renfort.nom, renfort.quantiteJoueur);
                            }
                            if (flasque.quantiteJoueur > 0) {
                                printf("[4]%s\n", flasque.nom);
                                printf("%s | Quantite : %d |\n", flasque.nom, flasque.quantiteJoueur);
                            }
                              scanf("%d", &choixObjet);
                                if (choixObjet == 0) {
                                    printf("Vous appliquez de la %s sur vos blessures et recuperez des PV !\n", poudrelfe.nom);
                                    pp.pv = pp.pv + (0.33*pp.pvMax);
                                    poudrelfe.quantiteJoueur = poudrelfe.quantiteJoueur -1;
                                    objetTotal = objetTotal -1;
                                } else if (choixObjet == 1) {
                                    printf("Vous detruisez ce %s douloureux, votre haine augmente !\n", souvenir.nom);
                                    pp.haine = pp.haine + 10;
                                    souvenir.quantiteJoueur = souvenir.quantiteJoueur -1;
                                    objetTotal = objetTotal -1;
                                } else if (choixObjet == 2) {
                                    printf("Vous aiguisez votre lame, vos degats augmentent !\n");
                                    pp.capacites_list[0]->degatsBase = pp.capacites_list[0]->degatsBase + (0.2*pp.capacites_list[0]->degatsBase);
                                    pp.capacites_list[2]->degatsBase = pp.capacites_list[2]->degatsBase + (0.2*pp.capacites_list[2]->degatsBase);
                                    pp.capacites_list[3]->degatsBase = pp.capacites_list[3]->degatsBase + (0.2*pp.capacites_list[3]->degatsBase);
                                    aiguisage.quantiteJoueur = aiguisage.quantiteJoueur -1;
                                    objetTotal = objetTotal -1;
                                } else if (choixObjet == 3) {
                                    printf("Vous renforcez votre armure, vos competences defensives sont ameliorees.\n");
                                    pp.capacites_list[1]->defense = pp.capacites_list[1]->defense +(0.3*pp.capacites_list[1]->defense);
                                    renfort.quantiteJoueur = renfort.quantiteJoueur -1;
                                    objetTotal = objetTotal -1;
                                } else if (choixObjet == 4) {
                                    printf("Vous consommez une %s, vos points de vie maximum augmentent.\n", flasque.nom);
                                    pp.pvMax = pp.pvMax + 10;
                                    flasque.quantiteJoueur = flasque.quantiteJoueur -1;
                                    objetTotal = objetTotal -1;
                                }
                        } else if (choixDirection == 1) {
                            printf("Vous preferez ne pas utiliser d'objets et continuez votre quete.\n");
                        }
                    }

Sleep(5000);
system("cls");
 }



  return 0;
} // accolade fin de programme
