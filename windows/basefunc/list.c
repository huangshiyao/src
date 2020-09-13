#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

//#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define container_of(ptr, type, member) ({\
const typeof(((type *)0)->member) *__mptr = (ptr);\
(type *)((char *)__mptr - offsetof(type,member));})

struct list
{
	pthread_rwlock_t lock;
	struct list *const head;
	struct list *next;
	struct list *prev;
};

struct list_node
{
	void *data;
	struct list ls;
};

struct list_head
{
	sig_atomic_t count;
	struct list ls;
};

static int list_node_trylock(struct list *ls, int n, unsigned int try_count, bool wrflag)
{
	unsigned int i, j, t, n0;
	struct list *p;
	int rval;

	t=(time(NULL)%100)*100;
	n0 = abs(n);
	for (j = 0; try_count != 0 ? j < try_count : true; j++)
	{
		p = ls;
		for (i = 0; n0 != 0 ? i < n0 : true; i++)
		{
			if (wrflag)
				rval = pthread_rwlock_trywrlock(&p->lock);
			else
				rval = pthread_rwlock_tryrdlock(&p->lock);
			if (EBUSY == rval)
				break;
			if (rval)
				abort();
			if (n >= 0)
				p = p->next;
			else
				p = p->prev;
			if (p == ls)
				break;
		}
		if (0 == rval)
			break;
		for (; i != 0; i--)
		{
			if (n >= 0)
				p = p->prev;
			else
				p = p->next;
            if (pthread_rwlock_unlock(&p->lock))
				abort();
		}
		for (i = 0; i < t; i++);
	}
	if (try_count != 0 && j == try_count)
		return -1;
	return 0;
}

static void list_node_unlock(struct list *ls, int n)
{
	unsigned int i, n0;
	struct list *p;

	n0 = abs(n);
	p = ls;
	for (i = 0; n0 != 0 ? i < n0 : true; i++)
	{
        if (pthread_rwlock_unlock(&p->lock))
			abort();
		if (n >= 0)
			p = p->next;
		else
			p = p->prev;
		if (p == ls)
			break;
	}
}

struct list *list_create()
{
	struct list_head *head = NULL;
	
	head = (struct list_head *)malloc(sizeof(*head));
	if (NULL == head)
		return NULL;

	if (pthread_rwlock_init(&head->ls.lock, NULL))
		abort();
	*(struct list **)(&head->ls.head) = &head->ls;
	head->ls.next = &head->ls;
	head->ls.prev = &head->ls;
	head->count = 0;

	return &head->ls;
}

void list_destroy(struct list *ls, void(*destroy)(void *))
{
	struct list *p, *q;
	struct list_node *node;

	list_node_trylock(ls, 0, 0, true);
	for (p = ls->head->next; p != ls->head; p = q)
	{
		node = container_of(p, struct list_node, ls);
		destroy(node->data);
		q = p->next;
		free(node);
	}
	free(container_of(p, struct list_head, ls));
}

void list_add_next(struct list *ls, void *data)
{
	struct list_node *node;
	struct list_head *head;

	node=(struct list_node *)malloc(sizeof(*node));
	if (NULL == node)
		abort();
	head = container_of(ls->head, struct list_head, ls);

	node->data = data;
	if (pthread_rwlock_init(&node->ls.lock, NULL))
		abort();
	if (pthread_rwlock_wrlock(&node->ls.lock))
		abort();
	list_node_trylock(ls, 2, 0, true);
	*(struct list **)(&node->ls.head) = ls->head;
	node->ls.prev = ls;
	node->ls.next = ls->next;

	ls->next->prev = &node->ls;
	ls->next = &node->ls;
	list_node_unlock(ls, 3);
	head->count++;
}

void list_add_prev(struct list *ls, void *data)
{
	struct list_node *node;
	struct list_head *head;

	node = (struct list_node *)malloc(sizeof(*node));
	if (NULL == node)
		abort();
	head = container_of(ls->head, struct list_head, ls);

	node->data = data;
	if (pthread_rwlock_init(&node->ls.lock, NULL))
		abort();
	if (pthread_rwlock_wrlock(&node->ls.lock))
		abort();
	list_node_trylock(ls, -2, 0, true);
	*(struct list **)(&node->ls.head) = ls->head;
	node->ls.prev = ls->prev;
	node->ls.next = ls;

	ls->prev->next = &node->ls;
	ls->prev = &node->ls;
	list_node_unlock(ls, -3);
	head->count++;
}

void *list_del(struct list *ls)
{
	unsigned int i, t;
	int s, rval;
	struct list_node *node;
	void *data;
	struct list_head *head;

	t = (time(NULL) % 100) * 1000;
	while (1)
	{
		s = 0;
		do
		{
			if (ls == ls->head)
				break;
			rval = pthread_rwlock_trywrlock(&ls->lock);
			if (EBUSY == rval)
				break;
			if (rval)
				abort();
			s++;
			if (ls->prev == ls)
				break;
			rval = pthread_rwlock_trywrlock(&ls->prev->lock);
			if (EBUSY == rval)
				break;
			if (rval)
				abort();
			s++;
			if (ls->next == ls->prev)
				break;
			rval = pthread_rwlock_trywrlock(&ls->next->lock);
			if (EBUSY == rval)
				break;
			if (rval)
				abort();
			s++;
		} while (0);
		if (0 == rval)
			break;
		switch (s)
		{
		default:
            if (pthread_rwlock_unlock(&ls->prev->lock))
				abort();
		case 1:
            if (pthread_rwlock_unlock(&ls->lock))
				abort();
		case 0:
			break;
		}
		for (i = 0; i < t; i++);
	}

	node = container_of(ls, struct list_node, ls);
	data = node->data;
	head = container_of(ls->head, struct list_head, ls);

	ls->prev->next = ls->next;
	ls->next->prev = ls->prev;
	switch (s)
	{
	default:
        if (pthread_rwlock_unlock(&ls->next->lock))
			abort();
	case 2:
        if (pthread_rwlock_unlock(&ls->prev->lock))
			abort();
	case 1:
		free(node);
	case 0:
		break;
	}
	head->count--;

	return data;
}

struct list *list_next(struct list *ls)
{
	struct list *next;

    if (pthread_rwlock_rdlock(&ls->lock))
		abort();
	next = ls->next;
    if (pthread_rwlock_unlock(&ls->lock))
		abort();

	return next;
}

struct list *list_prev(struct list *ls)
{
	struct list *prev;

    if (pthread_rwlock_rdlock(&ls->lock))
		abort();
	prev = ls->prev;
    if (pthread_rwlock_unlock(&ls->lock))
		abort();

	return prev;
}

void list_close(struct list *ls)
{
	if (ls != ls->head)
        if (pthread_rwlock_unlock(&ls->lock))
			abort();
}

void *list_open(struct list *ls)
{
	struct list_node *node;

	if (pthread_rwlock_rdlock(&ls->lock))
		abort();
	if (ls == ls->head)
	{
        if (pthread_rwlock_unlock(&ls->lock))
			abort();
		return NULL;
	}
	node = container_of(ls, struct list_node, ls);
	return node->data;
}

int list_count(struct list *ls)
{
	struct list_head *head;

	head = container_of(ls->head, struct list_head, ls);
	return head->count;
}
