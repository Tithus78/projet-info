#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "affichage.h"
#include <windows.h>

HANDLE hConsole;

void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

// Outils pour la gestion de la console
void effacerEcran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseAffichage() {
    printf("\nAppuyez sur une touche pour continuer...");
    getch();
}

// Transforme l'entier du plateau en symbole visuel
char obtenirSymbole(int valeur) {
    switch (valeur) {
        case 1: setColor(13); return 'O'; // Violet
        case 2: setColor(12); return 'O'; // Rose
        case 3: setColor(10); return 'O'; // Vert
        case 4: setColor(14); return 'O'; // Jaune
        case 5: setColor(11); return 'O';
        default: setColor(7); return ' ';
    }
}
void afficherMenuPrincipal() {
    effacerEcran();

    printf("########################################################\n");
    printf("#                                                      #\n");
    printf("#          ######  #####  ##     ##    ##    ##        #\n");
    printf("#            ##    ##     ##     ##     ##  ##         #\n");
    printf("#            ##    ####   ##     ##       ##           #\n");
    printf("#         ## ##    ##     ##     ##       ##           #\n");
    printf("#          ###     #####  #####  #####    ##           #\n");
    printf("#                                                      #\n");
    printf("#                                                      #\n");
    printf("#         ######   #####  ##     ##    ##    ##        #\n");
    printf("#         ##  ##   ##     ##     ##     ##  ##         #\n");
    printf("#         #####    ####   ##     ##       ##           #\n");
    printf("#         ##  ##   ##     ##     ##       ##           #\n");
    printf("#         #####    #####  #####  #####    ##           #\n");
    printf("#                                                      #\n");
    printf("########################################################\n\n");

    printf(" 1. Lire les regles du jeu\n");
    printf(" 2. Commencer une nouvelle partie\n");
    printf(" 3. Reprendre une partie sauvegardee\n");
    printf(" 4. Quitter\n");
}

void afficherRegles() {
    effacerEcran();
    printf("=============== REGLES DU JEU ===============\n\n");
    printf("- Alignez 3 items ou plus pour les collecter.\n");
    printf("- Atteignez les objectifs du contrat.\n");
    printf("- Utilisez ZQSD pour deplacer le curseur.\n");
    printf("- ESPACE pour echanger deux items.\n");
    pauseAffichage();
}

void afficherEcranJeu(
    int niveau,
    int vies,
    int temps,
    int coups,
    int contrat[5], // Valeurs à atteindre
    int actuel[5],  // Valeurs déjà collectées
    int plateau[8][8],
    int cx,
    int cy
) { hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    effacerEcran();

    // --- LIGNE SUPÉRIEURE (NIVEAU | TEMPS) ---
    printf("-----NIVEAU %02d-----|---------------------------|---------TEMPS RESTANT----------|\n", niveau);

    // Affichage des coeurs (Vies)
    setColor(12);
    printf("  ");
    for(int i=0; i<3; i++) printf(i < vies ? "  <3 " : "    ");
    setColor(7);

    printf("  |                           |             00:%02d              |\n", temps);

    printf("-------------------|                           |--------------------------------|\n");

    // --- CORPS CENTRAL ---
    printf("----CONTRAT--------|        JELLY BELLY        |---------COUPS RESTANTS---------|\n");
    printf(" Remplir le contrat|                           |              %02d                |\n", coups);
    printf(" en 30 coups max   |                           |--------------------------------|\n");
    printf("-------------------|---------------------------|------------COMMANDES-----------|\n");

    // --- BOUCLE DE DESSIN (OBJECTIFS | PLATEAU | COMMANDES) ---
    for (int i = 0; i < 8; i++) {

        // 1. Colonne GAUCHE (Objectifs)
        if (i < 5) {
            char s = obtenirSymbole(i + 1);
            printf(" %c", s);
            setColor(7);
            printf(" : %02d/%02d         |", actuel[i], contrat[i]);
        } else if (i == 5) {
            printf("-------------------|");
        } else {
            printf("                   |");
        }

        // 2. Colonne MILIEU (Le Plateau)
        printf("  ");
        for (int j = 0; j < 8; j++) {
            if (i == cy && j == cx){
                setColor(7);
                printf("[");
                printf("%c", obtenirSymbole(plateau[i][j]));
                setColor(7);
                printf("]");
                }
            else
                printf(" %c ", obtenirSymbole(plateau[i][j]));
        }setColor(7);
        printf(" |");

        // 3. Colonne DROITE (Commandes dynamiques selon la ligne)
        switch(i) {
            case 0: printf(" ----Bouger----   --Selection-- |"); break;
            case 1: printf("    Z/Q/S/D          Espace     |"); break;
            case 2: printf("                                |"); break;
            case 4: printf(" -Sauvegarde-     ---Quitter--- |"); break;
            case 5: printf("       P              Echap     |"); break;
            default: printf("                                |"); break;
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------\n");
}


/* Le affichage.h :

#ifndef AFFICHAGE_H
#define AFFICHAGE_H


void effacerEcran();
void pauseAffichage();

void afficherMenuPrincipal();
void afficherRegles();

void afficherEcranJeu(
    int niveau,
    int vies,
    int temps,
    int coups,
    int contrat[5],
    int actuel[5],
    int plateau[8][8],
    int cx,
    int cy
);

#endif
*/



/* Un main test :
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "affichage.h"
#define X 8
#define Y 8
int main() {
    srand(time(NULL));

    int niveau = 1, vies = 3, temps = 17, coups = 7;
    int contrat[5] = {20, 10, 20, 10,15};
    int actuel[5]  = {12, 5, 18, 10,7};
    int plateau[X][Y];

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            plateau[i][j] = (rand() % 5) + 1;
        }
    }

    afficherMenuPrincipal();
    printf("\nAppuyez sur une touche pour voir les regles...");
    getch(); // Correction ici aussi

    afficherRegles();
    afficherEcranJeu(niveau, vies, temps, coups, contrat, actuel, plateau, 5, 5);

    printf("\nTest termine.\n");
    getch(); // Correction ici aussi

    return 0;
}
*/
