#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int players = 2;
	int p;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHand = 5;
	int cardsInDeck = 10;
	int deckStart;
	int handStart = 0;
	int fail = 0;
	int actions;

	printf("Testing Village card\n");

	for (p = 0; p < players; p++)
	{
		for (handStart = 1; handStart < maxHand; handStart++)
		{	
			for (actions = 0; actions < 2; actions++)
			{
				printf("Testing player %d with %d cards in hand and %d initial actions\n", p+1,  handStart, actions);

				memset(&G, 23, sizeof(struct gameState));
				initializeGame(players, k, seed, &G);
				G.whoseTurn = p;

				G.handCount[p] = handStart;
				memcpy(G.hand[p], k, sizeof(int)*handStart);
			
				deckStart = cardsInDeck-handStart;
				G.deckCount[p] = deckStart;
				memcpy(G.deck[p], k, sizeof(int)*deckStart);

				G.numActions = actions;
			
				cardEffect(village, 0, 0, 0, &G, handStart-1, 0);

				//Check hand size (should be the same due to drawing and discarding 1)
				printf("Result hand size = %d, Expected = %d", G.handCount[p], handStart);
				if (G.handCount[p] == handStart)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Check deck size
				printf("Result deck size = %d, Expected = %d", G.deckCount[p], deckStart-1);
				if(G.deckCount[p] == deckStart-1)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Check number of actions
				printf("Result actions = %d, Expected = %d", G.numActions, actions+2);
				if (G.numActions == actions+2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}
				printf("\n");
			}
		}
	}

	if (fail == 0)
	{
		printf("All tests passed!\n");
	}
	else
	{
		printf("Tests failed\n");
	}

	return 0;
}
