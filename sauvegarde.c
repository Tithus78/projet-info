#include <stdio.h>
#include <string.h>


// STRUCTURE DES DONNEES 
typedef struct {
    char pseudo[50];        
    int niveau_atteint;     
    int vies_restantes;     
} SauvegardePartie;


// CONSTANTES 
#define FILENAME "sauvegardes.txt"
#define TEMP_FILENAME "temp.txt"

// PROTOTYPES DES FONCTIONS (Déplacés du .h)

int verifier_pseudo(const char* pseudo);
int charger_partie(const char* pseudo, int* niveau_ptr, int* vies_ptr);
int sauvegarder_partie(const char* pseudo, int niveau, int vies);


// 1. VERIFICATION DU PSEUDO 

int verifier_pseudo(const char* pseudo) {
    FILE *fichier_sauvegarde = NULL;
    char pseudo_lu[50];
    int niveau_lu, vies_lu;
    
    fichier_sauvegarde = fopen(FILENAME, "r");

    if (fichier_sauvegarde == NULL) {
        return 1;
    }

    while (fscanf(fichier_sauvegarde, "%s %d %d", pseudo_lu, &niveau_lu, &vies_lu) == 3) {
        
        if (strcmp(pseudo_lu, pseudo) == 0) {
            fclose(fichier_sauvegarde);
            return 0; 
        }
    }

    fclose(fichier_sauvegarde);
    return 1;
}

// 2. CHARGEMENT D'UNE PARTIE 
int charger_partie(const char* pseudo, int* niveau_ptr, int* vies_ptr) {
    FILE *fichier_sauvegarde = NULL;
    char pseudo_lu[50];
    int niveau_lu;
    int vies_lu;
    
    fichier_sauvegarde = fopen(FILENAME, "r");

    if (fichier_sauvegarde == NULL) {
        return 0; 
    }

    while (fscanf(fichier_sauvegarde, "%s %d %d", pseudo_lu, &niveau_lu, &vies_lu) == 3) {
        
        if (strcmp(pseudo_lu, pseudo) == 0) {
            
            *niveau_ptr = niveau_lu;
            *vies_ptr = vies_lu;
            
            fclose(fichier_sauvegarde);
            return 1; 
        }
    }

    fclose(fichier_sauvegarde);
    return 0; 
}


// 3. SAUVEGARDE ET MISE A JOUR DE PARTIE 
int sauvegarder_partie(const char* pseudo, int niveau, int vies) {
    FILE *sauvegardes = NULL;
    FILE *temp = NULL;
    char pseudo_lu[50];
    int niveau_lu;
    int vies_lu;
    int pseudo_trouve = 0;
    
    temp = fopen(TEMP_FILENAME, "w");

    if (temp == NULL) {
        return 0; 
    }

    sauvegardes = fopen(FILENAME, "r");

    
    if (sauvegardes != NULL) {
        
        while (fscanf(sauvegardes, "%s %d %d", pseudo_lu, &niveau_lu, &vies_lu) == 3) {
            
            if (strcmp(pseudo_lu, pseudo) == 0) {
                
                // Mise à jour
                fprintf(temp, "%s %d %d\n", pseudo, niveau, vies);
                pseudo_trouve = 1;
            } else {
                
                // Conservation
                fprintf(temp, "%s %d %d\n", pseudo_lu, niveau_lu, vies_lu);
            }
        }
        fclose(sauvegardes);
    }
    
    // Nouvel enregistrement
    if (!pseudo_trouve) {
        fprintf(temp, "%s %d %d\n", pseudo, niveau, vies);
    }

    fclose(temp);
    
    // Remplacement des fichiers
    remove(FILENAME);
    
    if (rename(TEMP_FILENAME, FILENAME) != 0) {
        return 0;
    }
    
    return 1;
}
