#include <stdio.h>
#include <stdlib.h>

#include "Moteur.h"

void CreationPlateau(Case tab[][10])
{
	int x, y;
	Case cel;

	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			UpdateCase(&cel, 0, 0, x, y);
			tab[x][y] = cel;
		}
	}
}

void InitialisationPlateau(Case tab[][10])
{
	int x,y;

	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			if (y == 0 || y == 9)
			{
				if (x != 4 && x != 5)
					UpdateCase(&tab[x][y], 0, -1, x, y);
			}

			if (x == 0)
			{
				if (y == 1 || y == 8)
					UpdateCase(&tab[x][y], 1, 3, x, y);
				else if (y == 2 || y == 7)
					UpdateCase(&tab[x][y], 1, 2, x, y);
				else if (y == 3 || y == 6)
					UpdateCase(&tab[x][y], 1, 1, x, y);
			}
			else if (x == 1)
			{
				if (y == 1 || y == 8)
					UpdateCase(&tab[x][y], 1, 2, x, y);
				else if (y == 2 || y == 7)
					UpdateCase(&tab[x][y], 1, 1, x, y);
				else if (y == 4 || y == 5)
					UpdateCase(&tab[x][y], 1, 4, x, y);
			}
			else if (x == 2)
			{
				if (y == 1 || y == 8)
					UpdateCase(&tab[x][y], 1, 1, x, y);
			}
			else if (x == 7)
			{
				if (y == 1 || y == 8)
					UpdateCase(&tab[x][y], 2, 1, x, y);
			}
			else if (x == 8)
			{
				if (y == 1 || y == 8)
					UpdateCase(&tab[x][y], 2, 2, x, y);
				else if (y == 2 || y == 7)
					UpdateCase(&tab[x][y], 2, 1, x, y);
				else if (y == 4 || y == 5)
					UpdateCase(&tab[x][y], 2, 4, x, y);
			}
			else if (x == 9)
			{
				if (y == 1 || y == 8)
					UpdateCase(&tab[x][y], 2, 3, x, y);
				else if (y == 2 || y == 7)
					UpdateCase(&tab[x][y], 2, 2, x, y);
				else if (y == 3 || y == 6)
					UpdateCase(&tab[x][y], 2, 1, x, y);
			}
		}
	}
}

void UpdateCase(Case *cel, int joueur, int type, int x, int y)
{
	cel->joueur = joueur;
	cel->type = type;
	cel->x = x;
	cel->y = y;
}

int ExisteDeplacement(Case tab[][10], Case *cel)
{
	int retour = 0;
	int i;
	int nbCase = 0;
	Case caseOk[8]; // Au maximum 8 cases pourront être possible
	Case tmpCel;
	UpdateCase(&tmpCel, 0, -1, 0, 0);
	caseOk[0] = tmpCel;

	/** SINGES et LIONS **/
	if (cel->type == 1 || cel->type == 2)
	{
		if (ExisteContigueVide(tab, cel)) // Si il existe une case vide contiguë il peut jouer 
		{
			retour = 1;
		}
		else
		{
			if (cel->type == 1) // Singe
			{
				// Le singe peut sauter par dessus un singe uniquement
				ExisteContigueType(tab, cel, 1, caseOk, &nbCase);
				if (caseOk[0].type != -1) // Si un singe est présent
				{
					for (i = 0; i < nbCase; i++)
					{
						// détermination de la direction afin de tester si la case dans cette direction est vide
						int dir = GetDirection(&caseOk[i], cel);
						retour = CaseDirVide(tab, &caseOk[i], dir);
					}
				}
			}
			else if(cel->type == 2) // Lion
			{
				// Le lion peut sauter par dessus un lion ou un singe uniquement
				ExisteContigueType(tab, cel, 1, caseOk, &nbCase);
				ExisteContigueType(tab, cel, 2, caseOk, &nbCase);
				if (caseOk[0].type != -1) // Si il y a un singe ou un lion dans le tableau
				{
					for (i = 0; i < nbCase-1; i++) // -1 Pour palier un bug qui duplique un des pions dans le tableau
					{
						// Détermination de la direction
						int dir = GetDirection(&caseOk[i], cel);
						retour = CaseDirVide(tab, &caseOk[i], dir);
					}
				}
			}
		}
	}
	else // Dragon
	{
		// Le dragon peut sauter par dessus les lions, les singes et les dragons
		ExisteContigueType(tab, cel, 1, caseOk, &nbCase);
		ExisteContigueType(tab, cel, 2, caseOk, &nbCase);
		ExisteContigueType(tab, cel, 3, caseOk, &nbCase);
		if (caseOk[0].type != -1)
		{
			for (i = 0; i < nbCase-1; i++) // -1 Pour palier un bug qui duplique un des pions dans le tableau
			{
				int dir = GetDirection(&caseOk[i], cel);
				retour = CaseDirVide(tab, &caseOk[i], dir);
			}
		}
	} 

	return retour;
}

