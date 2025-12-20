/* =============================================================
   PROJET MATCH-3 - ECE 2025 - VERSION CUSTOM FINALISÉE
   - Permutations libres (Même sans match)
   - Style d'affichage "0" colorés
   - Panneau de contrôles ajouté et corrigé (alignement)
   ============================================================= */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

// --- CONSTANTES & CONFIG ---
#define NB_LIGNES 9  
#define NB_COLONNES 9 
#define FILENAME "sauvegardes.txt"
#define TEMP_FILENAME "temp.txt"

// --- COULEURS ---
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15

// --- VARIABLES GLOBALES POUR L'AFFICHAGE ---
static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

// =============================================================
//                    OUTILS CONSOLE
// =============================================================

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clrscr() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;
    COORD home = {0, 0};
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', cellCount, home, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, home, &written);
    SetConsoleCursorPosition(hConsole, home);
}

void gotoxy(int x, int y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = x; 
    c.Y = y;
    SetConsoleCursorPosition(h, c);
}

void text_color(int color) {
    __FOREGROUND = color;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

void bg_color(int color) {
    __BACKGROUND = color;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

void hide_cursor() {
    HANDLE cH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO inf;
    GetConsoleCursorInfo(cH, &inf);
    inf.bVisible = 0;
    SetConsoleCursorInfo(cH, &inf);
}

void show_cursor() {
    HANDLE cH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO inf;
    GetConsoleCursorInfo(cH, &inf);
    inf.bVisible = 1;
    SetConsoleCursorInfo(cH, &inf);
}

void effacerEcran() {
    clrscr();
}

void pauseAffichage() {
    printf("\nAppuyez sur une touche pour continuer...");
    getch();
}

void cls(){
    system("cls");
}

// =============================================================
//                    LOGIQUE DU JEU
// =============================================================

void initNiveau(int difficulte, int contrat[5], int *temps_restant, int *coups_restant){
    for(int i=0; i<5; i++) contrat[i] = 0;

    if (difficulte == 1) {
        contrat[0] = rand()%5+6; contrat[1] = rand()%5+6; contrat[2] = rand()%5+6; 
        *temps_restant = 120; 
        *coups_restant = 20;
    }
    else if (difficulte == 2) {
        contrat[0] = rand()%6+8; contrat[1] = rand()%6+8; contrat[2] = rand()%6+8; contrat[3] = rand()%6+8;
        *temps_restant = 100; 
        *coups_restant = 25;
    }
    else if (difficulte == 3) {
        contrat[0] = rand()%8+10; contrat[1] = rand()%8+10; contrat[2] = rand()%8+10; contrat[3] = rand()%8+10; contrat[4] = rand()%8+10;
        *temps_restant = 80;
        *coups_restant = 30;
    }
    else { 
        contrat[0] = 15; contrat[1] = 15; contrat[2] = 15; contrat[3] = 15; contrat[4] = 15;
        *temps_restant = 60; 
        *coups_restant = 35;
    }
}

// Detections
int figure3itemHorizontale(int tab[NB_LIGNES][NB_COLONNES]){
    for(int i = 0; i<NB_LIGNES;i++){ for(int j = 0; j< NB_COLONNES-2;j++){ int c1 = tab[i][j]; if(c1 != 0 && c1 == tab[i][j+1] && c1 == tab[i][j+2]) return c1; }} return 0;
}
int figure3itemVertical(int tab[NB_LIGNES][NB_COLONNES]){
    for(int i = 0; i<NB_LIGNES-2;i++){ for(int j = 0; j< NB_COLONNES;j++){ int c1 = tab[i][j]; if(c1 != 0 && c1 == tab[i+1][j] && c1 == tab[i+2][j]) return c1; }} return 0;
}
int figure4itemHorizontale(int tab[NB_LIGNES][NB_COLONNES]){
    for(int i = 0; i<NB_LIGNES;i++){ for(int j = 0; j< NB_COLONNES-3;j++){ int c1 = tab[i][j]; if(c1 != 0 && c1 == tab[i][j+1] && c1 == tab[i][j+2] && c1 == tab[i][j+3]) return c1; }} return 0;
}
int figure4itemVertical(int tab[NB_LIGNES][NB_COLONNES]){
    for(int i = 0; i<NB_LIGNES-3;i++){ for(int j = 0; j< NB_COLONNES;j++){ int c1 = tab[i][j]; if(c1 != 0 && c1 == tab[i+1][j] && c1 == tab[i+2][j] && c1 == tab[i+3][j]) return c1; }} return 0;
}
int figure6itemHorizontale(int tab[NB_LIGNES][NB_COLONNES]){
    for(int i = 0; i<NB_LIGNES;i++){ for(int j = 0; j< NB_COLONNES-5;j++){ int c1=tab[i][j]; if(c1!=0 && c1==tab[i][j+1] && c1==tab[i][j+2] && c1==tab[i][j+3] && c1==tab[i][j+4] && c1==tab[i][j+5]) return c1; }} return 0;
}
int figure6itemVertical(int tab[NB_LIGNES][NB_COLONNES]){
    for(int i = 0; i<NB_LIGNES-5;i++){ for(int j = 0; j< NB_COLONNES;j++){ int c1=tab[i][j]; if(c1!=0 && c1==tab[i+1][j] && c1==tab[i+2][j] && c1==tab[i+3][j] && c1==tab[i+4][j] && c1==tab[i+5][j]) return c1; }} return 0;
}
int figure9croix(int tab[NB_LIGNES][NB_COLONNES]){
    int c3;
    for(int i=2; i<NB_LIGNES-2; i++){
        for(int j=2; j<NB_COLONNES-2; j++){
            c3 = tab[i][j];
            if(c3!=0 && c3==tab[i][j-2] && c3==tab[i][j-1] && c3==tab[i][j+1] && c3==tab[i][j+2] 
               && c3==tab[i-2][j] && c3==tab[i-1][j] && c3==tab[i+1][j] && c3==tab[i+2][j]) 
            return c3;
        }
    }
    return 0;
}
int figurecarre(int tab[NB_LIGNES][NB_COLONNES]){
    int c1;
    for(int i=0; i<NB_LIGNES-3; i++){
        for(int j=0; j<NB_COLONNES-3; j++){
            c1 = tab[i][j];
            if(c1!=0 && c1==tab[i+1][j] && c1==tab[i+2][j] && c1==tab[i+3][j] &&
               c1==tab[i][j+1] && c1==tab[i][j+2] && c1==tab[i][j+3] &&
               c1==tab[i+3][j+1] && c1==tab[i+3][j+2] && 
               c1==tab[i+1][j+3] && c1==tab[i+2][j+3] && c1==tab[i+3][j+3])
            return c1;
        }
    }
    return 0;
}

bool presenceFigure(int tab[NB_LIGNES][NB_COLONNES]){
    if(figure4itemVertical(tab)) return true;          
    else if(figure4itemHorizontale(tab)) return true; 
    else if(figure3itemVertical(tab)) return true;
    else if(figure3itemHorizontale(tab)) return true;
    else return false;
}

void genererPlateau(int tab[NB_LIGNES][NB_COLONNES]) {
    do {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = 0; j < NB_COLONNES; j++) {
                tab[i][j] = rand() % 5 + 1; 
            }
        }
    } while (presenceFigure(tab)); 
}

