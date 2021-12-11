#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef double dlist_value;

/// @brief A single node of a doubly linked list
typedef struct dnode
{
	dlist_value value;
	struct dnode* prev;
	struct dnode* next;
} dnode;

dnode* dnode_new(dlist_value value);

/// @brief Soubly linked list
typedef struct dlist
{
	dnode* head;
	dnode* tail;
	size_t size;
} dlist;

dlist dlist_make(void);
void dlist_destroy(dlist* self);

dnode* dlist_append(dlist* self, dlist_value value);
dnode* dlist_insert_before(dlist* self, dnode* pos, dlist_value value);
dnode* dlist_insert_after(dlist* self, dnode* pos, dlist_value value);
bool dlist_remove(dlist* self, dnode* node);

typedef void (*dnode_op)(dlist_value value);

void dlist_foreach(const dlist* self, dnode_op op);

#endif
