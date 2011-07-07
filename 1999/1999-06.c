#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _word_t {
 char *text;
 int n_links; 
 struct _word_t **links;
 struct _word_t *next;
} word_t;

word_t *new_word(char *text) {
 word_t *word;
 word = calloc(1,sizeof(word_t));
 word->text = calloc(strlen(text)+1,sizeof(char));
 strcpy(word->text,text);
 word->n_links = 0;
 word->links = NULL;
 word->next = NULL;
 return word;
}


void wordlist_add(word_t **wordlist, word_t *word) {
 word->next = *wordlist;
 *wordlist = word;
 return;
}

void wordlist_print(word_t *wordlist) {
 while (wordlist != NULL) {
  printf("%s\n",wordlist->text);
  wordlist = wordlist->next;
 }
 return;
}

int words_count_differences(char *a, char *b) {
 int count = 0;
 while (a[0] != 0) {
  if (a[0] != b[0]) count++;
  a++;
  b++;
 }
 return count;
}

void word_add_link(word_t *word, word_t *link) {
 word->n_links ++;
 word->links = realloc(word->links, word->n_links * sizeof(word_t *));
 word->links[word->n_links - 1] = link;
 return; 
}

int linkup(word_t *wordlist) {
 word_t *word_a, *word_b;
 int links = 0;

 for (word_a = wordlist; word_a != NULL; word_a = word_a->next) {
  for (word_b = word_a->next; word_b != NULL; word_b = word_b->next) {
   if (words_count_differences(word_a->text,word_b->text) == 1) {
    word_add_link(word_a, word_b);
    word_add_link(word_b, word_a); 
    links ++;
   }
  }
 }
 return links;
}

typedef struct _ptrlist_t {
 word_t *ptr;
 struct _ptrlist_t *next;
} ptrlist_t;

int list_contains(ptrlist_t *list, word_t *item) {
 if (list == NULL) return 0;
 if (list->ptr == item) return 1;
 return list_contains(list->next, item);
}

int search_at_depth(word_t *src, word_t *dst, int target_depth, int current_depth, ptrlist_t *route) {
 int i;
 ptrlist_t fluffy;
 fluffy.ptr = src;
 fluffy.next = route;
 if (target_depth > current_depth) {
  for (i=0; i<src->n_links; i++) {
   if (
   src->next = src->links[i];
   if ((!list_contains(&fluffy,src->links[i])) && 
       (search_at_depth(src->links[i],dst,target_depth,current_depth+1,&fluffy)))  {
    printf("%s\n",src->text);
    return 1;
   }
  }
  return 0;
 }
 return (src == dst);
}

void search(word_t *src, word_t *dst) {
 int found =0;
 int depth;
 for (depth = 0; !found; depth++) 
  found = search_at_depth(src,dst,depth,0,NULL);
}

int main(int argc, char **argv) {
 char src[21], dst[21], word[21];
 word_t *src_ptr, *dst_ptr;
 int wordlen;
 word_t *wordlist = NULL;

 scanf("%s %s",src,dst);
 assert(strlen(src) == strlen(dst));
 wordlen = strlen(src);

 while (1 == scanf("%s",word)) 
  if (strlen(word) == wordlen) {
     word_t *the_word;
     the_word = new_word(word);
     if (0 == strcmp(word, src)) src_ptr = the_word;
     if (0 == strcmp(word, dst)) dst_ptr = the_word;
     wordlist_add(&wordlist,the_word);
  }

 wordlist_print(wordlist);
 printf("%u links made\n",linkup(wordlist));
 search(src_ptr, dst_ptr);
 printf("---\n");
 wordlist_print(src_ptr);
}

