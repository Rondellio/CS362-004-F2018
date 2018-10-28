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
	int maxHand = 10;
	int curHand;
	int fail = 0;

	printf("Testing numHandCards...\n");	
	for (p = 0; p < players; p++)
	{
		for (curHand = 0; curHand < maxHand ; curHand++)
		{
			printf("Testing player %d with %d cards\n", p+1, curHand);

			memset(&G, 23, sizeof(struct gameState));
			initializeGame(players, k, seed, &G);
			G.whoseTurn = p;
			G.handCount[p] = curHand;

			int result = numHandCards(&G);

			printf("Hand result = %d, Expected = %d\n",result, curHand);

			if(result == curHand)
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
