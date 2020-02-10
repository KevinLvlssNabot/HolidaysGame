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
  char nom[20];
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

//  Sleep(7000); system("cls"); Color (11,0);
//  printf("La bas ! Il y a quelqu'un au fond de cette impasse ! Vite amenez-vous !\nEh! Eh! Vous m'entendez ? Reveillez-vous !\nAIDEZ-MOI A LA PORTER, BANDE DE FAINEANTS !\n");


// Main
int main(int argc, char const *argv[]) {

// variables
    int newGame;
    perso persoPrincipal;
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



  return 0;
} // Accolade de fin de programme.
