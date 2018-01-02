#ifndef CONSOLE_H
#define CONSOLE_H

// @: Fonction
// #: Retourne

/*** FONCTIONS ***/
// @ Affichant le plateau de jeu dans la console
void AfficherPlateau(Case tab[][10]);

// @ Demandant le pion à jouer et teste si il peut se déplacer
void SelectionPion(Case tab[][10], int joueur);

// @ Demandant le déplacement du joueur
void getPion(Case tab[][10], int joueur, int *x, int *y);

// @ Testant si le pion appartient bien au joueur
// # 1 si pion jouable / 0 si pion non jouable
int testPion(Case tab[][10], int joueur, int x, int y);

// @ Damandant la case d'arrivée du pion
void getCase(Case tab[][10], int joueur, int xD, int yD, int *xA, int *yA);

// @ Initialisant le tableau de déplacement
void initDpTab(Coor tab[8]);

// @ Attandant une entrée et vérifie si celle-ci est bien un entier
// Elle change la valeur du pointeur "enter" avec celle de l'entier rentré
void getEnter(int *enter);

#endif