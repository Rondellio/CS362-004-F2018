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
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "rngs.h"

//Function to run smithy card with random inputs
int checkSmithy(struct gameState *final, int handPos){

	//Create copy of original game state for comparison
	struct gameState initial;
	memcpy (&initial, final, sizeof(struct gameState));

	//Initialize variables
	int p = whoseTurn(final);
	int r, i;
	int failures = 0;

	//Run smithy card with random inputs
	r = cardEffect(smithy, 0, 0, 0, final, handPos, 0); 

	//Increase original game state cards by correct number from playing card
	//If deck has more than 3 cards, draw 3 cards from deck
	if (initial.deckCount[p] > 3)
	{
		for (i = 0; i < 3; i++)
		{
			initial.handCount[p]++;
			initial.hand[p][initial.handCount[p]-1] = initial.deck[p][initial.deckCount[p]-1];
			initial.deckCount[p]--;
		}
		initial.discardCount[p]++;
		initial.handCount[p]--;
	}
	//If deck has less than 3, but discard pile has more than 3, move discard to deck and draw 3
	else if (initial.discardCount[p] > 3)
	{
		memcpy(initial.deck[p], final->deck[p], sizeof(int) * initial.discardCount[p]);
		memcpy(initial.discard[p], final->discard[p], sizeof(int) * initial.discardCount[p]);
		for (i = 1; i <= 3; i++)
		{
			initial.hand[p][final->handCount[p]-i] = final->hand[p][final->handCount[p]-i];
			initial.handCount[p]++;
		}
		
		initial.deckCount[p] = initial.discardCount[p] - 3;
		initial.discardCount[p] = 1;
	}
		
	//Check to make sure smithy card ran
	if (r != 0)
	{
		printf("Playing Smithy Card Failed\n");
		failures++;
	}

	//Compare hand size to known hand size
	if (initial.handCount[p] != final->handCount[p])
	{
		printf("Hand counts do not match\n");
		failures++;
	}

	//Compare deck count to known deck count
	if (initial.deckCount[p] != final->deckCount[p])
	{
		printf("Deck count does not match\n");
		failures++;
	}

	//Compare discard count to known discard count
	if (initial.discardCount[p] != final->discardCount[p])
	{
		printf("Discard count does not match\n");
		failures++;
	}
	
	//If any failures, return 1, else print passed
	if (failures > 0)
	{
		return 1;
	}
	else
	{
		printf("PASSED");
		return 0;
	}

}

int main() {
	//Initialize random seed and variables
	srand(time(NULL));
	int i, n, p;
	int fails = 0;
	struct gameState G;
	
	printf("Testing Smithy Card\n");

	printf("RANDOM TESTS\n");


	//Run loop 2000 times to ensure coverage
	for (n = 0; n < 2000; n++)
	{
		//Create random gameState
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = rand() % 256;
		}

		//Set random player
		p = rand() % 2;
		G.whoseTurn = p;

		//Set hand, discard, deck, and played cards to random 
		G.deckCount[p] = rand() % (MAX_DECK/2);
		G.discardCount[p] = rand() % (MAX_DECK/2);
		G.handCount[p] = rand() % MAX_HAND;
		G.playedCardCount = rand() % (MAX_DECK/2);

		//If handcount is 0, change to 1 to prevent dividing by 0
		if (G.handCount[p] == 0)
		{
			G.handCount[p]++;
		}
		int handPos = rand() % G.handCount[p];

		//Keep track of number of fails
		fails += checkSmithy(&G, handPos);
	}
	printf("\n\n");

	//Print how many tests failed out of how many were ran
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
