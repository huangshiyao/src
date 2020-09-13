#ifndef BASEFUNC
#define BASEFUNC

typedef void *list;

list list_create();
void list_destroy(list node, void (*destroy)(void *data));
void list_add_next(list node, void *data);
void list_add_prev(list node, void *data);
void *list_del(list node);
//list list_find_open(list node, bool (*find)(void *data, void *key), void *key);
list list_next(list node);
list list_prev(list node);
void *list_open(list node);
void list_close(list node);
int list_count(list node);

struct datetime_t
{
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int sec;
};

int chk_datetime(struct datetime_t *datetime);

#endif /*BASEFUNC*/
