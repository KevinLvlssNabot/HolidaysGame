#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Setup Couleur
void Color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}


// Structures
struct Perso_t{
  char nom[15];
};
typedef struct Perso_t perso;

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
  printf("\n");
}
// Main
int main(int argc, char const *argv[]) {

// variables
    int newGame;
// Ecran d'accueil
Color (6,0);
  titre();

Sleep (3000);
Color (15,0);
  welcome(newGame);
system("cls");






  return 0;
} // Accolade de fin de programme.