void permuterItems(int plateau[NB_LIGNES][NB_COLONNES], int x1, int y1, int x2, int y2) {
    int temp = plateau[y1][x1];
    plateau[y1][x1] = plateau[y2][x2];
    plateau[y2][x2] = temp;
}

void majContrat(int valeur, int contrat[5], int actuel[5]) {
    if (valeur >= 1 && valeur <= 5) {
        actuel[valeur-1]++; 
        if (contrat[valeur-1] > 0) {
            contrat[valeur-1]--;
        }
    }
}

void supprimerFigure(int tab[NB_LIGNES][NB_COLONNES], int contrat[5], int actuel[5]){
    int valeur;
    while(presenceFigure(tab)){
        if((valeur = figure9croix(tab))){ 
            for(int i=2; i<NB_LIGNES-2; i++){
                for(int j=2; j<NB_COLONNES-2; j++){
                     if(tab[i][j]==valeur && 
                       tab[i][j-2]==valeur && tab[i][j-1]==valeur && tab[i][j+1]==valeur && tab[i][j+2]==valeur &&
                       tab[i-2][j]==valeur && tab[i-1][j]==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur){
                          for(int k=0; k<NB_COLONNES; k++) { if(tab[i][k] != 0) { majContrat(tab[i][k], contrat, actuel); tab[i][k] = 0; } }
                          for(int k=0; k<NB_LIGNES; k++) { if(tab[k][j] != 0) { majContrat(tab[k][j], contrat, actuel); tab[k][j] = 0; } }
                     }
                }
            }
        }
        else if((valeur = figurecarre(tab))){
             for(int i=0; i<NB_LIGNES-3; i++){
                for(int j=0; j<NB_COLONNES-3; j++){
                    int c1 = tab[i][j];
                    if(c1==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur && tab[i+3][j]==valeur &&
                       tab[i][j+1]==valeur && tab[i][j+2]==valeur && tab[i][j+3]==valeur){
                        for(int k=0; k<4; k++) for(int l=0; l<4; l++) {
                            if(tab[i+k][j+l] != 0) { majContrat(tab[i+k][j+l], contrat, actuel); tab[i+k][j+l] = 0; }
                        }
                    }
                }
             }
        }
        else if((valeur = figure6itemHorizontale(tab))){
            for(int i=0;i<NB_LIGNES;i++){
                for(int j=0;j<NB_COLONNES-5;j++){
                    if(tab[i][j]==valeur && tab[i][j+1]==valeur && tab[i][j+5]==valeur){
                         for(int k=0; k<NB_LIGNES; k++) for(int l=0; l<NB_COLONNES; l++) {
                             if(tab[k][l]==valeur) { majContrat(tab[k][l], contrat, actuel); tab[k][l]=0; }
                         }
                    }
                }
            }
        }
        else if((valeur = figure6itemVertical(tab))){
             for(int k=0; k<NB_LIGNES; k++) for(int l=0; l<NB_COLONNES; l++) {
                 if(tab[k][l]==valeur) { majContrat(tab[k][l], contrat, actuel); tab[k][l]=0; }
             }
        }
        else if((valeur = figure4itemHorizontale(tab))){
            for(int i=0;i<NB_LIGNES;i++){
                for(int j=0;j<NB_COLONNES-3;j++){
                    if(tab[i][j]==valeur && tab[i][j+1]==valeur && tab[i][j+2]==valeur && tab[i][j+3]==valeur){
                        for(int k=0; k<4; k++) { majContrat(tab[i][j+k], contrat, actuel); tab[i][j+k] = 0; }
                    }
                }
            }
        }
        else if((valeur = figure4itemVertical(tab))){
            for(int i=0;i<NB_LIGNES-3;i++){
                for(int j=0;j<NB_COLONNES;j++){
                    if(tab[i][j]==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur && tab[i+3][j]==valeur){
                        for(int k=0; k<4; k++) { majContrat(tab[i+k][j], contrat, actuel); tab[i+k][j] = 0; }
                    }
                }
            }
        }
        else if((valeur = figure3itemHorizontale(tab))){
            for(int i=0;i<NB_LIGNES;i++){
                for(int j=0;j<NB_COLONNES-2;j++){
                    if(tab[i][j]==valeur && tab[i][j+1]==valeur && tab[i][j+2]==valeur){
                        for(int k=0; k<3; k++) { majContrat(tab[i][j+k], contrat, actuel); tab[i][j+k] = 0; }
                    }
                }
            }
        }
        else if((valeur = figure3itemVertical(tab))){
            for(int i=0;i<NB_LIGNES-2;i++){
                for(int j=0;j<NB_COLONNES;j++){
                    if(tab[i][j]==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur){
                        for(int k=0; k<3; k++) { majContrat(tab[i+k][j], contrat, actuel); tab[i+k][j] = 0; }
                    }
                }
            }
        }
        else valeur = 0;
    }
}

