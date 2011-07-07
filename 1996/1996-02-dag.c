
#include "contest.h"

// map name -> file
struct namedef {
	char name[256];
	char file[256];
	namedef * next;
	int orig;
};


// list of entries
struct entry {
	char name[256];
	entry * next;
};

// map file -> list of entries
struct ofile {
	int used;
	char name[256];
	entry * p;
	ofile * next;
};

namedef * ndlist = 0;
ofile * oflist = 0;;

void hit(char * fname) {

	//printf("hitting %s\n", fname);

	// find it in linst;
	ofile * f;
	for (f = oflist; f; f=f->next)
		if (!strcmp(f->name, fname)) break;

	if (!f) exit(0);  
	if (f->used) return;
	//printf("%s not used\n", fname);
	f->used = 1;

	// scan uses, look up each, hit that file
	for (entry * en = f->p; en; en = en->next)  {
		//printf("entry %s\n", en->name);
		for (namedef * n = ndlist; n ; n=n->next)
			if (!strcmp(n->name, en->name)) {
				hit(n->file);
			}
		}
}

void show(ofile * f) {
	if (!f) return;
	show(f->next);
	if (f->used) puts(f->name);
}


main() {
char buf[256];

	while (1) {
		scanf("%s", buf);
		if (buf[0] == ';') break;
		namedef * nd = new namedef;
		strcpy(nd->name, buf);
		nd->next = ndlist;
		nd->orig = 1;
		ndlist = nd;
	}

	while (1) {
		if (scanf("%s", buf) != 1) break;

		ofile * of = new ofile;
		strcpy(of->name, buf);
		of->used =0;

		of->next = oflist;
		oflist = of;

		entry * elist = 0;
		while (1) {
			scanf("%s", buf);
			if (buf[0] == ';') break;
			int def = buf[0] == 'D';
			scanf("%s", buf);

			if (def) {
				// add of->name to the namedef list
				namedef *n;
				for (n = ndlist; n; n= n->next) 
					if (!strcmp(n->name, buf)) { strcpy(n->file, of->name);

						//printf("adding %s to %s\n", n->name, of->name);
						break;
					}
				if (!n) {
					n = new namedef;
					strcpy(n->name, buf);
					strcpy(n->file, of->name);
						//printf("Adding %s to %s\n", n->name, of->name);
					n->orig = 0;
					n->next = ndlist;
					ndlist = n;
				}
			} else {
				// add the use to the use list;
				entry * en = new entry;
				strcpy(en->name, buf);
				en->next = elist;
				elist = en;
			}
		}
		of->p = elist;
	}

	// dfs of tree
	for (namedef * n = ndlist; n; n= n->next)
		if (n->orig) hit(n->file);


	show(oflist);
}





