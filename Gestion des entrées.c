#include <stdio.h>
#include <conio.h>   // kbhit(), getch()
#include <stdbool.h>

#define LARGEUR 5
#define HAUTEUR 5

// Lire une touche sans bloquer
char lireTouche() {
    if (kbhit()) {
        return getch();
    }
    return '\0';
}

// Déplacer le curseur
void deplacerCurseur(int *x, int *y, char touche, int Hauteur, int Largeur) {
    if (touche == 'z' && *y > 0){
      *y =-1;
    }// avancer vers le haut de l'écran 
    if (touche == 's' && *y < Hauteur - 1){
      *y =+1; // reculer
    }
    if (touche == 'q' && *x > 0){
      *x =-1; // avancer vers la gauche
    }
    if (touche == 'd' && *x < Largeur - 1){
      *x =+1; // avancer vers la droite
    }
}

// Gérer la sélection
bool gererSelection(bool selectionActive, int *selX, int *selY, int x, int y) {
    if (!selectionActive) {
        *selX = x;
        *selY = y;
        return true;
    } else {
        return false;
    }
}

// Permuter deux items
void permuterItems(int plateau[N][P], int x1, int y1, int x2, int y2) {
    int valeur1;
    int valeur2;
  
    valeur1 = plateau[y1][x1];
    valeur2 = plateau[y2][x2]; //copie des deux valeurs dans chaque case 

    plateau[y1][x1] = valeur2;
    plateau[y2][x2] = valeur1; //on permutte les deux valeurs 
}

// Affichage du plateau
void afficherPlateau(int plateau[N][P], int cx, int cy) {
    system("cls");
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            if (x == cx && y == cy)
                printf("[X] ");
            else
                printf(" %d  ", plateau[y][x]);
        }
        printf("\n");
    }
}



 