void remplirPlateau(int tab[NB_LIGNES][NB_COLONNES]){
    for(int j=0; j<NB_COLONNES; j++){ 
        int compteur = 0; 
        for(int i=NB_LIGNES-1; i>=0; i--){ 
            if(tab[i][j]==0) compteur++;
            else if(compteur>0){
                tab[i+compteur][j] = tab[i][j]; 
                tab[i][j] = 0; 
            }
        }
        for(int i=0; i<compteur; i++) tab[i][j] = rand()%5 +1;
    }
}

int finDeNiveau(int contrat[5], int temps_restant, int coups_restant){
    if (contrat[0]<=0 && contrat[1]<=0 && contrat[2]<= 0 && contrat[3]<=0 && contrat[4] <= 0) return 0; // Gagne
    if (temps_restant <= 0) return 1; // Perdu
    if (coups_restant <= 0) return 1; // Perdu
    return 2; // En cours
}

// =============================================================
//                    AFFICHAGE MODIFIE (STYLE 0 + CONTROLES)
// =============================================================

// Retourne toujours '0' si c'est un item (1-5)
char obtenirSymbole(int valeur) {
    if (valeur >= 1 && valeur <= 5) return '0';
    return ' ';
}

// Couleurs vives pour les différents 0
int obtenirCouleur(int valeur) {
    switch(valeur) {
        case 1: return LIGHTRED;      // 0 Rouge
        case 2: return LIGHTBLUE;     // 0 Bleu
        case 3: return LIGHTGREEN;    // 0 Vert
        case 4: return YELLOW;        // 0 Jaune
        case 5: return LIGHTMAGENTA;  // 0 Magenta
        default: return WHITE;
    }
}

