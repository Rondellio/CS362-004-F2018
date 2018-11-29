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
	int treasureCards = 3;
	int i;
	int discardStart, deckStart;
	int handStart = 0;
	int treasureStart = 0;
	int fail = 0;
	

	printf("Testing Adventurer Cards...\n");
	for (p = 0; p < players; p++)
	{
		for (deckStart = 0; deckStart < cardsInDeck-handStart ; deckStart++)
		{
			for (handStart = 0; handStart < maxHand; handStart++)
			{
				printf("Testing player %d with %d cards in deck and %d cards in hand\n", p+1, deckStart, handStart);

				memset(&G, 23, sizeof(struct gameState));
				initializeGame(players, k, seed, &G);
				G.whoseTurn = p;
	
				//Setup initial piles
				discardStart = cardsInDeck - deckStart - handStart;
				G.deckCount[p] = deckStart;
				memcpy(G.deck[p], k, sizeof(int) * deckStart);
				G.handCount[p] = handStart;
				memcpy(G.hand[p], k, sizeof(int) * handStart);
				G.discardCount[p] = discardStart;
				memcpy(G.discard[p], k, sizeof(int) * discardStart);

				//start with coppers mixed between deck and discard piles
				for (i = 0; i < treasureCards; i++)
				{
					if (G.deckCount[p] < 1)
					{
						G.discard[p][i] = copper;
					}
					else if (G.deckCount[p] < 3)
					{
						G.deck[p][i] = copper;
						G.discard[p][i] = copper;
					}
					else
					{
						G.deck[p][i] = copper;
					}
				}

				G.hand[p][handStart] = adventurer;
				G.coins = treasureStart;
				cardEffect(adventurer, 0, 0, 0, &G, handStart,0);
				updateCoins(p, &G, 0);
				
				//Compare coins before and after
				printf("Copper--Result coins = %d, Expected coins = %d", G.coins, 2*1);
				if (G.coins == 2*1)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}
				
				//Compare hand size before and after
				printf("Copper--Result hand size = %d, Expected hand size = %d", G.handCount[p], handStart+2);
				if (G.handCount[p] == handStart+2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Compare deck and discard size before and after
				printf("Copper--Remaining cards between deck and discard = %d, Expected = %d", G.discardCount[p]+G.deckCount[p], cardsInDeck-handStart-2);
				if (G.discardCount[p]+G.deckCount[p] == cardsInDeck-handStart-2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}				

				//Silvers
				discardStart = cardsInDeck - deckStart - handStart;
				G.deckCount[p] = deckStart;
				memcpy(G.deck[p], k, sizeof(int) * deckStart);
				G.handCount[p] = handStart;
				memcpy(G.hand[p], k, sizeof(int) * handStart);
				G.discardCount[p] = discardStart;
				memcpy(G.discard[p], k, sizeof(int) * discardStart);

				//start with silvers mixed between deck and discard piles
				for (i = 0; i < treasureCards; i++)
				{
					if (G.deckCount[p] < 1)
					{
						G.discard[p][i] = silver;
					}
					else if (G.deckCount[p] < 3)
					{
						G.deck[p][i] = silver;
						G.discard[p][i] = silver;
					}
					else
					{
						G.deck[p][i] = silver;
					}
				}
				
				G.hand[p][handStart] = adventurer;
				G.coins = treasureStart;
				cardEffect(adventurer, 0, 0, 0, &G, handStart,0);
				updateCoins(p, &G, 0);

				//Compare coins before and after
				printf("Silver--Result coins = %d, Expected coins = %d", G.coins, 2*2);
				if (G.coins == 2*2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Compare hand size before and after
				printf("Silver--Result hand size = %d, Expected hand size = %d", G.handCount[p], handStart+2);
				if (G.handCount[p] == handStart+2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Compare deck and discard size before and after
				printf("Silver--Remaining cards between deck and discard = %d, Expected = %d", G.discardCount[p]+G.deckCount[p], cardsInDeck-handStart-2);
				if (G.discardCount[p]+G.deckCount[p] == cardsInDeck-handStart-2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}				
				
				//Golds
				discardStart = cardsInDeck - deckStart - handStart;
				G.deckCount[p] = deckStart;
				memcpy(G.deck[p], k, sizeof(int) * deckStart);
				G.handCount[p] = handStart;
				memcpy(G.hand[p], k, sizeof(int) * handStart);
				G.discardCount[p] = discardStart;
				memcpy(G.discard[p], k, sizeof(int) * discardStart);

				//start with silvers mixed between deck and discard piles
				for (i = 0; i < treasureCards; i++)
				{
					if (G.deckCount[p] < 1)
					{
						G.discard[p][i] = gold;
					}
					else if (G.deckCount[p] < 3)
					{
						G.deck[p][i] = gold;
						G.discard[p][i] = gold;
					}
					else
					{
						G.deck[p][i] = gold;
					}
				}

				G.hand[p][handStart] = adventurer;
				G.coins = treasureStart;
				cardEffect(adventurer, 0, 0, 0, &G, handStart, 0);
				updateCoins(p, &G, 0);

				//Compare coins before and after
				printf("Gold--Result coins = %d, Expected coins = %d", G.coins, 2*3);
				if (G.coins == 2*3)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Compare hand size before and after
				printf("Gold--Result hand size = %d, Expected hand size = %d", G.handCount[p], handStart+2);
				if (G.handCount[p] == handStart+2)
				{
					printf("---Success!\n");
				}
				else
				{
					printf("---Failed\n");
					fail = 1;
				}

				//Compare deck and discard size before and after
				printf("Gold--Remaining cards between deck and discard = %d, Expected = %d", G.discardCount[p]+G.deckCount[p], cardsInDeck-handStart-2);
				if (G.discardCount[p]+G.deckCount[p] == cardsInDeck-handStart-2)
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

	if (fail != 1)
	{
		printf("All tests passed!\n");
	}
	else
	{
		printf("Tests Failed\n");
	}

	return 0;
} 
