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
	int discardStart = 1, deckStart;
	int handStart = 0;
	int fail = 0;

	printf("Testing Smithy card\n");

	for (p = 0; p < players; p++)
	{
		for (handStart = 1; handStart < maxHand; handStart++)
		{	
			printf("Testing player %d with %d cards in hand\n", p+1,  handStart);

			memset(&G, 23, sizeof(struct gameState));
			initializeGame(players, k, seed, &G);
			G.whoseTurn = p;

			G.handCount[p] = handStart;
			memcpy(G.hand[p], k, sizeof(int)*handStart);

			G.discardCount[p] = discardStart;
			memcpy(G.discard[p], k, sizeof(int)*discardStart);

			deckStart = cardsInDeck - handStart-discardStart;
			G.deckCount[p] = deckStart;
			memcpy(G.deck[p], k, sizeof(int)*deckStart);

			G.hand[p][handStart-1] = smithy; //Set smithy to last card
			
			cardEffect(smithy, 0, 0, 0, &G, handStart-1,0);

			printf("Result hand count = %d, Expected = %d", G.handCount[p], handStart+2); //Discarding smithy, so only add 2
			if (G.handCount[p] == handStart+2)
			{
				printf("---Success!\n");
			}
			else
			{
				printf("---Failed\n");
				fail = 1;
			}

			printf("Smithy top of discard pile?");
			if (G.discard[p][discardStart] == smithy)
			{
				printf("---Success!\n");
			}
			else
			{
				printf("---Failed\n");
				fail = 1;
			}
			
			printf("Result deck count = %d, Expected = %d", G.deckCount[p], deckStart - 3);
			if (G.deckCount[p] == deckStart-3)
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

	if (fail != 1)
	{
		printf("All tests passed!\n");
	}
	else
	{
		printf("Tests failed\n");
	}

	return 0;
}
