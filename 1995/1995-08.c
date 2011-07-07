#include <stdio.h>
#include <stdlib.h>

int num_rooms, num_party_room, a, b, i;

#define min(a,b) (a<b ? a : b)
typedef struct _link_t {
  struct _room_t *destination;
  struct _link_t *next;
} link_t;

typedef struct _room_t {
  int num;
  link_t *link;
  struct _room_t *next;
  unsigned int dist;
} room_t;

room_t *rooms = NULL;
room_t *possibilities = NULL;

room_t *new_room(int num) {
 room_t *room;
 room = (room_t *)malloc(sizeof(room_t));
 room->num = num;
 room->next = NULL;
 return room;
}

void roomlist_add(room_t **list, room_t *room) {
 room->next = *list;
 *list = room;
 return;
} 

void roomlist_remove(room_t **list, room_t *room) {
 if ((*list == NULL) || (room == NULL))
   return;
 if (*list == room) 
   *list = (*list)->next;
 else
   roomlist_remove(&((*list)->next),room);
}

room_t *roomlist_find(room_t *list, int num) {
 printf("find_room(%u)\n",num);
 while (list != NULL)
   if (list->num == num)
    return list;
   else
    list = list->next;
 return NULL;
}


void roomlist_print(room_t *list) {
 link_t *link;
 while (list != NULL) {
  printf("room %u, linked to:",list->num);
  link = list->link;
  while (link!=NULL) {
    printf(" %u",link->destination->num);
    link = link->next;
  }
  list = list->next;
  printf("\n"); 
 }
}

void roomlist_quickprint(room_t *list) {
 printf("< ");
 for ( ; list != NULL; list = list->next) printf("%u ",list->num);
 printf(">");
 return;
}

int roomlist_size(room_t *list) {
 return (list == NULL ? 0 : 1 + roomlist_size(list->next));
}

void add_link(room_t *src, room_t *dst) {
 link_t *newlink;
 printf("add_link(%u,%u)\n",src->num,dst->num);
 newlink = (link_t *)malloc(sizeof(link_t));
 newlink->destination = dst;
 newlink->next = src->link;
 src->link = newlink;
}

void connect_rooms(int src, int dst) {
 printf("connect_rooms(%u,%u)\n",src,dst);
 add_link(roomlist_find(rooms,src),roomlist_find(rooms,dst));
}

int depth_first(room_t *start, room_t *route) {
 int dist;
 room_t *node;
 link_t *link;

 printf("depth_first(%u,",start->num);
 roomlist_quickprint(route);
 printf(")\n");

 dist = roomlist_size(route); 
 start->dist = min(start->dist, dist);

 if (start->num == 0) {
  room_t *room;
  for (room = possibilities; room != NULL; room = room->next)
   if (NULL == roomlist_find(route,room->num)) 
     roomlist_remove(&possibilities, room);
  return;
 }

 node = new_room(start->num);
 node->next = route;
 
 for (link = start->link; link != NULL; link = link->next) {
   if (NULL == roomlist_find(route,link->destination->num))
     depth_first(link->destination, node);
 }
 free(node);
}

room_t *roomlist_find_closest(room_t *list) {
 printf("roomlist_find_closest(");
 roomlist_quickprint(list);
 printf(")\n");
 if (list->next == NULL) 
   return list;
 else {
   room_t *cdr;
   cdr = roomlist_find_closest(list->next);
   return (cdr->dist < list->dist ? cdr : list);
 }
}

int main(int argc, char **argv) {
  scanf("%u",&num_rooms);
  scanf("%u",&num_party_room);

  for (i=0; i<num_rooms; i++) {
   room_t *room_a, *room_b;
   room_a = new_room(i);
   room_b = new_room(i);
   roomlist_add(&rooms,room_a);
   roomlist_add(&possibilities,room_b);
  }

  while (EOF != scanf("%u %u",&a, &b))
	connect_rooms(b,a);

  printf("there are %u rooms and the party is in room number %u\n",num_rooms, num_party_room);
  printf("rooms list contains %u rooms: \n",roomlist_size(rooms));
  roomlist_print(rooms);
  printf("possibilities list contains %u rooms: \n", roomlist_size(possibilities));
  roomlist_print(possibilities);

  depth_first(roomlist_find(rooms,num_party_room),NULL);

  roomlist_remove(&possibilities,roomlist_find(possibilities,num_party_room));
  printf("the possibilities are: ");
  roomlist_quickprint(possibilities);
  printf("\n");

  printf("the answer is %u \n",roomlist_find_closest(possibilities)->num);
}
