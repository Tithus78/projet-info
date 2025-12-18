#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define X 8
#define Y 8

//Pour oublier de mettre dans le main les init de variables
//A savoir : Les item sont numérotés de 1 à 5, 0 représente une case vide
// X et Y représentent les dimensions du plateau

bool presenceFigure(int tab[X][Y]);
void genererPlateau(int tab[X][Y]); 
void afficherPlateau(int tab[X][Y]);
int figure4itemHorizontale(int tab[X][Y]);  
int figure4itemVertical(int tab[X][Y]);
int figure6itemHorizontale(int tab[X][Y]);
int figure6itemVertical(int tab[X][Y]);
int figure9croix(int tab[X][Y]);
int figurecarre(int tab[X][Y]);
void supprimerFigure(int tab[X][Y]);
void remplirPlateau(int tab[X][Y]);
int finDeNiveau(int contrat[5], int temps_restant, int coups_restant);
int initNiveau(int difficulte, int contrat[5], int *temps_restant, int *coups_restant);
int initPartie(int contrat[5], int temps_restant, int coups_restant);
int tempsRestant();   

void genererPlateau(int tab[X][Y]) {
    do {
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                tab[i][j] = rand() % 5 + 1; //0=vide et 1 à 5 = figures
            }
        }
    } while (presenceFigure(tab)); //tant qu'une figure est détecter le boucle continue
}

int figure4itemHorizontale(int tab[X][Y]){
    int case1, case2, case3,case4;
    for(int i = 0; i<X;i++){ 
        for(int j = 0; j< Y-3;j++){ //Vérification horizontale
            case1 = tab[i][j];
            case2 = tab[i][j+1];
            case3 = tab[i][j+2];
            case4 = tab[i][j+3];
            if(case1 != 0 && case1 == case2 && case1 == case3 && case1 ==case4){ //on verifie que les cases sont égales et différentes de zéro (pareille dans les autres sous programmes)
            return case1;
            }
        }
    }
    return 0;
}

int figure4itemVertical(int tab[X][Y]){
    int case1, case2, case3,case4;
    for(int i = 0; i<X-3;i++){ //Vérification vertical
        for(int j = 0; j< Y;j++){
            case1 = tab[i][j];
            case2 = tab[i+1][j];
            case3 = tab[i+2][j];
            case4 = tab[i+3][j];
            if(case1 != 0 && case1 == case2 && case1 == case3 && case1 ==case4){
            return case1;
            }
        }
    }
    return 0;
}

int figure6itemHorizontale(int tab[X][Y]){
    int case1, case2, case3,case4,case5,case6;
    for(int i = 0; i<X;i++){ 
        for(int j = 0; j< Y-5;j++){ //Vérification horizontale
            case1 = tab[i][j];
            case2 = tab[i][j+1];
            case3 = tab[i][j+2];
            case4 = tab[i][j+3];
            case5 = tab[i][j+4];
            case6 = tab[i][j+5];
            if(case1!=0 && case1==case2 && case1==case3 
                && case1==case4 && case1==case5 && case1==case6){
            return case1;
            }
        }
    }
    return 0;
}

int figure6itemVertical(int tab[X][Y]){
    int case1, case2, case3,case4,case5,case6;
    for(int i = 0; i<X-5;i++){ //Vérification vertical
        for(int j = 0; j< Y;j++){
            case1 = tab[i][j];
            case2 = tab[i+1][j];
            case3 = tab[i+2][j];
            case4 = tab[i+3][j];
            case5 = tab[i+4][j];
            case6 = tab[i+5][j];
            if(case1 != 0 && case1 == case2 && case1 == case3 
                && case1 ==case4 && case1==case5 && case1==case6){
            return case1;
            }
        }
    }
    return 0;
}

