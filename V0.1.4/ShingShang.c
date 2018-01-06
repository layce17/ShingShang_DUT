#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Moteur.h"
#include "Console.h"

int main(void)
{
	srand(time(NULL));

	InitJoueur();

	int enter;
	int cur_joueur = rand() % (2 - 1 + 1) + 1;
	Case plateau[10][10];

	printf("- - - Bienvenue sur le jeu du Shing Shang ! - - -\n");
		CreationPlateau(plateau);
		InitialisationPlateau(plateau);

	while (testVictoire() == 0)
	{
		printf("\nAu tour du joueur %d\n\n", cur_joueur);
		SelectionPion(plateau, cur_joueur);

		if (cur_joueur == 1)
			cur_joueur = 2;
		else
			cur_joueur = 1;
	}

	if (joueur1.portail || joueur2.nbDragon <= 0)
		printf("VICTOIRE DU JOUEUR 1 !!\n");
	else
		printf("VICTOIRE DU JOUEUR 2 !!\n");

	return 0;
}
