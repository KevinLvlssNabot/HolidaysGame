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
    int haineNecessaire;
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
int etage = 1;
int nbreEnnemis;

capacites trancher = {"Trancher", 10, 0};
capacites defendre = {"Defendre", 5, 0};
capacites attaquer = {"Attaquer", 5};
capacites sucer = {"Sucer le sang", 7};


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

printf("%s %d %d\n", sangsueG.capacites_list[1]->nom, sangsueG.capacites_list[1]->degats, sangsueG.capacites_list[1]->haineNecessaire);
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
  printf("Bienvenue %s\n", pp.nom);
Sleep (2000);
  printf("Vous vous appretez a vivre une epreuve difficile, voire insurmontable.\nPlongez dans les tenebres d'un sabbat sanguinaire, serez-vous assez fort et intelligent pour en sortir indemne et obtenir votre vengeance ?");
  printf("Seul l'avenir nous le dira. Je vous souhaiterez bien bonne chance, mais dans ce monde, la chance n'a pas sa place.\n");

 while (finPartie == 0) {
   printf(" -----------------------------------\n\n");
   printf("|              ETAGE %d              |\n\n", etage);
   printf(" -----------------------------------\n\n");
  if (pp.niveau < 5) {
      printf("%s | %d | %d / %d\n", pp.nom, pp.niveau, pp.exp, pp.levelup);
  } else {
    printf("%s | Lvl : %d | Exp : %d / %d | Haine : %d\n", pp.nom, pp.niveau, pp.exp, pp.levelup, pp.haine);
  }
Sleep (2000);
      if (etage < 10) {
            srand(time(NULL));
          int MAX = 3, MIN = 1;
          nbreEnnemis = (rand() %(MAX - MIN + 1)) + MIN;
            if (nbreEnnemis == 1) {
                monstre1 = sangsueG;
            }
      }

 }



  return 0;
} // accolade fin de programme
