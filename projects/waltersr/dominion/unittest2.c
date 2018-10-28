#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int provinces;
	int emptySupplies;
	int players = 2;
	int i;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int fail = 0;
	
	printf("Testing isGameOver...\n");
	for (provinces = 10; provinces >=0; provinces--)
	{
		for (emptySupplies = 0; emptySupplies < 25; emptySupplies++)
		{

			printf("Testing with %d provinces remaining and %d empty supply piles\n", provinces, emptySupplies);

			memset(&G, 23, sizeof(struct gameState));
			initializeGame(players, k, seed, &G);
			G.supplyCount[province] = provinces;

			for (i = 0; i < emptySupplies; i++)
			{
				G.supplyCount[i] = 0;
			}

			int r = isGameOver(&G);
				
			if (provinces == 0)
			{
				int expected = 1;
				printf("Game over result - provinces");
				
				if(r == expected)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}
			}
			else if (emptySupplies >= 3)
			{
				int expected = 1;
				printf("Game over result - Supplies");

				if(r == expected)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}
			}
			else
			{
				int expected = 0;
				printf("Game not over");

				if(r == expected)
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
	}
	
	if (fail == 0)
	{
		printf("All tests passed!\n");
	}
	else
	{
		printf("Tests Failed\n");
	}

	return 0;

}
