
#include "contest.h"

#define float double

int N;
float V, A, C;
struct rob {
	float x,y;
	float vx, vy;
	int active;
	int n;
	rob * next;
};
struct dir {
	float x,y;
	int active;
	int n;
	dir * next;
};
	
rob rlist;
dir dlist;

main() {
char ch = 0;
float x,y;
int tcount;

	scanf("%d %lf %lf %lf", &N, &V, &A, &C);
	rob * rtail = &rlist;
	dir * dtail = &dlist;
	int rn = 0, dn = 0;

	while (scanf(" %c %lf %lf", &ch, &x, &y) == 3) 
		if (ch == 'R') {
			rob * r = new rob;
			r->x = x; r->y = y;
			r->active = 1;
			r->n = rn++;

			r->next = 0;
			rtail->next = r;
			rtail = r;
		} else {
			dir * r = new dir;
			r->x = x; r->y = y;
			r->active = 1;
			r->n = dn++;

			r->next = 0;
			dtail->next = r;
			dtail = r;
		}

	// scan and hist dirt and compute new: positions
	// scan and update

	for (tcount = 0; tcount <= N; tcount++) {

	for (rob * r = &rlist; r; r= r->next) if (r->active) {
#define within(a,b,w) \
	( (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) < w*w)

	
		// hit the dirt 
		{
		for (dir * d = &dlist; d; d=d->next) 
			if (d->active && within(r,d,C)) {
				d->active = 0;
				printf("Robot #%d picked up dirt pile #%d at time %d.\n",
					r->n, d->n, tcount);
			} }

		// try for other robots
		rob * rr;
		for (rr = &rlist; rr; rr=rr->next) if (rr->active && rr!=r) 
			if (within(r,rr,A)) {
				float dx = r->x - rr->x;
				float dy = r->y - rr->y;
				float norm = sqrt(dx*dx+dy*dy);
				r->vx = r->x + dx/norm * V;
				r->vy = r->y + dy/norm * V;
				printf("Robot #%d turns to avoid robot #%d at time %d.\n",
				// %f,%f\n",
					r->n, rr->n, tcount);
					//, r->x, r->y);
				break;
			}

		if (!rr) {
		// try dirt
		dir * d;
		float bestnorm = 999999999;
		for (d = &dlist; d; d=d->next) if (d->active) {
				float dx = r->x - d->x;
				float dy = r->y - d->y;
				float norm = sqrt(dx*dx+dy*dy);

				if (norm < bestnorm) {
					r->vx = r->x - dx/norm * V;
					r->vy = r->y - dy/norm * V;
					bestnorm  = norm;
				}
			}

		if (bestnorm >= 999999998 && !rr)  {r->active = 0;
			printf("Robot #%d stops at time %d.\n", r->n, tcount);
			}
		}
	}

	for (rob * r = &rlist; r; r= r->next) if (r->active) {
		r->x = r->vx, r->y = r->vy;
		//printf("%d now at %f,%f\n", r->n, r->x, r->y);
	}

	}

}
			

		

	
