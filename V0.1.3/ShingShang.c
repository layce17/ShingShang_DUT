#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Moteur.h"
#include "Console.h"

int main(void)
{
	srand(time(NULL));

	int enter;
	int cur_joueur = rand() % (2 - 1 + 1) + 1;
	Case plateau[10][10];

	printf("- - - Bienvenue sur le jeu du Shing Shang ! - - -\n");

	do{
		printf("Voulez-vous jouer en mode console (1) ou en mode graphique (2):\n");
		scanf("%d", &enter);
	} while (enter < 1 || enter > 2);

	if (enter == 1) // Mode console
	{
		CreationPlateau(plateau);
		InitialisationPlateau(plateau);
		while (1)
		{
			printf("\nAu tour du joueur %d\n\n", cur_joueur);
			SelectionPion(plateau, cur_joueur);

			if (cur_joueur == 1)
				cur_joueur = 2;
			else
				cur_joueur = 1;
		}
	}
	else // Mode graphique
	{
		printf("Mode graphique \"Comming Soon!\"\n");
		// TODO: Mode graphique
	}

	return 0;
}