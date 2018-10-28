#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int players = 2;
	int fails = 0;
	int testCounts = 0;
	int p, i;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHand = 5;
	int curHand;
	int curDiscard;
	int curDeck;

	int curses[maxHand];
	int estates[maxHand];
	int duchys[maxHand];
	int provinces[maxHand];
	int great_halls[maxHand];
	int gardens2[maxHand];

	//Arrays filled with specific cards
	for (i = 0; i < maxHand; i++)
	{
		curses[i] = curse;
		estates[i] = estate;
		duchys[i] = duchy;
		provinces[i] = province;
		great_halls[i] = great_hall;
		gardens2[i] = gardens;
	}

	printf("Testing scoreFor...\n");	
	for (p = 0; p < players; p++)
	{
		for (curHand = 0; curHand < maxHand; curHand++)
		{	
			for (curDiscard = 0; curDiscard < maxHand; curDiscard++)
			{
				for (curDeck = 0; curDeck < maxHand; curDeck++)
				{
					memset(&G, 23, sizeof(struct gameState));
					initializeGame(players, k, seed, &G);
	
					printf("Testing player %d with %d cards in hand, %d cards in discard, and %d cards in deck\n", p+1, curHand, curDiscard, curDeck);
					//Test for Curses
					printf("Testing curses..\n");
					G.handCount[p] = curHand;
					G.discardCount[p] = curDiscard;
					G.deckCount[p] = curDeck;

					//Set correct number of curses in each position
					memcpy(G.hand[p], curses, sizeof(int)*curHand);
					memcpy(G.discard[p], curses, sizeof(int)*curDiscard);
					memcpy(G.deck[p], curses, sizeof(int)*curDeck);

					int res = scoreFor(p, &G);
					printf("Resultant score = %d, Expected score = %d ", res, (curHand+curDiscard+curDeck)*-1);

					if (res == (curHand + curDiscard + curDeck)*-1)
					{
						printf("---Test Passed\n");
					}
					else
					{
						printf("---Test Failed!\n");
						fails++;
					}
					testCounts++;
	
					//Test for estates
					printf("Testing estates..\n");
					memcpy(G.hand[p], estates, sizeof(int)*curHand);
					memcpy(G.discard[p], estates, sizeof(int)*curDiscard);
					memcpy(G.deck[p], estates, sizeof(int)*curDeck);
					
					res = scoreFor(p, &G);
					printf("Resultant score = %d, Expected score = %d", res, (curHand+curDiscard+curDeck)*1);

					if (res == (curHand + curDiscard + curDeck)*1)
					{
						printf("---Test Passed\n");
					}
					else
					{
						printf("---Test Failed!\n");
						fails++;
					}
					testCounts++;

					//Test for duchys
					printf("Testing duchys..\n");
					memcpy(G.hand[p], duchys, sizeof(int)*curHand);
					memcpy(G.discard[p], duchys, sizeof(int)*curDiscard);
					memcpy(G.deck[p], duchys, sizeof(int)*curDeck);
					
					res = scoreFor(p, &G);
					printf("Resultant score = %d, Expected score = %d", res, (curHand+curDiscard+curDeck)*3);

					if (res == (curHand + curDiscard + curDeck)*3)
					{
						printf("---Test Passed\n");
					}
					else
					{
						printf("---Test Failed!\n");
						fails++;
					}
					testCounts++;

					//Test for provinces
					printf("Testing provinces..\n");
					memcpy(G.hand[p], provinces, sizeof(int)*curHand);
					memcpy(G.discard[p], provinces, sizeof(int)*curDiscard);
					memcpy(G.deck[p], provinces, sizeof(int)*curDeck);
					
					res = scoreFor(p, &G);
					printf("Resultant score = %d, Expected score = %d", res, (curHand+curDiscard+curDeck)*6);

					if (res == (curHand + curDiscard + curDeck)*6)
					{
						printf("---Test Passed\n");
					}
					else
					{
						printf("---Test Failed!\n");
						fails++;
					}
					testCounts++;

					//Test for great halls
					printf("Testing great halls..\n");
					memcpy(G.hand[p], great_halls, sizeof(int)*curHand);
					memcpy(G.discard[p], great_halls, sizeof(int)*curDiscard);
					memcpy(G.deck[p], great_halls, sizeof(int)*curDeck);
					
					res = scoreFor(p, &G);
					printf("Resultant score = %d, Expected score = %d", res, (curHand+curDiscard+curDeck)*1);

					if (res == (curHand + curDiscard + curDeck)*1)	
					{
						printf("---Test Passed\n");
					}
					else
					{
						printf("---Test Failed!\n");
						fails++;
					}
					testCounts++;

					//Test for gardens
					printf("Testing gardens..\n");
					memcpy(G.hand[p], gardens2, sizeof(int)*curHand);
					memcpy(G.discard[p], gardens2, sizeof(int)*curDiscard);
					memcpy(G.deck[p], gardens2, sizeof(int)*curDeck);
					
					res = scoreFor(p, &G);
					printf("Resultant score = %d, Expected score = %d", res, (curHand+curDiscard+curDeck)/10);

					if (res == (curHand + curDiscard + curDeck)/10)
					{
						printf("---Test Passed\n");
					}
					else
					{
						printf("---Test Failed!\n");
						fails++;
					}
					testCounts++;
				
					printf("\n");
				}
			}
					

		}
	}

	if (fails < 1)
	{
		printf("All tests passed!\n");
	}
	else
	{
		printf("%d/%d Tests Failed\n", fails, testCounts);
	}

	return 0;
} 