void afficherMenuPrincipal() {
    effacerEcran();
    text_color(LIGHTGREEN);
    printf("########################################\n");
    printf("#             JELLY BELLY              #\n");
    printf("########################################\n\n");
    text_color(WHITE);
    printf(" 1. Regles\n");
    printf(" 2. Nouvelle partie\n");
    printf(" 3. Charger partie\n");
    printf(" 4. Quitter\n\n");
}

int afficherMenuFinNiveau() {
    effacerEcran();
    text_color(LIGHTGREEN);
    printf("########################################\n");
    printf("#            NIVEAU GAGNE !            #\n");
    printf("########################################\n\n");
    text_color(WHITE);
    printf(" 1. Continuer vers le niveau suivant\n");
    printf(" 2. Sauvegarder et Quitter\n\n");
    printf(" Votre choix : ");
    
    int choix;
    show_cursor();
    if(scanf("%d", &choix) != 1) choix = 0;
    viderBuffer();
    hide_cursor();
    return choix;
}

int afficherEcranVictoire() {
    effacerEcran();
    bg_color(BLACK);
    
    text_color(YELLOW);
    printf("\n\n");
    printf("   ******************************************\n");
    printf("   * *\n");
    printf("   * CHAMPION DU MATCH-3            *\n");
    printf("   * *\n");
    printf("   ******************************************\n\n");
    
    text_color(LIGHTGREEN);
    printf("      FELICITATIONS ! VOUS AVEZ FINI LE JEU !\n");
    printf("      Tous les niveaux ont ete completes.\n\n");

    text_color(WHITE);
    printf("   1. Retourner au Menu Principal\n");
    printf("   2. Quitter le programme\n\n");
    printf("   Votre choix : ");

    int choix;
    show_cursor();
    if(scanf("%d", &choix) != 1) choix = 0;
    viderBuffer();
    hide_cursor();
    return choix;
}

