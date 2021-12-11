#include <assert.h>
#include <stdio.h>

#include "dlist/dlist.h"

static void print_node(dlist_value value);
static void print_list(const char* msg, const dlist* list);

int main(void)
{
	dlist list = dlist_make();
	print_list("Empty list:", &list);

	dnode* n1 = dlist_append(&list, 1.);
	dnode* n2 = dlist_append(&list, 2.);
	dnode* n3 = dlist_append(&list, 3.);
	print_list("After append (1, 2 3):", &list);

	dnode* n4 = dlist_insert_after(&list, n2, 4.);
	dnode* n5 = dlist_insert_after(&list, n3, 5.);
	dnode* n6 = dlist_insert_after(&list, NULL, 6.);
	print_list("After insert_after (4, 5, 6):", &list);

	dlist_remove(&list, n1);
	dlist_remove(&list, n6);
	dlist_remove(&list, n4);
	print_list("After remove (1, 4, 6):", &list);

	dnode* n7 = dlist_insert_before(&list, n2, 7.);
	dlist_insert_before(&list, n5, 8.);
	dnode* n9 = dlist_insert_before(&list, NULL, 9.);
	print_list("After insert_before (7, 8, 9):", &list);

	dlist_remove(&list, n7);
	dlist_remove(&list, n9);
	print_list("After remove (7, 9):", &list);

	dlist_append(&list, 10.);
	print_list("After append (10):", &list);

	dlist_destroy(&list);
}

static void print_node(dlist_value value)
{
	printf("%g ", value);
}

static void print_list(const char* msg, const dlist* list)
{
	printf("%s\n    Size: %zu; Items: [ ", msg, list->size);
	dlist_foreach(list, &print_node);
	puts("]");
}