int figure9croix(int tab[X][Y]){
    int c1x, c2x, c3, c4x, c5x, c1y, c2y, c4y, c5y ; //c3 est le centre de la croix
    for(int i=2; i<X-2; i++){
        for(int j=2; j<Y-2; j++){
            c3 = tab[i][j];
            c1x = tab[i][j-2]; 
            c2x = tab[i][j-1];
            c4x = tab[i][j+1];
            c5x = tab[i][j+2];
            c1y = tab[i-2][j]; 
            c2y = tab[i-1][j];
            c4y = tab[i+1][j];
            c5y = tab[i+2][j];
            if(c3!=0 && c3==c1x && c3==c2x && c3==c4x && c3==c5x 
                && c3==c1y && c3==c2y && c3==c4y && c3==c5y ) 
            return c3;
        }
    }
    return 0;
}

int figurecarre(int tab[X][Y]){
    int c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12; //c1 est le coin supérieur gauche du carré
    for(int i=0; i<X-3; i++){
        for(int j=0; j<Y-3; j++){
            c1 = tab[i][j];
            c2 = tab[i+1][j];
            c3 = tab[i+2][j];
            c4 = tab[i+3][j];
            c5 = tab[i][j+1];
            c6 = tab[i][j+2];
            c7 = tab[i][j+3];
            c8 = tab[i+3][j+1];
            c9 = tab[i+3][j+2];
            c10 = tab[i+1][j+3];
            c11 = tab[i+2][j+3];
            c12 = tab[i+3][j+3];
            if(c1!=0 && c1==c2 && c1==c3 && c1==c4 && c1==c5 && c1==c6 
                && c1==c7 && c1==c8 && c1==c9 && c1==c10 && c1==c11 && c1==c12)
            return c1;
        }
    }
    return 0;
}

bool presenceFigure(int tab[X][Y]){
    if(figure4itemVertical(tab)) return true;         //Toutes les figures actuelles sont au moins composés de ligne/colonne de 4 item, pas besoin de vérifier plus
    else if(figure4itemHorizontale(tab)) return true; 
    else return false;
}

void supprimerFigure(int tab[X][Y]){
    int valeur;
    //Utilisation du while pour supprimer toutes les figures présentes sur le plateau
    //De la figure la plus complexe à la moins complexe
    while(presenceFigure(tab)){
        if(valeur = figure9croix(tab)){ //Suppression de la ligne et de la colonne sur laquelle se trouve la croix
            for(int i=2; i<X-2; i++){
                for(int j=2; j<Y-2; j++){
                    if(tab[i][j]==valeur && 
                       tab[i][j-2]==valeur && tab[i][j-1]==valeur && tab[i][j+1]==valeur && tab[i][j+2]==valeur &&
                       tab[i-2][j]==valeur && tab[i-1][j]==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur){
                        for(int k=0; k<Y; k++){
                            tab[i][k] = 0;
                        }
                        for(int k=0; k<X; k++){
                            tab[k][j] = 0;
                        }
                    }
                }
            }
        }
        else if(valeur = figurecarre(tab)){
            // Cherche le carré et le supprime
            for(int i=0; i<X-3; i++){
                for(int j=0; j<Y-3; j++){
                    if(tab[i][j]==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur && tab[i+3][j]==valeur &&
                       tab[i][j+1]==valeur && tab[i][j+2]==valeur && tab[i][j+3]==valeur &&
                       tab[i+3][j+1]==valeur && tab[i+3][j+2]==valeur && 
                       tab[i+1][j+3]==valeur && tab[i+2][j+3]==valeur && tab[i+3][j+3]==valeur){
                        // Supprime le carré
                        tab[i][j] = 0;
                        tab[i+1][j] = 0;
                        tab[i+2][j] = 0;
                        tab[i+3][j] = 0;
                        tab[i][j+1] = 0;
                        tab[i][j+2] = 0;
                        tab[i][j+3] = 0;
                        tab[i+3][j+1] = 0;
                        tab[i+3][j+2] = 0;
                        tab[i+1][j+3] = 0;
                        tab[i+2][j+3] = 0;
                        tab[i+3][j+3] = 0;
                        //Suppression potentielle des item dans le carré
                        if(tab[i+1][j+1]==valeur)tab[i+1][j+1] = 0;
                        if(tab[i+1][j+2]==valeur)tab[i+1][j+2] = 0;
                        if(tab[i+2][j+1]==valeur)tab[i+2][j+1] = 0;
                        if(tab[i+2][j+2]==valeur)tab[i+2][j+2] = 0;
                    }
                }
            }
        }
        else if(valeur = figure6itemHorizontale(tab)){
            for(int i=0;i<X;i++){
                for(int j=0;j<Y;j++){
                    if(tab[i][j]==valeur) tab[i][j] = 0;
                }
            }
        }
        else if(valeur = figure6itemVertical(tab)){
            for(int i=0;i<X;i++){
                for(int j=0;j<Y;j++){
                    if(tab[i][j]==valeur) tab[i][j] = 0;
                }
            }
        }
        else if(valeur = figure4itemHorizontale(tab)){
            for(int i=0;i<X;i++){
                for(int j=0;j<Y-3;j++){
                    if(tab[i][j]==valeur && tab[i][j+1]==valeur && tab[i][j+2]==valeur && tab[i][j+3]==valeur){
                        tab[i][j] = 0;
                        tab[i][j+1] = 0;
                        tab[i][j+2] = 0;
                        tab[i][j+3] = 0;
                    }
                }
            }
        }
        else if(valeur = figure4itemVertical(tab)){
            for(int i=0;i<X-3;i++){
                for(int j=0;j<Y;j++){
                    if(tab[i][j]==valeur && tab[i+1][j]==valeur && tab[i+2][j]==valeur && tab[i+3][j]==valeur){
                        tab[i][j] = 0;
                        tab[i+1][j] = 0;
                        tab[i+2][j] = 0;
                        tab[i+3][j] = 0;
                    }
                }
            }
        }
        else valeur = 0;
    }
}