int afficherEcranDefaite() {
    effacerEcran();
    bg_color(BLACK);
    
    text_color(LIGHTRED);
    printf("\n\n");
    printf("   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("   x                                        x\n");
    printf("   x               GAME OVER                x\n");
    printf("   x                                        x\n");
    printf("   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");

    text_color(WHITE);
    printf("      Vous n'avez plus de vies...\n");
    printf("      Ne lachez rien, reessayez !\n\n");

    printf("   1. Retourner au Menu Principal\n");
    printf("   2. Quitter le programme\n\n");
    printf("   Votre choix : ");

    int choix;
    show_cursor();
    if(scanf("%d", &choix) != 1) choix = 0;
    viderBuffer();
    hide_cursor();
    return choix;
}

void afficherRegles() {
    effacerEcran();
    printf("REGLES DU JEU:\n");
    printf("- Alignez 3 symboles identiques ou plus.\n");
    printf("- Remplissez le contrat avant la fin du temps ou des coups.\n");
    printf("- Z/Q/S/D ou Fleches pour bouger.\n");
    printf("- ESPACE pour selectionner/permuter.\n");
    printf("- ECHAP pour quitter la partie en cours.\n\n");
    pauseAffichage();
}

// MODIFICATION : Nouvelle fonction d'affichage avec Panneau de Contrôle corrigé
void afficherEcranJeu(int niveau, int vies, int temps, int coups, int contrat[5], int actuel[5], int plateau[NB_LIGNES][NB_COLONNES], int cx, int cy, int selX, int selY) {
    gotoxy(0,0);
    text_color(WHITE);
    printf("NIV: %d | VIES: %d | TEMPS: %03d | COUPS: %02d     \n", niveau, vies, temps, coups);
    printf("----------------------------------------------------------\n");
    
    // Contrats
    printf("CONTRAT : ");
    for(int i=0; i<5; i++) {
        if(contrat[i] > 0) {
            text_color(obtenirCouleur(i+1));
            printf("%c:%d ", obtenirSymbole(i+1), contrat[i]);
        } else if(contrat[i] <= 0 && actuel[i] > 0) { 
            text_color(GREEN);
            printf("%c:OK ", obtenirSymbole(i+1));
        }
    }
    text_color(WHITE);
    printf("\n----------------------------------------------------------\n");
    // CORRECTION ICI : Suppression du "9x9" et réalignement
    printf("|         PLATEAU            |         CONTROLES        |\n");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < NB_LIGNES; i++) {
        printf("|");
        // PLATEAU (Gauche)
        for (int j = 0; j < NB_COLONNES; j++) {
            if (i == cy && j == cx) {
                bg_color(BLUE);
                text_color(obtenirCouleur(plateau[i][j]));
                printf("[%c]", obtenirSymbole(plateau[i][j]));
                bg_color(BLACK);
            }
            else if (i == selY && j == selX) {
                bg_color(RED);
                text_color(obtenirCouleur(plateau[i][j]));
                printf(" %c ", obtenirSymbole(plateau[i][j]));
                bg_color(BLACK);
            }
            else {
                text_color(obtenirCouleur(plateau[i][j]));
                printf(" %c ", obtenirSymbole(plateau[i][j]));
            }
        }
        text_color(WHITE);
        printf(" | ");
        
        // CONTROLES (Droite)
        switch(i) {
            case 1: printf(" Z/Q/S/D : Deplacer      "); break;
            // CORRECTION ICI : "Fleches" sans accent pour l'alignement
            case 2: printf(" Fleches : Deplacer      "); break;
            case 4: printf(" ESPACE  : Selectionner  "); break;
            case 5: printf("           Permuter      "); break;
            case 7: printf(" ECHAP   : Quitter       "); break;
            default:printf("                         "); break;
        }
        printf("|\n");
    }
    printf("----------------------------------------------------------\n");
}

// =============================================================
//                    SAUVEGARDE
// =============================================================

int verifier_pseudo(const char* pseudo) {
    FILE *fichier = fopen(FILENAME, "r");
    char lu[50];
    int n, v;
    if (fichier == NULL) return 1;
    while (fscanf(fichier, "%s %d %d", lu, &n, &v) == 3) {
        if (strcmp(lu, pseudo) == 0) {
            fclose(fichier);
            return 0; 
        }
    }
    fclose(fichier);
    return 1;
}

