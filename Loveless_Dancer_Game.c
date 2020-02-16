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


// Structures
struct Perso_t{
  char nom[20];
  int pv;
  int attaqueBase;
  int attaqueCombat;
  int exp;
  int levelup;
  int niveau;
  int choixAction;
};
typedef struct Perso_t perso;

struct Zone_t{
  char nom[30];
  int salleMax;
  char salle[20][30];
};
typedef struct Zone_t zone;

struct Ennemis_t{
  char nom[20];
  int pv;
  int attaqueBase;
  int attaqueCombat;
  int expDonnee;
  int max;
  int min;
  int actionM;
};
typedef struct Ennemis_t ennemis;


// Fonctions
void titre(){
  printf(" -----------------------------------\n\n");
  printf("|          LOVELESS DANCER          |\n\n");
  printf(" -----------------------------------\n\n");
}

int welcome(int newGame){
  printf("Pour commencer une nouvelle partie, appuyer sur 0 puis sur Entree.\n");
  printf("Faites cela pour chaque action au cours de la partie. Bon voyage.\n\n");
  printf("Nouvelle Partie [0] | Quitter le jeu [1]\n");
  scanf("%d", &newGame);
    if (newGame == 1) {
      return 0;
    }
}

void reveil(){
  printf("*Cough*, *Cough*, Haah, Haah.\nOu... Ou suis.. Je... \nQu'est... Ce que.. *Cough* *Cough*\nJ'ai froid, ma robe est... \n");
  Sleep(8000); system("cls");
  printf("AHHHHHHH ! Pourquoi suis-je recouverte de sang ?! Et cette obscurite... Aidez.. Moi.\nS'il... vous.. plait.\nMere...\n"); Sleep (7000); system("cls");
  Color (8,0); printf("** Ma fille.\nN'oublie jamais, que meme dans les moments les plus sombres.\nTu es une danseuse avant tout, et ta danse peut briser les plus hautes barrieres.\nRappelle toi les paroles de ton pere:\n");
  printf("Il y aura, au cours de ta vie,\nDes situations hors de ton controle,\nDes instants de honte, de joie, voire de folie,\nMais c'est au bout du chemin qu'existera ton role.**\n"); Sleep (20000); system("cls");
  printf("**Ma fille, leve-toi, et avance vers ta destinee, vers ce chemin que toi seule peut faconner.\n");
}

void nomPP(char nomJoueur[20]){
  printf("Entrez le nom de l'heroine.\n");
  scanf("%s", nomJoueur); system("cls");
  printf("Je t'aime %s**\n", nomJoueur); Color (15,0);
  printf("Mere... *Cough*.. Je dois, avancer... trouver... la sortie.\n");
}

//int carte(char nomZone[20], int n, char salle[20][30], int position, int choixDirection, int sortie){
//
//  printf("-------------- %s | %s ------------\n", nomZone, salle[position]);
//    if (position < n && position > 0) {
//        printf("Avancer [0], Reculer[1]\n");
//      } else if (position == 0) {
//        printf("Avancer [0]\n");
//      } else if (position == n){
//        printf("Reculer[1], Sortir[2]\n");
//      }
//    scanf("%d", &choixDirection);
//      while (choixDirection < 0 || choixDirection > 2) {
//        printf("Mere m'aurait dit: 'chaque chose en son temps, ma fille'.\n");
//        scanf("%d", &choixDirection);
//      }
//          if (choixDirection == 0) {
//            printf("Vous avancez.\n");
//            position++;
//          } else if (choixDirection == 1 && position > 0) {
//            printf("Vous reculez.\n");
//            position = position -1;
//          } else if (choixDirection == 2 && position == n) {
//            printf("Vous sortez de la zone.\n");
//            sortie = 1;
//          }
//}

int combat1v1(int pv, int pvM, char nom[20], char nomM[20], int choixAction, int actionM, int MAX, int MIN, int finCombat, int attaque, int attaqueM, int attaqueCombat, int attaqueCombatM, int xpM, int xp){
    printf("%s apparait.\n", nomM);
  while (finCombat == 0) {
    printf("Que dois faire %s ?\n", nom);
    printf("Attaquer [0], Defendre [1], Magie [2], Objets [3]\n");
    scanf("%d", &choixAction);
    MAX = 1, MIN = 0;
    actionM = (rand() %(MAX - MIN + 1)) + MIN;
          if (choixAction == 1) {
            attaqueCombatM = attaqueCombatM/2;
            printf("%s se defend.\n", nom);
          }
          if (actionM == 1) {
            attaqueCombat = attaqueCombat/2;
            printf("%s se defend.\n\n", nomM);
          }
      switch (choixAction) {
        case 0: printf("%s attaque.\n", nom);
                printf("%s subit %d degats.\n", nomM, attaqueCombat);
                pvM = pvM - attaqueCombat;
        break;
      }
      switch (actionM) {
        case 0: printf("%s attaque.\n", nomM);
                printf("%s subit %d degats.\n", nom, attaqueCombatM);
                pv = pv - attaqueCombatM;
        break;
      }
      attaqueCombat = attaque;
      attaqueCombatM = attaqueM;
      printf("%s | %d \n", nom, pv);
      printf("%s | %d \n", nomM, pvM);

      if (pv <= 0) {
        printf("%s tombe KO.\n", nom);
        printf("GAME OVER.\n");
        finCombat = 1;
        return 0;
      } else if (pvM <= 0) {
        printf("%s n'a plus de pv.\n");
        printf("Vous remportez %d points d'experience.\n", xpM);
        xp = xp + xpM;
        finCombat = 1;
      }
    }
}

