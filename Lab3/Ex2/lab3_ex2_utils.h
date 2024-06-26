#ifndef LAB3_EX2_UTILS_H
#define LAB3_EX2_UTILS_H

#include "../../utils.h"
#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 64

typedef struct dll_node_t {
	void *data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un
				   pointer la void. */
	struct dll_node_t *prev, *next;
} dll_node_t;

typedef struct doubly_linked_list_t {
	dll_node_t *head;
	unsigned int data_size;
	unsigned int size;
} doubly_linked_list_t;

doubly_linked_list_t *
dll_create(unsigned int data_size);

dll_node_t *
dll_get_nth_node(doubly_linked_list_t *list, unsigned int n);

void
dll_add_nth_node(doubly_linked_list_t *list, unsigned int n, const void *data);

dll_node_t *
dll_remove_nth_node(doubly_linked_list_t *list, unsigned int n);

unsigned int
dll_get_size(doubly_linked_list_t *list);

void
dll_free(doubly_linked_list_t **pp_list);

void
dll_print_int_list(doubly_linked_list_t *list);

void
dll_print_string_list(doubly_linked_list_t *list);

#endif
