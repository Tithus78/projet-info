#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

HANDLE hConsole;

// =======================
// GESTION COULEUR/CONSOLE
// =======================
void setColor(int color) { SetConsoleTextAttribute(hConsole, color); }

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

// =======================
// AFFICHAGE PLATEAU & MENU
// =======================
char obtenirSymbole(int valeur) {
    switch(valeur){
        case 1: setColor(13); return 'O'; // violet
        case 2: setColor(12); return 'O'; // rose
        case 3: setColor(10); return 'O'; // vert
        case 4: setColor(14); return 'O'; // jaune
        case 5: setColor(11); return 'O'; // cyan
        default: setColor(7); return ' ';
    }
}

void afficherMenuPrincipal() {
    effacerEcran();
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setColor(12);
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
    setColor(7);
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
int coupscontrat = 0;
int tempscontrat = 0;
void afficherEcranJeu(int niveau, int vies, int temps, int coups, int contrat[5], int actuel[5], int plateau[8][8], int cx, int cy){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    effacerEcran();
    int minutes = temps/60;
    int secondes = temps%60;

    printf("-----NIVEAU %02d-----|---------------------------|---------TEMPS RESTANT----------|\n", niveau);

    setColor(12);
    printf("  ");
    for(int i=0;i<3;i++) printf(i<vies?" <3 " : "    ");
    setColor(7);
    printf("     |                           |             %02d:%02d              |\n", minutes, secondes);

    printf("-------------------|                           |--------------------------------|\n");

    printf("----CONTRAT--------|");
    setColor(9);
    printf("        JELLY BELLY        ");
    setColor(7);
    printf("|---------COUPS RESTANTS---------|\n");
    printf(" Remplir le contrat|                           |              %02d                |\n", coups);
    printf(" en %02d coups max   |                           |--------------------------------|\n", coupscontrat);
    printf(" et en %d min max   |                           |--------------------------------|\n", tempscontrat);
    printf("-------------------|---------------------------|------------COMMANDES-----------|\n");
    printf("                   |                           |                                |\n");


    for(int i=0;i<8;i++){
        if(i<5){
            char s = obtenirSymbole(i+1);
            printf(" %c",s);
            setColor(7);
            printf(" : %02d/%02d         |", actuel[i], contrat[i]);
        } else if(i==5) printf("                   |");
        else printf("                   |");

        printf("  ");
        for(int j=0;j<8;j++){
            if(i==cy && j==cx){
                setColor(7); printf("["); printf("%c", obtenirSymbole(plateau[i][j])); printf("]");
            } else printf(" %c ", obtenirSymbole(plateau[i][j]));
        } setColor(7);
        printf(" |");

        switch(i){
            case 0: printf(" ----Bouger----   --Selection-- |"); break;
            case 1: printf("    Z/Q/S/D          Espace     |"); break;
            case 2: printf("                                |"); break;
            case 4: printf(" -Sauvegarde-     ---Quitter--- |"); break;
            case 5: printf("       P              Echap     |"); break;
            default: printf("                                |"); break;
        }
        printf("\n");
    }
    printf("-------------------|---------------------------|---------------------------------\n");
}

// =======================
// GESTION PLATEAU & FIGURES
// =======================


int figure3Horizontale(int tab[8][8]){
    for(int i=0;i<8;i++)
        for(int j=0;j<6;j++)
            if(tab[i][j]!=0 && tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2])
                return tab[i][j];
    return 0;
}

int figure3Verticale(int tab[8][8]){
    for(int i=0;i<6;i++)
        for(int j=0;j<8;j++)
            if(tab[i][j]!=0 && tab[i][j]==tab[i+1][j] && tab[i][j]==tab[i+2][j])
                return tab[i][j];
    return 0;
}

int figure4itemHorizontale(int tab[8][8]){
    for(int i=0;i<8;i++)
        for(int j=0;j<5;j++)
            if(tab[i][j]!=0 && tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2] && tab[i][j]==tab[i][j+3])
                return tab[i][j];
    return 0;
}

int figure4itemVertical(int tab[8][8]){
    for(int i=0;i<5;i++)
        for(int j=0;j<8;j++)
            if(tab[i][j]!=0 && tab[i][j]==tab[i+1][j] && tab[i][j]==tab[i+2][j] && tab[i][j]==tab[i+3][j])
                return tab[i][j];
    return 0;
}
bool presenceFigure(int tab[8][8]){
    if(figure4itemVertical(tab)) return true;
    if(figure4itemHorizontale(tab)) return true;
    if(figure3Horizontale(tab)) return true;
    if(figure3Verticale(tab)) return true;
    return false;
}

void genererPlateau(int tab[8][8]){
    do{
        for(int i=0;i<8;i++) for(int j=0;j<8;j++) tab[i][j] = rand()%5+1;
    } while(presenceFigure(tab));
}
// Fonction simplifiée pour supprimer toutes figures et mettre à jour objectifs

