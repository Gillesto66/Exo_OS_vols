#include <stdio.h>
#include "fonc.h"

int main() {
    int nb = 2;  // Nombre de vols pour suivre l'indexation
    int choix;

    printf("\nBienvenue à Benin Air Line.\n");

    do {
        printf("\nQuel action souhaitez-vous effectuer ?\n");
        printf("1. Ajouter un vol\n");
        printf("2. Réserver sur un vol ou annuler une réservation\n");
        printf("3. Voir tous les vols disponibles\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez réessayer.\n");
            while (getchar() != '\n');  // Vider le buffer
            continue;
        }

        switch (choix) {
            case 1:
                nb++;
                AjoutVol(nb);
                break;
            case 2:
                mod_s_vol();
                break;
            case 3:
                affichevols();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Veuillez entrer un choix valide.\n");
        }
    } while (choix != 0);

    return 0;
}
