#include <stdio.h>

#include "Moteur.h"
#include "Console.h"

int main(void)
{
	int enter;
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
		AfficherPlateau(plateau);
		// TODO: Mode console
	}
	else // Mode graphique
	{
		printf("Mode graphique \"Comming Soon!\"\n");
		// TODO: Mode graphique
	}

	return 0;
}
