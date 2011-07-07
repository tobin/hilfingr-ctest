#include "contest.h"

struct card {
	int suit;
	int rank;
	int count;
};

card oppo[5], deal[5], crib[5], start;

int s1(card c[5]) {
int tot = 0;

	// combos
	#define flip(k) for (int k = 0; k < 2; k++)
	flip(l0)
	flip(l1)
	flip(l2)
	flip(l3)
	flip(l4)
		if (l0*c[0].count + l1*c[1].count + l2*c[2].count + l3*c[3].count + l4*c[4].count 
			== 15) tot += 2;

	// pair
	for (int p = 0; p < 5; p++)
		for (int q = 0; q < p; q++)
			if (c[p].rank == c[q].rank) tot += 2;
	
	// runs
	int prev = 0, len = 0, sum = 0, mult = 0;
	for (int s = 0; s <= 13; s++) 
		if ((sum = ((c[0].rank == s) + 
			(c[1].rank == s )+
			(c[2].rank == s )+
			(c[3].rank == s )+
			(c[4].rank == s) )) )
			if (prev) len++, mult *= sum; 
			else prev = 1, len = 1, mult = sum;
		else
			if (prev)
				tot += (len >= 3? len*mult:0), prev = 0;

	if (
	c[0].suit == start.suit && c[0].rank == 10 ||
	c[1].suit == start.suit && c[1].rank == 10 ||
	c[2].suit == start.suit && c[2].rank == 10 ||
	c[3].suit == start.suit && c[3].rank == 10 )
		tot += 1;

	return tot;
}


void rc(card & c) {
char r,s;
char buf[10];
char * sui = "CDHS";
char * ran = "A234567891JQK";

	if (scanf("%s",buf) != 1) exit(0);
	if (buf[0] == '1') r = '1', s = buf[2];
	else r = buf[0], s = buf[1];

	c.suit = strchr(sui, s) - sui;
	c.rank = strchr(ran, r) - ran;
	c.count = c.rank >= 10 ? 10 : c.rank + 1;
	//printf("%s gets %d %d %d\n", buf, c.suit, c.rank, c.count);
}

main() {
int n = 0;
int i;

	while (1) {
	for (i = 0; i< 4; i++) rc(oppo[i]);
	for (i = 0; i< 4; i++) rc(deal[i]);
	for (i = 0; i< 4; i++) rc(crib[i]);
	rc(start);

	oppo[4] = start;
	deal[4] = start;
	crib[4] = start;

	printf("Hand %d:\n", n++);
	int 
	sc = s1(oppo);
	printf("Opponent's hand scores %d\n", sc ? sc : 19);
	sc = s1(deal);
	printf("Dealer's hand scores %d\n", sc ? sc : 19);
	sc = s1( crib);
	printf("Crib scores %d\n\n", sc ? sc : 19);
	}
}

