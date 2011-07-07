#include "contest.h"



struct edge {
char a[130], b[130];
int dist;

	int used;
	int au,bu;
	edge * next;
};

edge * elist;

void usenode(char * n) {

	for (edge * p = elist; p; p=p->next) {
		if (!strcmp(n, p->a)) p->au = 1;
		if (!strcmp(n, p->b)) p->bu = 1;
	}
}

	void show(edge * e) {
		if (!e) return;
		show(e->next);
		if (e->used) printf("Clear %s to %s\n", e->a, e->b);
	}

main() {

// read file

// start with any node
/*
find shortest unused which connects to any used node.
add, repeat until edge foudn which connects used to unused.
*/

int set = 0;

	while (1) {
	elist = 0;

	char a[130], b[130];
	int val;

	while (1) {
		if (scanf("%s", a) != 1) return 0;
		if (a[0] == ';') break;
		scanf("%s %d", b, &val);

		edge * e = new edge;
		strcpy(e->a, a);
		strcpy(e->b, b);
		e->dist = val;
		e->au = e->bu = 0;
		e->next = elist;
		elist = e;
	}

	usenode(b);

	while (1) {
		edge * best = 0;
		int m = 2147483647;

		for(edge * e = elist; e; e=e->next) 
			if (e->au ^ e->bu) 
				if (e->dist < m) m = e->dist, best = e;

		if (!best) break;

		if (!best->au) usenode(best->a);
		if (!best->bu) usenode(best->b);
		best->used = 1;
	}

	printf("Set %d:\n", set++);
	show(elist);
	puts("");

	}
}
	

