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

//Function to run great hall with random inputs
int checkGreatHall(struct gameState *final, int handPos){

	//Create copy of original game state
	struct gameState initial;
	memcpy (&initial, final, sizeof(struct gameState));

	//Initialize variables
	int p = whoseTurn(final);
	int r;
	int failures = 0;

	//Run great hall card function with random inputs
	r = cardEffect(great_hall, 0, 0, 0, final, handPos, 0); 

	//Draw a card to copy of game state
	//If deck has cards left, draw from deck
	if (initial.deckCount[p] > 0)
	{
		initial.hand[p][initial.handCount[p]] = initial.deck[p][initial.deckCount[p]-1];
		initial.deckCount[p]--;
	
	}
	//otherwise, put discard pile into deck and draw a card
	else if (initial.discardCount[p] > 0)
	{
		memcpy(initial.deck[p], final->deck[p], sizeof(int) * initial.discardCount[p]);
		memcpy(initial.discard[p], final->discard[p], sizeof(int) * initial.discardCount[p]);
		initial.hand[p][final->handCount[p]-1] = final->hand[p][final->handCount[p]-1];
		initial.deckCount[p] = initial.discardCount[p] - 1;
		initial.discardCount[p] = 0;
	}
	
	//Increase number of actions (due to card)
	initial.numActions++;
		
	//Make sure that great hall card ran correctly
	if (r != 0)
	{
		printf("Playing Great Hall Card Failed\n");
		failures++;
	}
	
	//Compare number of actions
	if (initial.numActions != final->numActions)
	{
		printf("Number of actions does not match\n");
		failures++;
	}
	
	//Compare hand counts
	if (initial.handCount[p] != final->handCount[p])
	{
		printf("Number of cards in hand does not match\n");
		failures++;
	}

	//Compare deck counts
	if (initial.deckCount[p] != final->deckCount[p])
	{
		printf("Number of cards in deck does not match\n");
		failures++;
	}

	//Compare discard counts
	if (initial.discardCount[p] != final->discardCount[p])
	{
		printf("Number of cards in discard does not match\n");
		failures++;
	}
	
	//Return whether any tests failed or not
	if (failures > 0)
	{
		return 1;
	}
	else
	{
		printf("PASSED\n");
		return 0;
	}
}

int main() {
	//Initialize random seed and variables
	srand(time(NULL));
	int i, n, p;
	int fails = 0;
	struct gameState G;
	
	printf("Testing Great Hall Card\n");

	printf("RANDOM TESTS\n");


	//Loop 2000 times to ensure full coverage
	for (n = 0; n < 2000; n++)
	{
		//Create random game state
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = rand() % 256;
		}
		
		//Select random player
		p = rand() % 2;
		G.whoseTurn = p;

		//Randomize deck, hand, discard and played piles. 
		G.deckCount[p] = rand() % (MAX_DECK/2);
		G.discardCount[p] = rand() % (MAX_DECK/2);
		G.handCount[p] = rand() % MAX_HAND;
		G.playedCardCount = rand() % (MAX_DECK/2);

		//Randomize number of actions;
		G.numActions = rand() % 10;
		
		//Make sure that there is 1 item in hand to prevent dividing by 0
		if (G.handCount[p] == 0)
		{
			G.handCount[p]++;
		}
		int handPos = rand() % G.handCount[p];

		//Keep track of number of fails
		fails += checkGreatHall(&G, handPos);
	}
	printf("\n\n");

	//Print results out to screen of failed tests
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
