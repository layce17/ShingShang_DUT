#ifndef MOTEUR_H
#define MOTEUR_H

// @: Fonction
// #: Retourne

/*** STRUCTURES ***/
typedef struct 
{
	int x;
	int y;
} Coor;

typedef struct 
{
	int numero;
	int shingShang; // 1 si le joueur est entrain de faire un shingShang
	int nbDragon;
	int portail; // 1 si dragon sur portail
} Joueur;

typedef struct 
{
	int type; // -1: NULL - 1: Singe - 2: Lion - 3:Dragon 4: Portail
	int joueur; // 0, 1 ou 2
	Coor pos;
	int selected;
} Case;

/*** GLOBALES ***/
Joueur joueur1;
Joueur joueur2;

/*** FONCTIONS ***/

// @ Créant la matrice du plateau et la remplissant pour le début du jeu
void CreationPlateau(Case tab[][10]); // tab est bien pointeur

// @ Plançant les pions au bon endroit et enlevant les cases inutiles
void InitialisationPlateau(Case tab[][10]);

// @ Mettant à jour les informations liées à la structure Case
void UpdateCase(Case *cel, int joueur, int type, int x, int y);

// @ Mettant à jour la selection du pion
void UpdateSelected(Case *cel, int sel);

// @ Testant si le déplacement est possible
// # 1: Si déplcament possible / 0: Si déplacement impossible / 2: si dragon sur portail
int DeplacementPossible(Case tab[][10], Case *depart, Case *arrive);

// @ Calculant la distance entre deux case
// # La distance entre les deux points
int Distance(Coor *depart, Coor *arrive);

// @ Trouvant la direction du déplacement
// # La direction du déplacement: 0: Haut 1: Diag Haut Droit 2: Droite 3: Diag Bas Droite 4: Bas 5: Diag Bas Gauche 6: Gauche 7: Diag Haut Gauche
int Direction(Coor *depart, Coor *arrive, int dist);

// @ Testant si le saut est possible
// # 1: Si possible / 0: Si impossible
int SautPossible(Case tab[][10], Case *depart, int dir);

// @ Testant si la case contigue est vide
// # 1: Si vide / 0: Si non vide
int CaseVide(Case tab[][10], Case *depart, int dir);

// @ Déplaçant le pion vers la case indiquée
void Deplacement(Case *depart, Case *arrive);

// @ Testant si un autre coup est possible (uniquement un saut)
// # 1: possible / 0: impossible
int ExisteDeplacement(Case tab[][10], Case *cel, Coor tabDpl[8], int *nbSauts);

void UpdateCoor(Coor *c, int x, int y);

void InitJoueur();

// @ Testant si un joueur a gagné
// # 0: si personne n'a gagné / 1: si joueur 1 gagne / 2: si joueur 2 gagne
int testVictoire();

#endif
