#ifndef MOTEUR_H
#define MOTEUR_H

// @: Fonction
// #: Retourne

/*** STRUCTURES ***/

typedef struct 
{
	int type; // -1: NULL - 1: Singe - 2: Lion - 3:Dragon 4: Portail
	int joueur; // 0, 1 ou 2
	int x;
	int y;
} Case;

/*** FONCTIONS ***/

// @ Créant la matrice du plateau et la remplissant pour le début du jeu
void CreationPlateau(Case tab[][10]); // tab est bien pointeur

// @ Plançant les pions au bon endroit et enlevant les cases inutiles
void InitialisationPlateau(Case tab[][10]);

// @ Mettant à jour les informations liées à la structure Case
void UpdateCase(Case *cel, int joueur, int type, int x, int y);

// @ Testant si un déplacement est possible pour un pion donné
// # 1 si possible - 0 si impossible
int DeplacementPossible(Case *cel);

#endif
