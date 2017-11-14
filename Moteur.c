#include <stdio.h>

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