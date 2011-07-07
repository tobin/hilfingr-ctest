#include "contest.h"

char n[2000];
int best, beststt, besttail, bestk, bestsub;

main() { while (1) {
		if (scanf("%s", n) != 1) return 0;

	int stt, sub;
	int len = strlen(n);
		best = len;
		beststt = 0; besttail = 0; bestk = 1; bestsub = len;

	for (stt = 0; stt < len -1; stt++)
		for (sub = 1; sub <= len - stt; sub++) {
			// find out how often this sub recurs
			int k;

			for (k = 1; stt + sub*(k) <= len; k++) {
				int ok = 1;
				for (int j = 0; j < sub; j++)
					if (n[stt + j] != n[stt + sub*(k-1) + j]) ok = 0;
				if (!ok) break;
			}
			k--;
			int endpos = stt + sub*(k);

			int total = stt + sub + (len - endpos);
			//printf("Got total = %d (%d %d %d)\n", total, stt, sub, endpos);
			if (total < best
				|| (total == best
					&& (stt < beststt
						|| (stt == beststt && len-endpos < besttail) ) )
						) 
						{
				best = total;
				beststt = stt;
				besttail = len - endpos;
				bestk = k;
				bestsub = sub;
			//	puts("best");
			}
		}

	printf("%s = %.*s(%.*s)[%d]%s\n",
		n, beststt, n, bestsub, n+beststt, bestk, n+len-besttail);



}}


