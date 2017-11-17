#ifndef CONSOLE_H
#define CONSOLE_H

// @: Fonction
// #: Retourne

/*** FONCTIONS ***/
// @ Affichant le plateau de jeu dans la console
void AfficherPlateau(Case tab[][10]);

// @ Demandant le pion à jouer et teste si il peut se déplacer
void SelectionPion(Case tab[][10], int joueur);

#endif