#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonc.h"

void modifierMotDansChaine(char *chaine, int indexMot, int choix) {
    // Variables
    char *mots[10]; // Pour stocker jusqu'à 10 mots
    int i = 0;

    // Diviser la chaîne en mots
    char *token = strtok(chaine, " "); // Divise par les espaces
    while (token != NULL && i < 10) {
        mots[i++] = token;
        token = strtok(NULL, " ");
    }

    // Vérifier si l'index est valide
    if (indexMot < 0 || indexMot >= i) {
        fprintf(stderr, "Index du mot invalide.\n");
        return;
    }

    // Remplacer le mot
    int conv;
    conv = atoi(mots[indexMot]);
    if(choix == 1){
        conv ++;
    }
    else if(choix ==0){
        conv --;
    }
    else{
        fprintf(stderr, "Erreur de saisie.\n");
        return;
    }
    
    char buffer[20]; // Assurez-vous que le buffer est suffisamment grand pour contenir l'entier

    // Convertir l'entier en chaîne
    snprintf(buffer, sizeof(buffer), "%d", conv);

    // Dupliquer la chaîne dans mots[indexMot]
    //char *copie = strdup(buffer);

    mots[indexMot] = strdup(buffer); // Dupliquer le nouveau mot

    // Reconstruire la chaîne
    chaine[0] = '\0'; // Réinitialiser la chaîne
    for (int j = 0; j < i; j++) {
        strcat(chaine, mots[j]);
        if (j < i - 1) {
            strcat(chaine, " ");
        }
    }

    // Libérer la mémoire (strdup)
    free(mots[indexMot]);
}




// Fonction pour modifier une ligne spécifique dans un fichier
void modifierLigne(const char *nomFichier, int numeroLigne, const char *nouvelleLigne) {
    int fd = open(nomFichier, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        exit(EXIT_FAILURE);
    }

    // Lire le contenu du fichier ligne par ligne
    char buffer[1024];
    ssize_t bytesRead = 0;
    int ligneActuelle = 1;

    // Tampon pour stocker le contenu temporairement
    char contenu[8192] = {0};
    char *position = contenu;

    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Ajout de la fin de chaîne
        char *ligne = strtok(buffer, "\n");

        while (ligne != NULL) {
            if (ligneActuelle == numeroLigne) {
                // Remplace la ligne cible par la nouvelle ligne
                position += snprintf(position, sizeof(contenu) - (position - contenu), "%s\n", nouvelleLigne);
            } else {
                // Copie la ligne existante
                position += snprintf(position, sizeof(contenu) - (position - contenu), "%s\n", ligne);
            }
            ligne = strtok(NULL, "\n");
            ligneActuelle++;
        }
    }

    if (bytesRead == -1) {
        perror("Erreur lors de la lecture du fichier");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    // Réécrire le fichier avec le contenu modifié
    fd = open(nomFichier, O_WRONLY | O_TRUNC);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        exit(EXIT_FAILURE);
    }

    if (write(fd, contenu, strlen(contenu)) == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}


void AjoutVol(int nb){
    int code ;
    char destination ;
    char date;
    int sg;
    printf("Etrez le code du vols :");
    scanf("%d", &code);
    printf("Etrez la destination du vols :");
    scanf("%s", destination); 
    printf("Etrez la date du vols(format dd/mm/yy) :");
    scanf("%s", date);  
    printf("Etrez la date du le nombrede siège restant :");
    scanf("%d", &sg);
    char ligne[100];
    sprintf(ligne, "%d %s %s %d", code, destination, date, sg);
    modifierLigne("fiche.txt",nb,ligne) ;
    printf("Vol ajouté\n");

}
void mod_s_vol(){
    printf("Entrez 1 pour réserer ou 0 pour annuler un vols \n");
    int choix;
    scanf("%d",choix);
    printf("donnez le  code du vols :");
    int code ;
    scanf("%d",code);
    int fd = open("fiche.txt", O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        exit(EXIT_FAILURE);
    }

    // Lire le contenu du fichier ligne par ligne
    char buffer[1024];
    ssize_t bytesRead = 0;
    int ligneActuelle = 1;
    int comp = 0;
     char change[20]; // Assurez-vous que le buffer est suffisamment grand pour contenir l'entier

    // Convertir l'entier en chaîne
    sprintf(change,"%d", code);

    // Tampon pour stocker le contenu temporairement
    char contenu[8192] = {0};
    char *position = contenu;
    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Ajout de la fin de chaîne
        char *ligne = strtok(buffer, "\n");

        while (ligne != NULL) {
            if(strncmp(ligne, change, strlen(change)) == 0){
                break;
            }
            ligne = strtok(NULL, "\n");
            comp ++;
            
        }
    }

    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Ajout de la fin de chaîne
        char *ligne = strtok(buffer, "\n");

        while (ligne != NULL) {
            if (ligneActuelle == comp) {
                // Remplace la ligne cible par la nouvelle ligne
                modifierMotDansChaine(ligne,3,choix);
                position += snprintf(position, sizeof(contenu) - (position - contenu), "%s\n", ligne);
            } else {
                // Copie la ligne existante
                position += snprintf(position, sizeof(contenu) - (position - contenu), "%s\n", ligne);
            }
            ligne = strtok(NULL, "\n");
            ligneActuelle++;
        }
    }

    if (bytesRead == -1) {
        perror("Erreur lors de la lecture du fichier");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    // Réécrire le fichier avec le contenu modifié
    fd = open("fiche.txt", O_WRONLY | O_TRUNC);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        exit(EXIT_FAILURE);
    }

    if (write(fd, contenu, strlen(contenu)) == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    printf("\n");
}
void affichevols(){
    FILE *fichier = fopen("fiche.txt", "r"); // Ouvre le fichier en mode lecture ("r")
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[1024]; // Taille du buffer
    size_t bytesRead;

    printf("Vols disponibles:\n");
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fichier)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout); // Affiche le contenu lu
    }

    fclose(fichier); // Ferme le fichier après lecture
    printf("\n");


}

