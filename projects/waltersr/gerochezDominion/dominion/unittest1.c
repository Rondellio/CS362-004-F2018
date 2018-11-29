#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int handPos, handCount;
	int players = 2;
	int p;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int trashFlag;
	int fail = 0;
	
	int maxHandCount = 5;
	
	printf("Testing discardCard...\n");
	for (p = 0; p < players; p++)
	{
		for (handCount = 1; handCount <= maxHandCount; handCount++)
		{
			for (handPos = 0; handPos < handCount; handPos++)
			{
				for (trashFlag = 0; trashFlag < 2; trashFlag++)
				{
					printf("Testing player %d at handPos %d out of %d and trash flag %d\n", p, handPos+1, handCount, trashFlag);

					memset(&G, 23, sizeof(struct gameState));
					initializeGame(players, k, seed, &G);
					G.handCount[p] = handCount;
					memcpy(G.hand[p], k, sizeof(int) * handCount);	//Fill hand with kingdom cards
					int curCard = G.hand[p][handPos];
					discardCard(handPos, p, &G, trashFlag);

					if (!trashFlag)
					{
						printf("Played cards = %d, Expected = 1\n", G.playedCardCount);
						if (G.playedCardCount == 1)
						{
							printf("---Success!\n");
						}
						else
						{
							printf("---Failed\n");
							fail = 1;
						}
					}
		
					printf("Remaining hand size = %d, expected %d", G.handCount[p], handCount-1);
			
					if(G.handCount[p] == handCount -1)
					{
						printf("---Sucess!\n");
					}
					else
					{
						printf("---Failed\n");
						fail = 1;
					}
					printf("Cards in discard pile = %d, expected %d", G.discardCount[p], 1);
					if (G.discardCount[p] == 1)
					{
						printf("---Sucess!\n");
					}
					else
					{
						printf("---Failed\n");
						fail = 1;
					}

					printf("old card in position = %d, newHand = ", curCard);
					int i;
					int err = 0;
					for (i = 0; i < handCount-1; i++)
					{
						printf("%d ", G.hand[p][i]);
						if (G.hand[p][i] == curCard)
						{
							err = 1;
						}

					}
					if (err == 0)
					{
						printf("---Success!\n");
					}
					else
					{
						printf("---Failed\n");
						fail = 1;
					}
		
					printf("\n\n");
					
				}
			}
		}
	}
					
	if (fail != 1)
	{
		printf("All tests succeeded!\n");
	}
	else
	{
		printf("Tests failed\n");
	}

	return 0;
} 
