#include "dlist/dlist.h"

#include <stdlib.h>

dnode* dnode_new(dlist_value value)
{
	dnode* const node = malloc(sizeof(dnode));
	if (!node)
	{
		return NULL;
	}

	*node = (dnode){.value = value, .prev = NULL, .next = NULL};
	return node;
}

dlist dlist_make(void)
{
	return (dlist){0};
}

void dlist_destroy(dlist* self)
{
	if (!self)
	{
		return;
	}

	dnode* node = self->head;
	while (node)
	{
		dnode* next = node->next;
		free(node);
		node = next;
	}
	*self = (dlist){0};
}

dnode* dlist_append(dlist* self, dlist_value value)
{
	if (!self)
	{
		return NULL;
	}

	dnode* const new_node = dnode_new(value);
	if (!new_node)
	{
		return NULL;
	}

	if (self->head)
	{
		self->tail->next = new_node;
		new_node->prev = self->tail;
	}
	else
	{
		self->head = new_node;
	}
	self->tail = new_node;

	++self->size;
	return new_node;
}

dnode* dlist_insert_before(dlist* self, dnode* pos, dlist_value value)
{
	if (!self)
	{
		return NULL;
	}

	dnode* const new_node = dnode_new(value);
	if (!new_node)
	{
		return NULL;
	}

	if (pos)
	{
		new_node->next = pos;
		new_node->prev = pos->prev;
		if (pos->prev)
		{
			pos->prev->next = new_node;
		}
		pos->prev = new_node;
	}
	else
	{
		new_node->prev = self->tail;
		self->tail->next = new_node;
		self->tail = new_node;
	}

	if (pos == self->head)
	{
		self->head = new_node;
	}

	++self->size;
	return new_node;
}

dnode* dlist_insert_after(dlist* self, dnode* pos, dlist_value value)
{
	if (!self)
	{
		return NULL;
	}

	dnode* const new_node = dnode_new(value);
	if (!new_node)
	{
		return NULL;
	}

	if (pos)
	{
		new_node->next = pos->next;
		new_node->prev = pos;
		if (pos->next)
		{
			pos->next->prev = new_node;
		}
		pos->next = new_node;
	}
	else
	{
		new_node->next = self->head;
		self->head->prev = new_node;
		self->head = new_node;
	}

	if (pos == self->tail)
	{
		self->tail = new_node;
	}

	++self->size;
	return new_node;
}

bool dlist_remove(dlist* self, dnode* node)
{
	if (!self || !node)
	{
		return false;
	}

	if (node->prev)
	{
		node->prev->next = node->next;
	}
	else if (node == self->head)
	{
		self->head = node->next;
	}
	else
	{
		return false;
	}

	if (node->next)
	{
		node->next->prev = node->prev;
	}
	else if (node == self->tail)
	{
		self->tail = node->prev;
	}
	else
	{
		return false;
	}

	*node = (dnode){0};
	free(node);

	--self->size;
	return true;
}

void dlist_foreach(const dlist* self, dnode_op op)
{
	if (!self)
	{
		return;
	}

	for (dnode* node = self->head; node; node = node->next)
	{
		op(node->value);
	}
}
