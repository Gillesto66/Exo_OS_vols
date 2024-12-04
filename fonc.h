#ifndef FONC_H
#define FONC_H

// Déclarations des fonctions pour la gestion des vols

/**
 * Modifie un mot spécifique dans une chaîne de caractères.
 * @param chaine La chaîne à modifier.
 * @param indexMot L'index du mot à modifier.
 * @param choix 1 pour incrémenter, 0 pour décrémenter.
 */
void modifierMotDansChaine(char *chaine, int indexMot, int choix);

/**
 * Modifie une ligne spécifique dans un fichier.
 * @param nomFichier Le nom du fichier à modifier.
 * @param numeroLigne Le numéro de la ligne à modifier.
 * @param nouvelleLigne La nouvelle ligne à insérer.
 */
void modifierLigne(const char *nomFichier, int numeroLigne, const char *nouvelleLigne);

/**
 * Ajoute un vol à la base de données.
 * @param nb Le numéro du vol (pour le suivi).
 */
void AjoutVol(int nb);

/**
 * Réserve ou annule une réservation pour un vol.
 */
void mod_s_vol();

/**
 * Affiche tous les vols disponibles.
 */
void affichevols();

#endif // FONC_H
