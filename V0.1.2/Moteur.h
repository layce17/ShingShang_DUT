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

// @ Testant si le déplacement est possible
// # 1: Si déplcament possible / 0: Si déplacement impossible
int DeplacementPossible(Case tab[][10], Case *depart, Case *arrive);

// @ Calculant la distance entre deux case
// # La distance entre les deux points
int Distance(Case *depart, Case *arrive);

// @ Trouvant la direction du déplacement
// # La direction du déplacement: 0: Haut 1: Diag Haut Droit 2: Droite 3: Diag Bas Droite 4: Bas 5: Diag Bas Gauche 6: Gauche 7: Diag Haut Gauche
int Direction(Case *depart, Case *arrive, int dist);

// @ Testant si le saut est possible
// # 1: Si possible / 0: Si impossible
int SautPossible(Case tab[][10], Case *depart, int dir);

// @ Testant si la case contigue est vide
// # 1: Si vide / 0: Si non vide
int CaseVide(Case tab[][10], Case *depart, int dir);

// @ Déplaçant le pion vers la case indiquée
void Deplacement(Case *depart, Case *arrive);

#endif