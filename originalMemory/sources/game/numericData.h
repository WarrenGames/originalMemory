#ifndef GAMESTRUCTS_H
#define GAMESTRUCTS_H

#include <stdbool.h>

struct CardsNumericData
{
	unsigned int selectedCards[2];
	unsigned int currentStep;
	int *cardsIndexArray;//Valeurs (pointeur pour tableau à 1 dimension -> tableau linéarisé)
	bool *divulgedCards;//Voir si jumeaux trouvés (true si carte déjà révélées) (pointeur pour tableau à 1 dimension)
	unsigned int cardNumber;
	bool areCardsTwins;//Booléen definissant si les deux cartes retournées sont jumelles
	unsigned int whichTextToDisplay;//Voir defines de texte
	unsigned int triesNumber;
};

#endif//GAMESTRUCTS_H