int charger_partie(const char* pseudo, int* niveau_ptr, int* vies_ptr) {
    FILE *fichier = fopen(FILENAME, "r");
    char lu[50];
    int n, v;
    if (fichier == NULL) return 0;
    while (fscanf(fichier, "%s %d %d", lu, &n, &v) == 3) {
        if (strcmp(lu, pseudo) == 0) {
            *niveau_ptr = n;
            *vies_ptr = v;
            fclose(fichier);
            return 1;
        }
    }
    fclose(fichier);
    return 0;
}

int sauvegarder_partie(const char* pseudo, int niveau, int vies) {
    FILE *check = fopen(FILENAME, "a");
    if(check) fclose(check);

    FILE *sauvegardes = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMP_FILENAME, "w");
    char lu[50];
    int n, v;
    int trouve = 0;

    if (temp == NULL) return 0;

    if (sauvegardes != NULL) {
        while (fscanf(sauvegardes, "%s %d %d", lu, &n, &v) == 3) {
            if (strcmp(lu, pseudo) == 0) {
                fprintf(temp, "%s %d %d\n", pseudo, niveau, vies);
                trouve = 1;
            } else {
                fprintf(temp, "%s %d %d\n", lu, n, v);
            }
        }
        fclose(sauvegardes);
    }
    if (!trouve) {
        fprintf(temp, "%s %d %d\n", pseudo, niveau, vies);
    }
    fclose(temp);
    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);
    return 1;
}

// =============================================================
//                    PROGRAMME PRINCIPAL (MAIN)
// =============================================================

