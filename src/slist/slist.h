#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef double slist_value;

/// @brief A single node of a singly linked list
typedef struct snode
{
	slist_value value;
	struct snode* next;
} snode;

snode* snode_new(slist_value value);

/// @brief Singly linked list
typedef struct slist
{
	snode* head;
	snode* tail;
	size_t size;
} slist;

slist slist_make(void);
void slist_destroy(slist* self);

snode* slist_append(slist* self, slist_value value);
snode* slist_insert_after(slist* self, snode* pos, slist_value value);
bool slist_remove(slist* self, snode* node);

typedef void (*snode_op)(slist_value value);

void slist_foreach(const slist* self, snode_op op);

#endif // SLIST_H
