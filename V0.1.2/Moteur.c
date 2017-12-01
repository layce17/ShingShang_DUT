#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
			if (x == 0 || x == 9)
			{
				if (y != 4 && y != 5)
					UpdateCase(&tab[x][y], 0, -1, x, y);
			}
			else if (y == 0)
			{
				if (x == 1 || x == 8)
					UpdateCase(&tab[x][y], 1, 3, x, y);
				else if (x == 2 || x == 7)
					UpdateCase(&tab[x][y], 1, 2, x, y);
				else if (x == 3 || x == 6)
					UpdateCase(&tab[x][y], 1, 1, x, y);
			}
			else if (y == 1)
			{
				if (x == 1 || x == 8)
					UpdateCase(&tab[x][y], 1, 2, x, y);
				else if (x == 2 || x == 7)
					UpdateCase(&tab[x][y], 1, 1, x, y);
				else if (x == 4 || x == 5)
					UpdateCase(&tab[x][y], 1, 4, x, y);
			}
			else if (y == 2)
			{
				if (x == 1 || x == 8)
					UpdateCase(&tab[x][y], 1, 1, x, y);
			}
			else if (y == 7)
			{
				if (x == 1 || x == 8)
					UpdateCase(&tab[x][y], 2, 1, x, y);
			}
			else if (y == 8)
			{
				if (x == 1 || x == 8)
					UpdateCase(&tab[x][y], 2, 2, x, y);
				else if (x == 2 || x == 7)
					UpdateCase(&tab[x][y], 2, 1, x, y);
				else if (x == 4 || x == 5)
					UpdateCase(&tab[x][y], 2, 4, x, y);
			}
			else if (y == 9)
			{
				if (x == 1 || x == 8)
					UpdateCase(&tab[x][y], 2, 3, x, y);
				else if (x == 2 || x == 7)
					UpdateCase(&tab[x][y], 2, 2, x, y);
				else if (x == 3 || x == 6)
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

int DeplacementPossible(Case tab[][10], Case *depart, Case *arrive)
{
	int dist = Distance(depart, arrive);
	int dir = Direction(depart, arrive, dist);
	int retour = 0;

	// Singe
	if (depart->type == 1)
	{
		if (dist == 1 && arrive->type == 0) // Mouvement d'une case contigue
			retour = 1;
		else if (dist == 2 && arrive->type == 0 && CaseVide(tab, depart, dir) == 1) // Déplacement de 2 cases (unique au Singe)
			retour = 1;
		else if (dist == 2 && arrive->type == 0 && SautPossible(tab, depart, dir) == 1) // Saut
			retour = 1;
	}
	// Lion
	else if (depart->type == 2)
	{
		if (dist == 1 && arrive->type == 0) // Mouvement d'une case contigue
			retour = 1;
		else if (dist == 2 && arrive->type == 0 && SautPossible(tab, depart, dir) == 1) // Saut 
			retour = 1;
	}
	// Dragon
	else
	{
		if (dist == 2 && arrive->type == 0 && SautPossible(tab, depart, dir) == 1) // Saut
			retour = 1;
	}

	return retour;
}

int Distance(Case *depart, Case *arrive)
{
	return sqrt(((arrive->x - depart->x)*(arrive->x - depart->x)) + (arrive->y - depart->y)*(arrive->y - depart->y)); //sqrt((xb-xa)²+(yb-ya)²)
}

int Direction(Case *depart, Case *arrive, int dist)
{
	int retour = 0;

	if (depart->x == arrive->x && depart->y == arrive->y - dist) // Bas
		retour = 4;
	else if (depart->x == arrive->x + dist && depart->y == arrive->y - dist) // Diag Bas gauche
		retour = 5;
	else if (depart->x == arrive->x + dist && depart->y == arrive->y) // Gauche
		retour = 6;
	else if (depart->x == arrive->x + dist && depart->y == arrive->y + dist) // Diag Haut gauche
		retour = 7;
	else if (depart->x == arrive->x && depart->y == arrive->y + dist) // Haut
		retour = 0;
	else if (depart->x == arrive->x - dist && depart->y == arrive->y + dist) // Diag Haut droite
		retour = 1;
	else if (depart->x == arrive->x - dist && depart->y == arrive->y) // Droite
		retour = 2;
	else if (depart->x == arrive->x - dist && depart->y == arrive->y - dist) // Diag Bas droite
		retour = 3;

	return retour;
}

int SautPossible(Case tab[][10], Case *depart, int dir)
{
	int retour = 0;
	int x = depart->x;
	int y = depart->y;

	switch(dir)
	{
		case 0: // Haut
			if (tab[x][y-1].type <= depart->type && tab[x][y-1].type != 0)
				retour = 1;
			break;
		case 1: // Diag Haut Droit
			if (tab[x+1][y-1].type <= depart->type && tab[x+1][y-1].type != 0)
				retour = 1;
			break;
		case 2: // Droite
			if (tab[x+1][y].type <= depart->type && tab[x+1][y].type != 0)
				retour = 1;
			break;
		case 3: // Diag Bas Droite
			if (tab[x+1][y+1].type <= depart->type && tab[x+1][y+1].type != 0)
				retour = 1;
			break;
		case 4: // Bas
			if (tab[x][y+1].type <= depart->type && tab[x][y+1].type != 0)
				retour = 1;
			break;
		case 5: // Diag Bas Gauche
			if (tab[x-1][y+1].type <= depart->type && tab[x-1][y+1].type != 0)
				retour = 1;
			break;
		case 6: // Gauche
			if (tab[x-1][y].type <= depart->type && tab[x-1][y].type != 0)
				retour = 1;
			break;
		case 7: // Diag Haut Gauche
			if (tab[x-1][y-1].type <= depart->type && tab[x-1][y-1].type != 0)
				retour = 1;
			break;
	}

	return retour;
}

int CaseVide(Case tab[][10], Case *depart, int dir)
{
	int retour = 0;
	int x = depart->x;
	int y = depart->y;

	switch(dir)
	{
		case 0: // Haut
			if (tab[x][y-1].type == 0)
				retour = 1;
			break;
		case 1: // Diag Haut Droit
			if (tab[x+1][y-1].type == 0)
				retour = 1;
			break;
		case 2: // Droite
			if (tab[x+1][y].type == 0)
				retour = 1;
			break;
		case 3: // Diag Bas Droite
			if (tab[x+1][y+1].type == 0)
				retour = 1;
			break;
		case 4: // Bas
			if (tab[x][y+1].type == 0)
				retour = 1;
			break;
		case 5: // Diag Bas Gauche
			if (tab[x-1][y+1].type == 0)
				retour = 1;
			break;
		case 6: // Gauche
			if (tab[x-1][y].type == 0)
				retour = 1;
			break;
		case 7: // Diag Haut Gauche
			if (tab[x-1][y-1].type == 0)
				retour = 1;
			break;
	}

	return retour;
}

void Deplacement(Case *depart, Case *arrive)
{
	arrive->type = depart->type;
	arrive->joueur = depart->joueur;

	depart->type = 0;
	depart->joueur = 0;
}