#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "affichage.h"

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
    switch(valeur) {
        case 1: return '$'; // Rose dans l'image
        case 2: return '*'; // Orange
        case 3: return '#'; // Violet
        case 4: return '0'; // Gris
        default: return ' ';
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
    printf("- Utilisez ZQSD ou Fleches pour deplacer le curseur.\n");
    printf("- ESPACE pour echanger deux items.\n");
    pauseAffichage();
}

void afficherEcranJeu(
    int niveau,
    int vies,
    int temps,
    int coups,
    int contrat[4], // Valeurs à atteindre
    int actuel[4],  // Valeurs déjà collectées
    int plateau[X][Y],
    int cx,
    int cy
) {
    effacerEcran();

    // --- LIGNE SUPÉRIEURE (NIVEAU | TEMPS) ---
    printf("-----NIVEAU %02d-----|------------------------------|---------TEMPS RESTANT----------|\n", niveau);

    // Affichage des coeurs (Vies)
    printf("  ");
    for(int i=0; i<3; i++) printf(i < vies ? "  <3 " : "    ");
    printf("  |                              |             00:%02d              |\n", temps);

    printf("-------------------|                              |--------------------------------|\n");

    // --- CORPS CENTRAL ---
    printf("----CONTRAT--------|          JELLY BELLY         |---------COUPS RESTANTS---------|\n");
    printf(" Remplir le contrat|                              |              %02d                |\n", coups);
    printf(" en 30 coups max   |                              |--------------------------------|\n");
    printf("-------------------|------------------------------|------------COMMANDES-----------|\n");

    // --- BOUCLE DE DESSIN (OBJECTIFS | PLATEAU | COMMANDES) ---
    for (int i = 0; i < X; i++) {

        // 1. Colonne GAUCHE (Objectifs)
        if (i < 4) {
            char s = obtenirSymbole(i + 1);
            printf(" %c : %02d/%02d         |", s, actuel[i], contrat[i]);
        } else if (i == 4) {
            printf("-------------------|");
        } else {
            printf("                   |");
        }

        // 2. Colonne MILIEU (Le Plateau)
        printf("  ");
        for (int j = 0; j < Y; j++) {
            if (i == cy && j == cx)
                printf("[%c]", obtenirSymbole(plateau[i][j]));
            else
                printf(" %c ", obtenirSymbole(plateau[i][j]));
        }
        printf(" |");

        // 3. Colonne DROITE (Commandes dynamiques selon la ligne)
        switch(i) {
            case 0: printf(" ----Bouger----   --Selection-- |"); break;
            case 1: printf("    Z/Q/S/D          Espace     |"); break;
            case 2: printf("    Fleches                     |"); break;
            case 4: printf(" -Sauvegarde-     ---Quitter--- |"); break;
            case 5: printf("       P              Echap     |"); break;
            default: printf("                                |"); break;
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------\n");
}