void oneUp(char nom[20], int xp, int levelup, int niveau){
    printf("%s Nv.%d %d / %d\n", nom, niveau, xp, levelup);
  if (xp >= levelup) {
    niveau++;
    printf("Vous montez au niveau %d !\n", niveau);
    levelup = levelup*1.5;
  }
}
//  Sleep(7000); system("cls"); Color (11,0);
//  printf("La bas ! Il y a quelqu'un au fond de cette impasse ! Vite amenez-vous !\nEh! Eh! Vous m'entendez ? Reveillez-vous !\nAIDEZ-MOI A LA PORTER, BANDE DE FAINEANTS !\n");


// Main
int main(int argc, char const *argv[]) {


// variables
    int newGame;
    int position = 0;
    int choixDirection;
    int sortie = 0;
    int finCombat = 0;
    srand(time(NULL));


    zone lieuActuel;
    zone grotteDepart = {"Grotte", 2, {"Fond de la grotte","Mi-Chemin","Sortie"}};

    perso persoPrincipal = {"", 40, 7,7, 0, 50, 1};

    ennemis chauveSouris = {"Chauve-Souris", 20, 5, 5, 15, 1, 0};

while (sortie == 0) {
    printf("-------------- %s | %s ------------\n", grotteDepart.nom, grotteDepart.salle[position]);
      if (position < grotteDepart.salleMax && position > 0) {
          printf("Avancer [0], Reculer[1]\n");
        } else if (position == 0) {
          printf("Avancer [0]\n");
        } else if (position == grotteDepart.salleMax){
          printf("Reculer[1], Sortir[2]\n");
        }
      scanf("%d", &choixDirection);
        while (choixDirection < 0 || choixDirection > 2) {
          printf("Mere m'aurait dit: 'chaque chose en son temps, ma fille'.\n");
          scanf("%d", &choixDirection);
        }
            if (choixDirection == 0) {
              printf("Vous avancez.\n");
              position++;
            } else if (choixDirection == 1 && position > 0) {
              printf("Vous reculez.\n");
              position = position -1;
            } else if (choixDirection == 2 && position == grotteDepart.salleMax) {
              printf("Vous sortez de la zone.\n");
              sortie = 1;
            }
            if (position == 1) {
              combat1v1(persoPrincipal.pv, chauveSouris.pv, persoPrincipal.nom, chauveSouris.nom, persoPrincipal.choixAction, chauveSouris.actionM, chauveSouris.max, chauveSouris.min, finCombat, persoPrincipal.attaqueBase, chauveSouris.attaqueBase, persoPrincipal.attaqueCombat, chauveSouris.attaqueCombat, chauveSouris.expDonnee, persoPrincipal.exp);
              oneUp(persoPrincipal.nom, persoPrincipal.exp, persoPrincipal.levelup, persoPrincipal.niveau);
            }
}


// Ecran d'accueil
Color (6,0);
  titre();

Sleep (3000);
Color (15,0);
  welcome(newGame);
system("cls");

// Debut du jeu
  reveil(); nomPP(persoPrincipal.nom);
Color (15,0);
system("cls");

// Déplacements et premier combat
while (sortie == 0) {
    printf("-------------- %s | %s ------------\n", grotteDepart.nom, grotteDepart.salle[position]);
      if (position < grotteDepart.salleMax && position > 0) {
          printf("Avancer [0], Reculer[1]\n");
        } else if (position == 0) {
          printf("Avancer [0]\n");
        } else if (position == grotteDepart.salleMax){
          printf("Reculer[1], Sortir[2]\n");
        }
      scanf("%d", &choixDirection);
        while (choixDirection < 0 || choixDirection > 2) {
          printf("Mere m'aurait dit: 'chaque chose en son temps, ma fille'.\n");
          scanf("%d", &choixDirection);
        }
            if (choixDirection == 0) {
              printf("Vous avancez.\n");
              position++;
            } else if (choixDirection == 1 && position > 0) {
              printf("Vous reculez.\n");
              position = position -1;
            } else if (choixDirection == 2 && position == grotteDepart.salleMax) {
              printf("Vous sortez de la zone.\n");
              sortie = 1;
            }
            if (position == 1) {
              combat1v1(persoPrincipal.pv, chauveSouris.pv, persoPrincipal.nom, chauveSouris.nom, persoPrincipal.choixAction, chauveSouris.actionM, chauveSouris.max, chauveSouris.min, finCombat, persoPrincipal.attaqueBase, chauveSouris.attaqueBase, persoPrincipal.attaqueCombat, chauveSouris.attaqueCombat, persoPrincipal.exp, chauveSouris.expDonnee);
            }
}


  return 0;
} // Accolade de fin de programme.
