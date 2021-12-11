#include <stdio.h>
#include <assert.h>

#include "slist/slist.h"

static void print_node(slist_value value);
static void print_list(const char* msg, const slist* list);

int main(void)
{
	slist list = slist_make();
	print_list("Empty list:", &list);

	snode* n1 = slist_append(&list, 1.);
	snode* n2 = slist_append(&list, 2.);
	snode* n3 = slist_append(&list, 3.);
	print_list("After append (1, 2 3):", &list);

	snode* n4 = slist_insert_after(&list, n2, 4.);
	snode* n5 = slist_insert_after(&list, n3, 5.);
	snode* n6 = slist_insert_after(&list, NULL, 6.);
	print_list("After insert_after (4, 5, 6):", &list);

	slist_remove(&list, n1);
	slist_remove(&list, n6);
	slist_remove(&list, n4);
	print_list("After remove (1, 4, 6):", &list);

	slist_remove(&list, n2);
	slist_remove(&list, n5);
	print_list("After remove (2, 5):", &list);

	slist_append(&list, 7.);
	print_list("After append (7):", &list);

	slist_destroy(&list);
}

static void print_node(slist_value value)
{
	printf("%g ", value);
}

static void print_list(const char* msg, const slist* list)
{
	printf("%s\n    Size: %zu; Items: [ ", msg, list->size);
	slist_foreach(list, &print_node);
	puts("]");
}
