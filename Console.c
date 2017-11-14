#include <stdio.h>

#include "Moteur.h"
#include "Console.h"

#define couleur(param) printf("\033[%sm", param)

void AfficherPlateau(Case tab[][10])
{
	int x,y;

	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			if (tab[x][y].joueur == 1)
				couleur("31");
			else if (tab[x][y].joueur == 2)
				couleur("34");
			else
				couleur("37");

			if (tab[x][y].type == -1)
				printf(" ");
			else if (tab[x][y].type == 3)
				printf("D");
			else if (tab[x][y].type == 2)
				printf("L");
			else if (tab[x][y].type == 1)
				printf("S");
			else if (tab[x][y].type == 4)
				printf("P");
			else
				printf("0");

			printf(" ");
			couleur("0");
		}
		printf("\n");
	}
}