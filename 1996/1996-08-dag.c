#include "contest.h"

// funcs: match, 

struct cla {
	cla * one, *two;
	char op;
};

cla * rc() {
char ch;

	if (scanf(" %c", &ch) != 1) return 0;
	cla * k = new cla;
	if (ch == '(') {
		scanf(" %c", &ch);
		if (ch == ')') {
			k->op = 0;
			return k;
		}

		k->op = ch;
		k->one = rc();
		k->two = rc();
		scanf(" )");
	} else {
		k->op = ch;
		k->one = k->two = 0;
	}
	return k;
}
int match(cla * a, cla * b) ;

//struct sta {
	//int isgiven;
	//cla * c;
//} st[1000];
cla *  st[1000];

main() {

// read clauses

// take each
// find a match
// not->erro
// else continue

	int given = 1, firstgiven = 0;
	int i = 0;
	while (1) {
		cla * k = rc();
		if (!k) break;

		if (k->op == 0) given = 0, firstgiven = i;
		else {
			// add as given or statement
			st[i] = new cla;
			st[i] = k;
		//	st[i]->isgiven = given;
			i++;
		}
	}

	for (int j = firstgiven; j < i; j++) {
		// either match, or m.p

		int k;
		for (k = 0; k < j; k++)
			if (match(st[k], st[j])) break;
		if (k < j) continue;

		int ok = 0;
		for (int p = 0; p < j; p++) 
			if (st[p]->op == '>' && match(st[p]->two, st[j])) 
				for (int q = 0 ; q < j; q++)
					if (match(st[p]->one, st[q]))
						ok = 1;
		if (!ok) {
			printf("*Error in proof*\n");
			return 0;
			}
	}
	printf("*Proof OK*");
}

int match(cla * a, cla * b) {

	if (a->one) {
		if (!b->one) return 0;

		return (a->op == b->op && match(a->one, b->one) && match(a->two,
		b->two));
	} else
		return a->op == b->op && isupper(a->op);
}