int ExisteContigueVide(Case tab[][10], Case *cel)
{
	int retour = 0;

	if (tab[cel->x + 1][cel->y].type == 0) // Droite
		retour = 1;
	if (tab[cel->x - 1][cel->y].type == 0) // Gauche
		retour = 1;
	if (tab[cel->x][cel->y + 1].type == 0) // Bas
		retour = 1;
	if (tab[cel->x][cel->y - 1].type == 0) // Haut
		retour = 1;
	if (tab[cel->x + 1][cel->y + 1].type == 0) // Diag Haut Droit
		retour = 1;
	if (tab[cel->x + 1][cel->y - 1].type == 0) // Diag Bas Droit
		retour = 1;
	if (tab[cel->x - 1][cel->y + 1].type == 0) // Diag Haut Gauche
		retour = 1;
	if (tab[cel->x - 1][cel->y - 1].type == 0) // Diag Bas Gauche
		retour = 1;

	return retour;
}

void ExisteContigueType(Case tab[][10], Case *cel, int type, Case *caseOk, int *nb)
{
	if (tab[cel->x + 1][cel->y].type == type) // Droite
	{
		caseOk[*nb] = tab[cel->x + 1][cel->y];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x - 1][cel->y].type == type) // Gauche
	{
		caseOk[*nb] = tab[cel->x - 1][cel->y];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x][cel->y + 1].type == type) // Bas
	{
		caseOk[*nb] = tab[cel->x][cel->y + 1];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x][cel->y - 1].type == type) // Haut
	{
		caseOk[*nb] = tab[cel->x][cel->y - 1];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x + 1][cel->y + 1].type == type) // Diag Bas Droit
	{
		caseOk[*nb] = tab[cel->x + 1][cel->y + 1];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x + 1][cel->y - 1].type == type) // Diag Haut Droit
	{
		caseOk[*nb] = tab[cel->x + 1][cel->y - 1];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x - 1][cel->y + 1].type == type) // Diag Bas Gauche
	{
		caseOk[*nb] = tab[cel->x - 1][cel->y + 1];
		*nb = *(nb) + 1;
	}
	if (tab[cel->x - 1][cel->y - 1].type == type) // Diag Haut Gauche
	{
		caseOk[*nb] = tab[cel->x - 1][cel->y - 1];
		*nb = *(nb) + 1;
	}
}

int GetDirection(Case *saut, Case *sauteur)
{
	int retour = 0;

	if (saut->x == sauteur->x && saut->y == sauteur->y - 1) // Haut
		retour = 1;
	else if (saut->x == sauteur->x + 1 && saut->y == sauteur->y - 1) // Diag Haut Droit
		retour = 2;
	else if (saut->x == sauteur->x + 1 && saut->y == sauteur->y) // Droite
		retour = 3;
	else if (saut->x == sauteur->x + 1 && saut->y == sauteur->y + 1) // Diag Bas Droit
		retour = 4;
	else if (saut->x == sauteur->x && saut->y == sauteur->y + 1) // Bas
		retour = 5;
	else if (saut->x == sauteur->x - 1 && saut->y == sauteur->y + 1) // Diag Bas Gauche
		retour = 6;
	else if (saut->x == sauteur->x - 1 && saut->y == sauteur->y) // Gauche
		retour = 7;
	else if (saut->x == sauteur->x - 1 && saut->y == sauteur->y - 1) // Diag Haut Gauche
		retour = 8;

	return retour;
}

int CaseDirVide(Case tab[][10], Case *cel, int dir)
{
	int retour = 0;

	switch (dir)
	{
		case 1: // Haut
			if (tab[cel->x][cel->y + 2].type == 0)
				retour = 1;
			break;
		case 2: // Diag Haut Droit
			if (tab[cel->x + 2][cel->y - 2].type == 0)
				retour = 1;
			break;
		case 3: // Droite
			if (tab[cel->x + 2][cel->y].type == 0)
				retour = 1;
			break;
		case 4: // Diag Bas Droit
			if (tab[cel->x + 2][cel->y + 2].type == 0)
				retour = 1;
			break;
		case 5: // Bas
			if (tab[cel->x][cel->y + 2].type == 0)
				retour = 1;
			break;
		case 6: // Diag Bas Gauche
			if (tab[cel->x - 2][cel->y + 2].type == 0)
				retour = 1;
			break;
		case 7: // Gauche
			if (tab[cel->x - 2][cel->y].type == 0)
				retour = 1;
			break;
		case 8: // Diag Haut Gauche
			if (tab[cel->x - 2][cel->y - 2].type == 0)
				retour = 1;
			break;
	}

	return retour;
}