void remplirPlateau(int tab[X][Y]){
    for(int j=0; j<Y; j++){ //pour chaque colonne
        int compteur = 0; //compteur de cases vides
        for(int i=X-1; i>=0; i--){ //on part du bas du tableau
            if(tab[i][j]==0){
                compteur++;
            }
            else if(compteur>0){
                tab[i+compteur][j] = tab[i][j]; //on décale la valeur vers le bas en fonction du nombre de cases vides
                tab[i][j] = 0; //on vide la case d'origine
            }
        }
        for(int i=0; i<compteur; i++){ //on remplit les cases vides en haut de la colonne
            tab[i][j] = rand()%5 +1;
        }
    }
}


int finDeNiveau(int contrat[5], int temps_restant, int coups_restant){
    // Retourne 1 si le niveau est perdu 0  si gagné (temps écoulé, coups épuisés, ou contrats remplis)
    if (temps_restant == 0) return 1;
    if (coups_restant == 0) return 1;
    if (contrat[0]==0 && contrat[1]==0 && contrat[2]== 0 && contrat[3]==0 && contrat[4] == 0) return 1;
    return 0;
}


int initNiveau(int difficulte, int contrat[5], int *temps_restant, int *coups_restant){
    if (difficulte == 1) {
        contrat[0] = rand()%8+5;
        contrat[1] = rand()%8+5;
        contrat[2] = rand()%8+5;
        contrat[3] = rand()%8+5;
        contrat[4] = rand()%8+5;
        *temps_restant = 150; 
        *coups_restant = 20;
    }
    else if (difficulte == 2) {
        contrat[0] = rand()%10 + 10;
        contrat[1] = rand()%10 + 10;
        contrat[2] = rand()%10 + 10;
        contrat[3] = rand()%10 + 10;
        contrat[4] = rand()%10 + 10;
        *temps_restant = 120; 
        *coups_restant = 25;
    }
    else if (difficulte == 3) {
        contrat[0] = rand()%14+15;
        contrat[1] = rand()%14+15;
        contrat[2] = rand()%14+15;
        contrat[3] = rand()%14+15;
        contrat[4] = rand()%14+15;
        *temps_restant = 90; 
        *coups_restant = 30;
    }
    return 0;
}

int tempRestant(){
}
















