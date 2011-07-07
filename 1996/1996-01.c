/* Tobin Fricke
   Programming Contest 1996, Problem 1 
   October 6, 2000
*/

int debug = 0;

typedef struct _card_t {
  char count;
  char rank;
  char suit;
  int flag;
} card_t;

/* return the number of combinations summing to 15 */

int combinations (card_t *hand, int first, int last, int sumleft) {
  if (first > last) 
    return (sumleft == 0);
  else
    return 
      combinations(hand,first+1,last,sumleft - hand[first].count) +  /* include */
	combinations(hand,first+1,last,sumleft); /* exclude */
}

int count_cards_with_rank(card_t *card, int rank) {
  int i;
  int count = 0;
  for (i=0; i<5; i++)
    count += (card[i].rank==rank);
  return count;
}

int score_hand(card_t *hand) {
  int score = 0;
  int i,j,in_run,first_rank,rank,combos,runs,foo;

  /* Score two points for each distinct combination of cards whose counts add up to 15 */

  combos = combinations(hand,0,4,15);
  if (debug) printf(" + %u for %u combinations summing to 15\n",2*combos,combos);
  score += 2 * combos;

  /* Score two points for each distinct pair of cards with the same rank */

  for (i=0; i<5; i++) 
    for (j=i+1; j<5; j++) 
      if (hand[i].rank == hand[j].rank) {
	score += 2;
	if (debug)
	  printf(" + 2 for pair (%u,%c) (%u,%c)\n",
	       hand[i].rank, hand[i].suit,
	       hand[j].rank, hand[j].suit);
      }

  
  /* Score one point for each card in each distinct maximal run of three or more cards */

  in_run = 0;

  for (rank=0; rank<13; rank++) {
    int foo;
    foo = count_cards_with_rank(hand,rank);
    if (foo) 
      runs *= foo;
    if (!foo ^ !in_run) {
      if (foo) {
	first_rank = rank;
	runs = foo;
	in_run = 1;
      } else {
	if (rank - first_rank >= 3) {
	  if (debug)
	    printf(" + awarding %u points for %u runs of length %u\n",
		   (rank - first_rank)*runs, runs, rank - first_rank);
	  score += runs*(rank - first_rank);
	}
	in_run = 0;
      }
    }
    
  }
  
  /* Score one point if the hand contains the jack of the same suit as the starter */
  
  for (i=0; i<4; i++) 
    if ((hand[i].rank == 11) && (hand[i].suit == hand[4].suit)) {
      score += 1;
      break;
   }

  return (score == 0 ? 19 : score);
}

int read_card(card_t *card) {
  unsigned char rank, suit;
  int bob;
  char fred[4];

  bob = scanf("%s",fred);

  if (fred[0] == '1') {
    rank = 10;
    suit = fred[2];
  } else {
    rank = fred[0];
    suit = fred[1];
  }

  switch (rank) {
  case 'A': card->count = 1; card->rank = 1; break;
  case 'J': card->count = 10; card->rank = 11; break;
  case 'Q': card->count = 10; card->rank = 12; break;
  case 'K': card->count = 10; card->rank = 13; break;
  default:  card->count = rank - '0'; card->rank = rank - '0'; break;
  }

  card->suit = suit;

  if (debug) 
    printf("read card (rank = %u, count = %u, suit = %c)\n",
	 card->rank, card->count, card->suit);
  
  return (bob == 1);
}


int main(int argc, char **argv) {
  card_t opponent[5];
  card_t dealer[5];
  card_t crib[5];
  card_t starter;
  int i;
  int hand = 0;
  
  while (1) {
    hand ++;
    for (i = 0; i < 4; i++) 
      if (!read_card(opponent + i)) 
	return 0;
    for (i = 0; i < 4; i++) 
      if (!read_card(dealer + i))
	return 0;
    for (i = 0; i < 4; i++) 
      if (!read_card(crib + i))
	return 0;
    if (!read_card(&starter))
	return 0;
    
    opponent[4] = starter;
    dealer[4] = starter;
    crib[4] = starter;
    
    printf("Hand %u:\n",hand);
    printf("Opponent's hand scores %u\n",score_hand(opponent));
    printf("Dealer's hand scores %u\n",score_hand(dealer));
    printf("Crib scores %u\n",score_hand(crib));
    printf("\n");
 
  }
}


