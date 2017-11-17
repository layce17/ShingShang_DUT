#include <stdio.h>

#include "Moteur.h"
#include "Console.h"

// Fonction prépocesseur pour changer couleur du texte en console
// Source: https://openclassrooms.com/courses/des-couleurs-dans-la-console-linux
#define couleur(param) printf("\033[%sm", param)

void AfficherPlateau(Case tab[][10])
{
	int x,y;

	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			if (x == 9 && y == 1)
				couleur("32");
			else if (tab[x][y].joueur == 1)
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

void SelectionPion(Case tab[][10], int joueur)
{
	int x, y;

	do{
		printf("X:\n");
		scanf("%d", &x);
		printf("Y:\n");
		scanf("%d", &y);

		if (tab[x][y].type == 0 || tab[x][y].type == -1)
			printf("Pion sélectionné interdit!");
	} while (tab[x][y].joueur == joueur && ExisteDeplacement(tab, &tab[x][y]) == 0);

	printf("Deplacement! %d\n", tab[x][y].joueur);
	// TODO: Création fonction déplacement
}