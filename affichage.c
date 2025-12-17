#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "affichage.h"

// ================= OUTILS =================
void effacerEcran() {
    system("cls");
}

void pauseAffichage() {
    printf("\n\nAppuyez sur une touche...");
    getch();
}

// ================= MENU PRINCIPAL =================
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

// ================= REGLES =================
void afficherRegles() {
    effacerEcran();

    printf("=============== REGLES DU JEU ===============\n\n");
    printf("- Alignez des items identiques pour les eliminer\n");
    printf("- Utilisez Z Q S D ou les fleches pour bouger\n");
    printf("- ESPACE pour selectionner un item\n");
    printf("- Remplissez le contrat avant la fin du temps\n");
    printf("- Attention au nombre de coups limites !\n");

    pauseAffichage();
}

// ================= COMMANDES =================
void afficherMenuCommandes() {
    effacerEcran();

    printf("=============== COMMANDES ===============\n\n");
    printf(" Z / Fleche Haut    : Monter\n");
    printf(" S / Fleche Bas     : Descendre\n");
    printf(" Q / Fleche Gauche  : Gauche\n");
    printf(" D / Fleche Droite  : Droite\n");
    printf(" ESPACE             : Selection\n");
    printf(" P                  : Sauvegarder\n");
    printf(" ECHAP              : Quitter la partie\n");

    pauseAffichage();
}

// ================= AFFICHAGE DU JEU =================
void afficherEcranJeu(
    int niveau,
    int vies,
    int temps,
    int coups,
    int contrat[5],
    int restant[5],
    int plateau[X][Y],
    int cx,
    int cy
) {
    effacerEcran();

    printf("---- NIVEAU %02d ----   VIES : %d\n", niveau, vies);
    printf("TEMPS : %03d s   COUPS : %02d\n\n", temps, coups);

    printf("CONTRAT :\n");
    for (int i = 0; i < 5; i++) {
        printf(" Item %d : %d / %d\n", i + 1, restant[i], contrat[i]);
    }

    printf("\n");

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            if (i == cy && j == cx)
                printf("[");
            else
                printf(" ");

            if (plateau[i][j] == 0) printf(" ");
            else printf("%d", plateau[i][j]);

            if (i == cy && j == cx)
                printf("]");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\nZQSD / Fleches | ESPACE | P | ECHAP\n");
}



//---- petit main des familles pour observer l'affichage---------



/* enlever ça si vous voulez tester :
#define X 8
#define Y 8

int main() {
    // Variables de test pour le plateau
    int plateau[X][Y] = {
        {1, 0, 2, 0, 3},
        {0, 1, 0, 2, 0},
        {3, 0, 1, 0, 2},
        {0, 3, 0, 1, 0},
        {2, 0, 3, 0, 1}
    };

    int contrat[5] = {3, 2, 4, 1, 5};
    int restant[5] = {1, 0, 2, 0, 3};
    int cx = 2, cy = 2; // Position du curseur
    int niveau = 1, vies = 3, temps = 120, coups = 5;

    // Affichage du menu principal
    afficherMenuPrincipal();
    pauseAffichage();

    // Affichage des règles
    afficherRegles();

    // Affichage des commandes
    afficherMenuCommandes();

    // Affichage de l'écran de jeu
    afficherEcranJeu(niveau, vies, temps, coups, contrat, restant, plateau, cx, cy);
    pauseAffichage();

    return 0;
}
*/
