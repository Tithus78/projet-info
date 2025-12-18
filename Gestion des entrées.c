#include <stdio.h>
#include <conio.h>   // kbhit(), getch()
#include <stdbool.h>

#define X 8
#define Y 8

// Lire une touche sans bloquer
char lireTouche() {
    if (kbhit()) {
        return getch();
    }
    return '\0';
}

// Déplacer le curseur
void deplacerCurseur(int *x, int *y, char touche, int X, int Y) {
    if (touche == 'z' && *y > 0){
      *y =-1;
    }// avancer vers le haut de l'écran 
    if (touche == 's' && *y < Y - 1){
      *y =+1; // reculer
    }
    if (touche == 'q' && *x > 0){
      *x =-1; // avancer vers la gauche
    }
    if (touche == 'd' && *x < X - 1){
      *x =+1; // avancer vers la droite
    }
}

// Gérer la sélection
bool gererSelection(bool selectionActive, int *selX, int *selY, int x, int y) {
    if (selectionActive) 
        return false;
    
   *selX = x; 
   *selY = y; // enregistrement des positions
   return true;
}

// Permuter deux items
void permuterItems(int plateau[X][Y], int x1, int y1, int x2, int y2) {
    int valeur1;
    int valeur2;
  
    valeur1 = plateau[y1][x1];
    valeur2 = plateau[y2][x2]; //copie des deux valeurs dans chaque case 

    plateau[y1][x1] = valeur2;
    plateau[y2][x2] = valeur1; //on permutte les deux valeurs 
}

// Affichage du plateau
void afficherPlateau(int plateau[X][Y], int cx, int cy) {
    system("cls"); // effece l'écran
    
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) { // parcourir le plateau
            if (x == cx && y == cy)
                printf("[X] ");  // curseur
            else
                printf(" %d  ", plateau[X][Y]);
        }
        printf("\n");
    }
}



 
