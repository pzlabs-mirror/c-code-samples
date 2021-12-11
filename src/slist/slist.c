#include "slist/slist.h"

#include <stdlib.h>

snode* snode_new(slist_value value)
{
	snode* const node = malloc(sizeof(snode));
	if (!node)
	{
		return NULL;
	}
	*node = (snode){.value = value, .next = NULL};
	return node;
}

slist slist_make(void)
{
	return (slist){0};
}

void slist_destroy(slist* self)
{
	if (!self)
	{
		return;
	}
	snode* node = self->head;
	while (node)
	{
		snode* next = node->next;
		free(node);
		node = next;
	}
	*self = (slist){0};
}

snode* slist_append(slist* self, slist_value value)
{
	if (!self)
	{
		return NULL;
	}

	snode* const new_node = snode_new(value);
	if (!new_node)
	{
		return NULL;
	}

	if (self->head)
	{
		self->tail->next = new_node;
		self->tail = new_node;
	}
	else
	{
		self->head = new_node;
		self->tail = new_node;
	}

	++self->size;
	return new_node;
}

snode* slist_insert_after(slist* self, snode* pos, slist_value value)
{
	if (!self)
	{
		return NULL;
	}

	snode* const new_node = snode_new(value);
	if (!new_node)
	{
		return NULL;
	}

	if (pos)
	{
		new_node->next = pos->next;
		pos->next = new_node;
	}
	else
	{
		new_node->next = self->head;
		self->head = new_node;
	}

	if (pos == self->tail)
	{
		self->tail = new_node;
	}

	++self->size;
	return new_node;
}

bool slist_remove(slist* self, snode* node)
{
	if (!self || !node)
	{
		return false;
	}

	snode* before = NULL;
	for (snode* curr = self->head; curr && curr != node; curr = curr->next)
	{
		before = curr;
		if (!curr->next)
		{
			return false;
		}
	}

	if (before)
	{
		before->next = node->next;
		if (node == self->tail)
		{
			self->tail = before;
		}
	}
	else
	{
		self->head = node->next;
	}

	*node = (snode){0};
	free(node);

	--self->size;
	return true;
}

void slist_foreach(const slist* self, snode_op op)
{
	if (!self || !op)
	{
		return;
	}

	for (snode* node = self->head; node; node = node->next)
	{
		op(node->value);
	}
}
