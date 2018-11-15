/******************************************************************************************
 * Author: Ron Walters
 * ONID: waltersr
 * Assignment 4
 * Description: Adventurer Random Tests
 * ***************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

//Function to check the Adventurer card against random input values
int checkAdventurer(struct gameState *final){
	//Create a copy of the original game state for comparison
	struct gameState initial;
	memcpy (&initial, final, sizeof(struct gameState));

	int r;
	int failures = 0;

	//Get a count of the initial number of cards between the deck and discard pile
	int initialCards = initial.deckCount[initial.whoseTurn] + initial.discardCount[initial.whoseTurn];

	//Run the Adventurer card with the gamestate passed in
	r = cardEffect(adventurer, 0, 0, 0, final, final->handCount[final->whoseTurn]-1, 0); 

	//Add 2 cards to the initial number (for new treasures added)
	initial.handCount[initial.whoseTurn] += 2;

	//Verify card function ran correctly
	if (r != 0)
	{
		printf("Playing Adventure Card Failed\n");
		failures++;
	}
	
	//Compare deck count + discard count
	if (final->deckCount[final->whoseTurn] + final->discardCount[final->whoseTurn] != initialCards - 2)
	{
		printf("Final card counts don't match\n");
		failures++;
	}

	//Compare hand counts
	if (initial.handCount[initial.whoseTurn] != final->handCount[final->whoseTurn])
	{
		printf("Hand counts do not match\n");
		failures++;
	}
	
	//If any failures, return 1
	if (failures > 0)
	{
		return 1;
	}
	else
	{
		printf("PASSED\n");
		return 0;
	}

	return failures;
}

int main() {
	//Set random seed
	srand(time(NULL));

	//Initialize variables
	int i, n, p;
	int fails = 0;

	struct gameState G;

	printf("Testing adventurer\n");

	printf("RANDOM TESTS\n");

	//Run loop 5000 times to ensure coverage
	for (n = 0; n < 5000; n++)
	{
		//Create random gameState
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = rand() % 256;
		}

		//Select random player
		p = rand() % 2;
		G.whoseTurn = p;

		//Randomize deck and discard piles (half of max_deck size to ensure not larger than max_hand together)
		G.deckCount[p] = rand() % (MAX_DECK/2);
		G.discardCount[p] = rand() % (MAX_DECK/2);

		//Place 2 treasures in either deck or discard piles
		int treasureIn = 0;
		do
		{
			if (G.deckCount[p] > 0)
			{
				printf("Card added to deck: ");
				int treasure = rand() % 3;
				int position = rand() % G.deckCount[p];
				switch (treasure)
				{
					case 0:
						G.deck[p][position] = copper;
						printf("Copper\n");
						break;
					case 1:
						G.deck[p][position] = silver;
						printf("Silver\n");
						break;
					case 2:
						G.deck[p][position] = gold;
						printf("Gold\n");
						break;
				}
				treasureIn++;
			}	
			if (G.discardCount[p] > 0)
			{
				printf("Card added to discard: ");
				int treasure = rand() % 3;
				int position = rand() % G.discardCount[p];
				switch (treasure)
				{
					case 0:
						G.discard[p][position] = copper;
						printf("Copper\n");
						break;
					case 1:
						G.discard[p][position] = silver;
						printf("Silver\n");
						break;
					case 2:
						G.discard[p][position] = gold;
						printf("Gold\n");
						break;
				}
				treasureIn++;
			}
		} while (treasureIn < 2);

		//Randomize number of cards in hand, making sure 1 is in hand
		G.handCount[p] = rand() % (MAX_HAND - 1) + 1;

		//Keep track of number of fails
		fails += checkAdventurer(&G);
		printf("\n\n");
	}

	//Print results of tests
	if (fails == 0)
	{
		printf("ALL TESTS PASSED\n");
	}
	else
	{
		printf("FAILED %d OF %d TESTS\n", fails, n);
	}

	return 0;
}