// Remplir plateau
void remplirPlateau(int tab[8][8]){
    for(int j=0;j<8;j++){
        int compteur=0;
        for(int i=7;i>=0;i--){
            if(tab[i][j]==0) compteur++;
            else if(compteur>0){ tab[i+compteur][j]=tab[i][j]; tab[i][j]=0; }
        }
        for(int i=0;i<compteur;i++) tab[i][j]=rand()%5+1;
    }
}


void supprimerFigure(int tab[8][8], int actuel[5]) {
    bool trouve;

    do {
        trouve = false;
        bool aSupprimer[8][8] = {false};

        // HORIZONTAL
        for (int i = 0; i < 8; i++) {
            int count = 1;
            for (int j = 1; j <= 8; j++) {
                if (j < 8 && tab[i][j] != 0 && tab[i][j] == tab[i][j-1]) {
                    count++;
                } else {
                    if (count >= 3 && tab[i][j-1] != 0) {
                        trouve = true;
                        for (int k = 0; k < count; k++) {
                            aSupprimer[i][j-1-k] = true;
                        }
                    }
                    count = 1;
                }
            }
        }

        // VERTICAL
        for (int j = 0; j < 8; j++) {
            int count = 1;
            for (int i = 1; i <= 8; i++) {
                if (i < 8 && tab[i][j] != 0 && tab[i][j] == tab[i-1][j]) {
                    count++;
                } else {
                    if (count >= 3 && tab[i-1][j] != 0) {
                        trouve = true;
                        for (int k = 0; k < count; k++) {
                            aSupprimer[i-1-k][j] = true;
                        }
                    }
                    count = 1;
                }
            }
        }

        // SUPPRESSION + COMPTAGE
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (aSupprimer[i][j]) {
                    int val = tab[i][j];
                    if (val >= 1 && val <= 5)
                        actuel[val - 1]++;
                    tab[i][j] = 0;
                }
            }
        }

        if (trouve) remplirPlateau(tab);

    } while (trouve);
}




// =======================
// GESTION CURSEUR & ITEMS
// =======================
char lireTouche(){ if(kbhit()) return getch(); return '\0'; }

void deplacerCurseur(int *x,int *y,char touche){
    if(touche=='z' && *y>0) (*y)--;
    if(touche=='s' && *y<7) (*y)++;
    if(touche=='q' && *x>0) (*x)--;
    if(touche=='d' && *x<7) (*x)++;
}

bool sontAdjacents(int x1,int y1,int x2,int y2){
    return (abs(x1-x2)+abs(y1-y2))==1;
}

void permuterItems(int tab[8][8],int x1,int y1,int x2,int y2){
    int tmp = tab[y1][x1];
    tab[y1][x1]=tab[y2][x2];
    tab[y2][x2]=tmp;
}

// =======================
// GESTION NIVEAUX & FIN
// =======================
int finDeNiveau(int contrat[5], int actuel[5], int temps, int coups) {
    if (temps <= 0 || coups <= 0) return -1; // PERDU

    for (int i = 0; i < 5; i++)
        if (actuel[i] < contrat[i])
            return 0; // EN COURS

    return 1; // GAGNÉ
}


void initNiveau(int niveau,int contrat[5],int *temps,int *coups,int actuel[5],int plateau[8][8]){
    for(int i=0;i<5;i++){
        if(niveau==1) contrat[i]=rand()%8+5;
        else if(niveau==2) contrat[i]=rand()%10+10;
        else contrat[i]=rand()%15+15;
        actuel[i]=0;
    }

    if(niveau==1){ *temps=180; *coups=20;coupscontrat = 20;tempscontrat = 3; }
    else if(niveau==2){ *temps=120; *coups=25;coupscontrat = 25;tempscontrat = 2; }
    else{ *temps=60; *coups=35;coupscontrat = 35;tempscontrat = 1; }

    genererPlateau(plateau);
    supprimerFigure(plateau, actuel);
}

// =======================
// SAUVEGARDE
// =======================
typedef struct { char pseudo[50]; int niveau_atteint; int vies_restantes; } SauvegardePartie;
#define FILENAME "sauvegardes.txt"
#define TEMP_FILENAME "temp.txt"

int sauvegarder_partie(const char* pseudo,int niveau,int vies){
    FILE *sauvegardes=NULL,*temp=NULL;
    char pseudo_lu[50]; int niveau_lu,vies_lu; bool pseudo_trouve=false;

    temp=fopen(TEMP_FILENAME,"w");
    if(!temp) return 0;

    sauvegardes=fopen(FILENAME,"r");
    if(sauvegardes){
        while(fscanf(sauvegardes,"%s %d %d",pseudo_lu,&niveau_lu,&vies_lu)==3){
            if(strcmp(pseudo_lu,pseudo)==0){
                fprintf(temp,"%s %d %d\n",pseudo,niveau,vies);
                pseudo_trouve=true;
            } else fprintf(temp,"%s %d %d\n",pseudo_lu,niveau_lu,vies_lu);
        }
        fclose(sauvegardes);
    }

    if(!pseudo_trouve) fprintf(temp,"%s %d %d\n",pseudo,niveau,vies);
    fclose(temp);
    remove(FILENAME);
    rename(TEMP_FILENAME,FILENAME);
    return 1;
}