int main() {
    srand((unsigned int)time(NULL));
    system("mode con: cols=100 lines=30"); 
    hide_cursor();
    
    int choix = 0;
    char pseudo[50];

    // BOUCLE GLOBALE (Menu Principal)
    while(choix != 4) {
        afficherMenuPrincipal();
        printf("Votre choix : ");
        if(scanf("%d", &choix) != 1) { viderBuffer(); continue; }
        viderBuffer();

        if(choix == 1) { 
            afficherRegles();
        }
        else if(choix == 2 || choix == 3) { 
            int plateau[NB_LIGNES][NB_COLONNES];
            int contrat[5] = {0};
            int actuel[5] = {0}; 
            int temps_max, coups, temps_restant;
            int niveau = 1, vies = 3;
            int partieValide = 0;

            effacerEcran();
            show_cursor();
            if (choix == 2) {
                printf("Entrez votre pseudo : ");
                scanf("%49s", pseudo);
                viderBuffer();
                
                if (verifier_pseudo(pseudo) == 0) {
                    printf("Ce pseudo existe deja !\n"); pauseAffichage();
                } else {
                    partieValide = 1;
                    sauvegarder_partie(pseudo, niveau, vies);
                }
            } else {
                printf("Entrez votre pseudo a charger : ");
                scanf("%49s", pseudo);
                viderBuffer();
                
                if (charger_partie(pseudo, &niveau, &vies)) {
                    printf("Partie chargee !\n"); pauseAffichage();
                    partieValide = 1;
                } else {
                    printf("Sauvegarde introuvable.\n"); pauseAffichage();
                }
            }
            hide_cursor();

            if (partieValide) {
                // BOUCLE DES NIVEAUX (Jusqu'au niveau 4)
                while(vies > 0 && niveau <= 4 && partieValide) {
                    cls();
                    initNiveau(niveau, contrat, &temps_max, &coups);
                    genererPlateau(plateau);
                    for(int i=0; i<5; i++) actuel[i] = 0;

                    int cx = 4, cy = 4;
                    int selX = -1, selY = -1;
                    int jeuEnCours = 1;
                    int niveauGagne = 0;
                    
                    clock_t debut = clock();

                    // BOUCLE DU GAMEPLAY (Temps Réel)
                    while(jeuEnCours) {
                        int temps_ecoule = (int)((clock() - debut) / CLOCKS_PER_SEC);
                        temps_restant = temps_max - temps_ecoule;

                        afficherEcranJeu(niveau, vies, temps_restant, coups, contrat, actuel, plateau, cx, cy, selX, selY);

                        if(kbhit()) {
                            char touche = getch();
                            
                            // Navigation ZQSD
                            if(touche == 'z' && cy > 0) cy--;
                            if(touche == 's' && cy < NB_LIGNES-1) cy++;
                            if(touche == 'q' && cx > 0) cx--;
                            if(touche == 'd' && cx < NB_COLONNES-1) cx++;
                            
                            // Navigation Fleches
                            if (touche == -32) {
                                touche = getch();
                                if(touche == 72 && cy > 0) cy--;
                                if(touche == 80 && cy < NB_LIGNES-1) cy++;
                                if(touche == 75 && cx > 0) cx--;
                                if(touche == 77 && cx < NB_COLONNES-1) cx++;
                            }
                            
                            // Action Espace
                            if(touche == ' ') { 
                                if(selX == -1) {
                                    selX = cx; selY = cy; 
                                } else {
                                    if (abs(cx-selX) + abs(cy-selY) == 1) {
                                        
                                        // PERMUTATION LIBRE SANS RETOUR
                                        permuterItems(plateau, selX, selY, cx, cy);
                                        
                                        // On décompte le coup dans TOUS LES CAS
                                        coups--;

                                        if (presenceFigure(plateau)) {
                                            supprimerFigure(plateau, contrat, actuel);
                                            remplirPlateau(plateau);
                                            while(presenceFigure(plateau)) {
                                                afficherEcranJeu(niveau, vies, temps_restant, coups, contrat, actuel, plateau, cx, cy, -1, -1);
                                                Sleep(200);
                                                supprimerFigure(plateau, contrat, actuel);
                                                remplirPlateau(plateau);
                                            }
                                        } 
                                        // PAS DE 'ELSE' -> Le mouvement reste validé
                                    }
                                    selX = -1; selY = -1;
                                }
                            }
                            // Quitter en cours (Echap)
                            if(touche == 27) { jeuEnCours = 0; niveauGagne = 0; partieValide = 0; }
                        }
                        
                        int fin = finDeNiveau(contrat, temps_restant, coups);
                        if(fin == 1) { jeuEnCours = 0; niveauGagne = 0; } 
                        if(fin == 0) { jeuEnCours = 0; niveauGagne = 1; }
                        Sleep(50);
                    }
                    // --- FIN DE LA BOUCLE GAMEPLAY ---

                    if (niveauGagne) {
                        // --- CAS DE VICTOIRE ---
                        if (niveau == 4) {
                            // VICTOIRE TOTALE
                            int choixFin = afficherEcranVictoire();
                            if (choixFin == 2) choix = 4; // Quitter le programme
                            
                            partieValide = 0; // Retour menu
                            remove(FILENAME); // Jeu fini = sauvegarde effacée
                        } 
                        else {
                            // NIVEAU SUIVANT
                            int choixFin = afficherMenuFinNiveau();
                            if (choixFin == 1) {
                                niveau++;
                            } else {
                                niveau++; 
                                sauvegarder_partie(pseudo, niveau, vies);
                                partieValide = 0; 
                            }
                        }
                    } 
                    else if (partieValide) { 
                        // --- CAS DE DEFAITE ---
                        vies--;
                        
                        if (vies == 0) {
                            // GAME OVER FINAL
                            int choixFin = afficherEcranDefaite();
                            if (choixFin == 2) choix = 4; 
                            
                            partieValide = 0; 
                            remove(FILENAME); // Game Over = sauvegarde effacée
                        } else {
                            // PERTE D'UNE VIE
                            effacerEcran();
                            text_color(LIGHTRED);
                            printf("\n\n   PERDU... Le temps ou les coups sont epuises.\n");
                            printf("   Il vous reste %d vies.\n", vies);
                            text_color(WHITE);
                            pauseAffichage();
                            sauvegarder_partie(pseudo, niveau, vies);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
