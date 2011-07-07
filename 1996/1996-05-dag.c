#include "contest.h"

void conv(int i) {
	if (i == 0) return;

	int d = i/3, r = i%3;
if (r < 0) r += 3, d -= 1;
	switch (r) {
	 case 0: conv(d); printf("0"); return;
	 case 1: conv(d); printf("1"); return;
	 case 2: conv(d+1); printf("-"); return;
	 }
}

main() {
int i;

	while(scanf("%d", &i) == 1) 
		if (i == 0) printf("0 = 0 GQ\n");
		else {
			printf("%d = ", i);
			conv(i);
			printf(" GQ\n");
		}
}

	
