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

// @ Testant si il existe au moins un déplcament possible pour un pion donné
// # 1 si possible - 0 si impossible
int ExisteDeplacement(Case tab[][10], Case *cel);

// ~ Testant si il existe au moins une case contiguë vide
// # 1 si existe - 0 si n'existe pas
int ExisteContigueVide(Case tab[][10], Case *cel);

// @ Testant si il existe une case contiguë à la case du type donné
// # modifie un tableau de case contenant les case contigue du type donné
void ExisteContigueType(Case tab[][10], Case *cel, int type, Case *caseOk, int *nb);

// @ Trouvant la direction du saut 
// # la direction du saut 1: haut - 2: Diag Haut Droit - 3: Droite - etc... - 8:Diag Haut Gauche 
int GetDirection(Case *saut, Case *sauteur);

// @ Testant si la case après le saut est vide
// # 1 si vide - 0 si non vide
int CaseDirVide(Case tab[][10], Case *cel, int dir);

#endif