int charger_partie(const char* pseudo,int *niveau,int *vies){
    FILE *fichier=fopen(FILENAME,"r"); char pseudo_lu[50]; int niveau_lu,vies_lu;
    if(!fichier) return 0;
    while(fscanf(fichier,"%s %d %d",pseudo_lu,&niveau_lu,&vies_lu)==3){
        if(strcmp(pseudo_lu,pseudo)==0){
            *niveau=niveau_lu; *vies=vies_lu;
            fclose(fichier); return 1;
        }
    }
    fclose(fichier); return 0;
}

// =======================
// MAIN
// =======================

int main(){
    srand(time(NULL));
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

    int plateau[8][8]; genererPlateau(plateau); int actuel[5]={0};

    int cx=0, cy=0, selX=-1, selY=-1; bool selectionActive=false;

    int niveau=1, vies=3, temps=30, coups=20, contrat[5];

    char touche;
    DWORD dernierTemps=GetTickCount();

    // MENU PRINCIPAL
    while(1){
        afficherMenuPrincipal();
        touche=getch();
        if(touche=='1'){ afficherRegles(); }
        else if(touche=='2'){ break; }
        else if(touche=='3'){
            effacerEcran();
            char pseudo[50]; printf("Entrez votre pseudo : "); scanf("%s",pseudo);
            if(charger_partie(pseudo,&niveau,&vies)) printf("Partie chargee !\n");
            else printf("Pseudo non trouve !\n"); pauseAffichage();
            break;
        }
        else if(touche=='4') return 0;
    }

    // BOUCLE DES NIVEAUX
    int etatNiveau(int contrat[5], int actuel[5], int temps, int coups){
    if(temps<=0 || coups<=0) return -1; // perdu
    for(int i=0;i<5;i++) if(actuel[i]<contrat[i]) return 0; // en cours
    return 1; // gagné
}

    while(niveau<=3){
        initNiveau(niveau, contrat, &temps, &coups, actuel, plateau);

        int etat;
        while ((etat = finDeNiveau(contrat, actuel, temps, coups)) == 0) {
            if (etat == -1) {
                effacerEcran();
                printf("PERDU ! Vous n'avez pas rempli le contrat.\n");
                pauseAffichage();
                return 0; // FIN DU JEU
            }

            // gestion du temps
            DWORD maintenant=GetTickCount();
            if(maintenant-dernierTemps>=1000){ temps--; dernierTemps=maintenant; }

            afficherEcranJeu(niveau,vies,temps,coups,contrat,actuel,plateau,cx,cy);

            touche = lireTouche();

            deplacerCurseur(&cx,&cy,touche);

            if(touche==' '){
                if(!selectionActive){ selectionActive=true; selX=cx; selY=cy; }
                else{
                    if(sontAdjacents(selX,selY,cx,cy)){
                        permuterItems(plateau, selX, selY, cx, cy);
                        supprimerFigure(plateau, actuel);
                        remplirPlateau(plateau);
                        coups--;
                    }
                    selectionActive=false;
                }
            }

            if(touche==27) return 0;
            if(touche=='p' || touche=='P'){
                char pseudo[50]; effacerEcran(); printf("Entrez votre pseudo : "); scanf("%s",pseudo);
                sauvegarder_partie(pseudo, niveau, vies);
            }
        }
        if (etat == -1) { // PERDU
            vies--;

            effacerEcran();
            printf("PERDU !\n");
            printf("Il vous reste %d vie(s).\n", vies);
            pauseAffichage();

            if (vies <= 0) {
                effacerEcran();
                printf("GAME OVER\n");
                pauseAffichage();
                return 0; // fin du jeu
            }

    // RECOMMENCER LE MÊME NIVEAU
            genererPlateau(plateau);
            supprimerFigure(plateau, actuel);

            for (int i = 0; i < 5; i++)
                actuel[i] = 0;

            initNiveau(niveau, contrat, &temps, &coups,actuel, plateau);

            continue
        }
        if (etat == 1) { // GAGNÉ
            effacerEcran();
            printf("NIVEAU %d TERMINE !\n", niveau);
            pauseAffichage();

            niveau++;

            genererPlateau(plateau);
            supprimerFigure(plateau,actuel);

            for (int i = 0; i < 5; i++)
                actuel[i] = 0;

            initNiveau(niveau, contrat, &temps, &coups,actuel, plateau);
        }
    }

    printf("\nBravo ! Vous avez fini tous les niveaux !\n");
    pauseAffichage();
    return 0;
}
