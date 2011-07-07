#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define entity_is_switch(e) ((e > n_generators + n_customers) && (e <= n_generators + n_customers + n_switches))
#define entity_is_source(e) ((e <= n_generators))
#define switch_index(e) (e - n_generators - n_customers - 1)
#define min(a,b) (a < b ? a : b)

void swap_int(int *a, int *b) {int c; c = *a; *a = *b; *b = c; return; }

typedef struct _switch_t {
 int num;
 int load;
 int n_links;
 struct _switch_t **links;
 int *capacities;
} switch_t;  

typedef struct _switch_list_t {
 switch_t *a_switch;
 struct _switch_list_t *next;
} switch_list_t;

int route_contains(switch_list_t *route, switch_t *a_switch) {
 if (route == NULL) 
   return 0;
 if (route->a_switch == a_switch)
   return 1;
 return route_contains(route->next, a_switch);
}
 
switch_list_t *route_add(switch_list_t *route, switch_t *a_switch) {
 switch_list_t *an_item;
 an_item = malloc(sizeof(switch_list_t));
 an_item->a_switch = a_switch;
 an_item->next = route;
 return an_item;
}  

void route_print(switch_list_t *route) {
 printf("< ");
 while (route != NULL) {
  printf("%u ",route->a_switch->num);
  route = route->next;
 }
 printf(">");
} 

switch_t *switch_new(int num) {
 switch_t *my_switch;
 printf("switch_new(%u)\n",num);
 my_switch = malloc(sizeof(switch_t));
 my_switch->num = num;
 my_switch->n_links = 0;
 my_switch->links = NULL;
 my_switch->capacities = NULL;
 my_switch->load = 0;
 return my_switch;
}

void switch_add_link(switch_t *my_switch, switch_t *destination, int capacity) {
 printf("switches_add_link(%u,%u,%d)\n",my_switch->num,destination->num,capacity);
 my_switch->n_links ++;
 my_switch->links = realloc(my_switch->links, my_switch->n_links * sizeof(switch_t *));
 my_switch->capacities = realloc(my_switch->capacities, my_switch->n_links * sizeof(int));
 my_switch->links[my_switch->n_links - 1] = destination;
 my_switch->capacities[my_switch->n_links - 1] = capacity;
}

void switches_link(switch_t *switch_a, switch_t *switch_b, int capacity) {
 printf("switches_link(%u,%u,%u)\n",switch_a->num,switch_b->num,capacity);
 switch_add_link(switch_a, switch_b, capacity);
 switch_add_link(switch_b, switch_a, capacity); 
}


void switch_add_load(switch_t *my_switch, int load) {
 my_switch->load += load;
 printf("adjusting switch %u load by %d, new load is %d\n",my_switch->num,load,my_switch->load);
}

int satisfy(switch_t *start, int needed, switch_list_t *route, int indent) {
 int collected = 0;
 switch_t *site;
 int capacity, harvest, available, i, j;

 for (i=0; i<indent; i++) printf(" ");
 printf("satisfy(%u,%u,",start->num,needed);
 route_print(route);
 printf(");\n");

 for (i=0; i<start->n_links; i++) {
  printf("checking connection %u (to %u, capacity %u)\n",i,start->links[i]->num,start->capacities[i]);
  site = start->links[i];
  capacity = start->capacities[i];

  if ( (!route_contains(route, site)) && (capacity > 0)) {
    available = - site->load;
    if (available > 0) {
      harvest = min(available, min(needed, capacity)); 
      printf("harvesting %d units from %d\n",harvest,site->num);
      site->load += harvest;
      collected += harvest; 
      start->capacities[i] -= harvest;
      for (j=0; j<site->n_links; j++)
       if (site->links[j] == start) {
        site->capacities[j] += harvest;
        break;
       }
     }
      if (needed - collected > 0)
        collected += satisfy(site, min(needed - collected,capacity), route_add(route,start),indent+1);
  }
 }
 return collected;
}

int main(int argc, char **argv) {

 int n_generators, n_customers, n_switches, i, j, entity_a, entity_b, capacity;
 switch_t **switches;

 scanf("%u %u %u",&n_generators, &n_customers, &n_switches);

 /* create the switches */

 switches = malloc(n_switches * sizeof(switch_t *));
 for (i=0; i<n_switches; i++) switches[i] = switch_new(i);

 /* read in data structures */
 
 while (3 == scanf("%u %u %u",&entity_a, &entity_b, &capacity)) {

   printf("%u %u %u\n",entity_a, entity_b, capacity);

   if (entity_b > entity_a) 
      swap_int(&entity_a,&entity_b);

   assert(entity_is_switch(entity_a));

   if (entity_is_switch(entity_b)) {
     printf("connection between two switches (%d and %d)\n",switch_index(entity_a),switch_index(entity_b));
     switches_link(switches[switch_index(entity_a)],switches[switch_index(entity_b)],capacity);

   } else {
      if (entity_is_source(entity_b)) 
         capacity = -capacity;
      printf("connection between switch and a %s\n",(capacity < 0) ? "generator" : "customer");
      switch_add_load(switches[switch_index(entity_a)], capacity);
   }

 }

 /* */
 for (i=0; i<n_switches; i++) 
   printf(" switch %d has load %d \n",switches[i]->num,switches[i]->load);

 /* the algorithm */

 for (i=0; i<n_switches; i++) {  
   printf("checking satisfiability of switch %u\n",i);
   if (switches[i]->load < 0) 
     continue;
   if (switches[i]->load != satisfy(switches[i],switches[i]->load,NULL,0)) {
     printf("the demand cannot be met.\n");
     exit(0);
   }
 }

 printf("The demand can be met.\n");

}
