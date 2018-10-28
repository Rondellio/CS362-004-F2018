/*
    case outpost:
      //set outpost flag
      state->outpostPlayed++;
			
      //discard card
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
*/

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
	int handStart = 0;
	int fail = 0;

	printf("Testing Outpost card...\n");

	for (p = 0; p < players; p++)
	{
		for (handStart = 1; handStart < maxHand; handStart++)
		{	
			printf("Testing player %d with %d cards in hand\n", p+1,  handStart);

			memset(&G, 23, sizeof(struct gameState));
			initializeGame(players, k, seed, &G);
			G.outpostPlayed = 0;
			G.whoseTurn = p;

			G.handCount[p] = handStart;
			memcpy(G.hand[p], k, sizeof(int)*handStart);
			
			cardEffect(outpost, 0, 0, 0, &G, handStart-1, 0);

			printf("Result outpost flag = %d, Expected 1", G.outpostPlayed);
			if (G.outpostPlayed == 1)
			{
				printf("---Success!\n");
			}
			else
			{
				printf("---Failed\n");
				fail = 1;
			}

			printf("Result hand count = %d, Expected %d", G.handCount[p], handStart-1);
			if (G.handCount[p] == handStart-1)
			{
				printf("---Success!\n");
			}
			else
			{
				printf("---Failed\n");
				fail = 1;
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
