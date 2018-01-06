#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Moteur.h"
#include "Console.h"

// Fonction prépocesseur pour changer couleur du texte en console
// Source: https://openclassrooms.com/courses/des-couleurs-dans-la-console-linux
#define couleur(param) printf("\033[%sm", param)

void AfficherPlateau(Case tab[][10])
{
	int x,y;

	for (y = -1; y < 10; y++)
	{
		for (x = -1; x < 10; x++)
		{
			if (y == -1 && x >= 0)
				printf("%d", x);
			else if (x == -1 && y >= 0)
				printf("%d", y);
			else
			{
				if (tab[x][y].joueur == 1)
				couleur("31");
				else if (tab[x][y].joueur == 2)
					couleur("34");
				else
					couleur("37");

				if (tab[x][y].selected == 1)
					couleur("35");

				if (tab[x][y].type == -1)
					printf(" ");
				else if (tab[x][y].type == 3)
					printf("D");
				else if (tab[x][y].type == 2)
					printf("L");
				else if (tab[x][y].type == 1)
					printf("S");
				else if (tab[x][y].type == -2)
					printf("P");
				else
					printf(".");
			}
			printf(" ");
			couleur("0");
		}
		printf("\n");
	}
}

void SelectionPion(Case tab[][10], int joueur)
{ 
	int xD = -5, yD = -5, xA = -5, yA = -5;
	int enter = 0;
	int nbCoups = 0; // Compteur de coups (afin de savoir si un ShingShang a lieu)
	int Shing = 0;
	int nbPions = 0; // Nombre de pion différents joués

	Coor PionsJoue[10]; // Tableau des pions joué (permet de ne pas rejouer le meme pion apres un shingshang)
	InitPionsJoue(PionsJoue);

	do{
		int nbSauts = 0;
		Coor tbDpl[8]; // Tableau qui contiendra les déplacement possibles (uniquement en saut pour les enchaîner)
		initDpTab(tbDpl);

		AfficherPlateau(tab);

		if (xD == -5 || Shing == 1)  // Si different de -5 c'est qu'un deuxieme coup est joué, donc le meme pion est utilisé
		{
			if (Shing == 1)
			{
				printf("\n");
				printf("Vous pouvez rejouer mais avec un pion diffrent !\n");
			}
			printf("Entrez le pion à sélectionner\n");
			getPion(tab, PionsJoue, joueur, &xD, &yD);
		}
		else
		{ // Le pion se trouve maintenant sur la case d'arrivée
			xD = xA;
			yD = yA;
		}
		Shing = 0;

		printf("\nEntrez la case de destination\n");
		getCase(tab, joueur, xD, yD, &xA, &yA);

		Deplacement(&tab[xD][yD], &tab[xA][yA]);
		nbCoups++;

		if (nbCoups > 1) // Si il y a un ShingShang
		{
			Shing = TestShingShang(tab, xD, yD, xA, yA); // Test si le pion sauter est à manger
			if (Shing)
			{
				printf("OK\n");
				if (joueur == 1)
					MangerPion(&tab[joueur1.posSaut.x][joueur1.posSaut.y]);
				else
					MangerPion(&tab[joueur2.posSaut.x][joueur2.posSaut.y]);

				Coor c;
				c.x = xA;
				c.y = yA;
				PionsJoue[nbPions] = c;
				nbPions++;
			}
		}

		AfficherPlateau(tab);
		enter = 0;

		// Vérif pour rejouer:
		if (ExisteDeplacement(tab, &tab[xA][yA], tbDpl, &nbSauts) == 1 && Shing != 1)
		{
			printf("Il existe %d déplacement(s) possible(s)\n", nbSauts);
			int i;
			for (i = 0; i < nbSauts; i++)
			{
				printf(" (%d;%d) ", tbDpl[i].x, tbDpl[i].y);
			}
			printf("\n\n");

			printf("Voulez-vous rejouer ? (1/0)\n");
			scanf("%d", &enter);
		}
	} while (enter == 1 || Shing == 1);
}

void getPion(Case tab[][10], Coor Pions[10], int joueur, int *x, int *y)
{
	do{
		printf("Entrez x:\n");
		scanf("%d", x);
		printf("Entrez y:\n");
		scanf("%d", y);
	} while (testPion(tab, Pions, joueur, *x, *y) == 0);
}

int testPion(Case tab[][10], Coor Pions[10], int joueur, int x, int y)
{
	int retour = 0;
	int identique = 0;

	int i;
	for (i = 0; i < 10; i++)
	{
		if (Pions[i].x == x && Pions[i].y == y)
			identique = 1;
	}

	if (tab[x][y].joueur == joueur && identique == 0)
		retour = 1;

	return retour;
}

void getCase(Case tab[][10], int joueur, int xD, int yD, int *xA, int *yA)
{
	int  dpl = 0;
	do{
		printf("Entrez x:\n");
		scanf("%d", xA);
		printf("Entrez y:\n");
		scanf("%d", yA);

		dpl = DeplacementPossible(tab, &tab[xD][yD], &tab[*xA][*yA]);
	} while (dpl == 0);

	if (dpl == 2) // Si un Dragon est sur portail
	{
		if (joueur == 1)
			joueur1.portail = 1;
		else
			joueur2.portail = 1;
	}
}

void initDpTab(Coor tab[8])
{
	int i;
	Coor c;

	for (i = 0; i < 8; i++){
		c.x = 0;
		c.y = 0;
		tab[i] = c;
	}
}

void getEnter(int *enter)
{
	char e;
	do{
		scanf("%s", &e);
	} while (isdigit(e) == 0);

	*enter = (int) e;
}

void InitPionsJoue(Coor tab[10])
{
	Coor c;
	c.x = -1;
	c.y = -1;

	int x;
	for (x = 0; x < 10; x++)
		tab[x] = c;
}