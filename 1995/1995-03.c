

typedef struct _list_t {
  void *thing;
  list_t *next;
} list_t;

typedef struct _var_t {
  char name;
} var_t;

typedef struct _line_t {
  int num;
  int is_stop;
  list_t *assigns;
  list_t *depends;
  list_t *links;
} line_t;


list_t *list_newelement(void *item) {
 list_t *foo;
 foo = malloc(sizeof(list_t));
 foo->next = NULL;
 foo->thing = item;
 return foo;
}

void list_add(list_t **list, void *item) {
 list_t *foo;
 foo = list_newelement(item);
 item->next = *list;
 (*list) = item;
 return; 
}

line_t *line_new(int num) {
 line_t *foo;
 foo = malloc(sizeof(line_t));
 foo->num = num;
 foo->assigns = NULL;
 foo->depends = NULL;
 foo->links = NULL;
 foo->is_stop = 0;
 return foo;
}

void line_addlink(line_t *line, line_t *link) {
 list_add(line->links, link);
}

int main(int argc, char **argv) {

 line_t *lines; 
   
}
