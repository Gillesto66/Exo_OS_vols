#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonc.h"

void testModifierMotDansChaine() {
    char chaine[] = "10 20 30";
    modifierMotDansChaine(chaine, 1, 1);
    if (strcmp(chaine, "10 21 30") == 0) {
        printf("Vérification réussie : modifierMotDansChaine\n");
    } else {
        printf("Échec : modifierMotDansChaine\n");
    }
}

void testModifierLigne() {
    // Créer un fichier de test
    FILE *fichier = fopen("testfile.txt", "w");
    fprintf(fichier, "Ligne 1\nLigne 2\nLigne 3\n");
    fclose(fichier);

    modifierLigne("testfile.txt", 2, "Nouvelle Ligne 2");

    // Vérifier le contenu du fichier
    fichier = fopen("testfile.txt", "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fichier); // Ligne 1
    fgets(buffer, sizeof(buffer), fichier); // Nouvelle Ligne 2

    if (strcmp(buffer, "Nouvelle Ligne 2\n") == 0) {
        printf("Vérification réussie : modifierLigne\n");
    } else {
        printf("Échec : modifierLigne\n");
    }
    fclose(fichier);
}

void testAjoutVol() {
    // Tester la fonction AjoutVol
    FILE *fichier = fopen("testfile.txt", "w"); // Crée le fichier si nécessaire
    fclose(fichier);
    AjoutVol(1);

    // Simple vérification pour voir si le fichier a été modifié
    fichier = fopen("testfile.txt", "r");
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        printf("Vérification réussie : AjoutVol\n");
    } else {
        printf("Échec : AjoutVol\n");
    }
    fclose(fichier);
}

void testMod_s_vol() {
    // Tester la fonction mod_s_vol
    mod_s_vol();

    // Simple vérification pour voir si le fichier a été modifié
    FILE *fichier = fopen("testfile.txt", "r");
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        printf("Vérification réussie : mod_s_vol\n");
    } else {
        printf("Échec : mod_s_vol\n");
    }
    fclose(fichier);
}

void testAffichevols() {
    // Tester la fonction affichevols
    affichevols();
    // Simple vérification pour voir si la fonction s'exécute sans erreur
    printf("Vérification (exécution) réussie : affichevols\n");
}

int main() {
    printf("Démarrage des tests...\n");
    testModifierMotDansChaine();
    testModifierLigne();
    testAjoutVol();
    testMod_s_vol();
    testAffichevols();
    printf("Fin des tests.\n");

    return 0;
}
