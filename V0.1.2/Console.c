#include <stdio.h>

#include "Moteur.h"
#include "Console.h"

// Fonction prépocesseur pour changer couleur du texte en console
// Source: https://openclassrooms.com/courses/des-couleurs-dans-la-console-linux
#define couleur(param) printf("\033[%sm", param)

void AfficherPlateau(Case tab[][10])
{
	int x,y;

	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
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

void SelectionPion(Case tab[][10], int joueur)
{
	int xD, yD, xA, yA;
	int possible = 0; // Booléan 1: déplacement possible / 2: déplacement impossible

	do{
		printf("Pion à déplacer:\n");
		printf("X:\n");
		scanf("%d", &xD);
		printf("Y:\n");
		scanf("%d", &yD);

		if (tab[xD][yD].type == 0 || tab[xD][yD].type == -1 || tab[xD][yD].joueur != joueur)
			printf("Pion sélectionné interdit!\n");
		else
		{
			AfficherPlateau(tab);

			printf("Case d'arrivée:\n");
			printf("X:\n");
			scanf("%d", &xA);
			printf("Y:\n");
			scanf("%d", &yA);
		}

		possible = DeplacementPossible(tab, &tab[xD][yD], &tab[xA][yA]);
		if (possible == 0)
			printf("Déplacement impossible !\n");

	} while (tab[xD][yD].joueur != joueur || possible == 0);

	Deplacement(&tab[xD][yD], &tab[xA][yA]);
}