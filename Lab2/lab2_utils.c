#include "lab2_utils.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>

linked_list_t *
ll_create(unsigned int data_size)
{
	linked_list_t *linkedList = malloc(sizeof(linked_list_t *));
	DIE(!linkedList, "malloc() failed");
	linkedList->data_size = data_size;
	linkedList->head = NULL;
	linkedList->size = 0;
	return linkedList;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, ignorati comanda (iesiti din functie).
 */
void
ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data)
{
	if (n < 0)
		return;
	if (n > list->size)
		n = list->size;

	list->size++;

	ll_node_t *new_node = malloc(sizeof(ll_node_t *));
	DIE(!new_node, "malloc() failed");
	new_node->next = NULL;
	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, "malloc() failed");
	memcpy(new_node->data, new_data, list->data_size);

	if (n == 0) {
		new_node->next = list->head;
		list->head = new_node;
		return;
	}

	int curr_pos = 0;
	ll_node_t *temp = list->head;
	while (curr_pos < n - 1) {
		temp = temp->next;
		curr_pos++;
	}

	new_node->next = temp->next;
	temp->next = new_node;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, ignorati comanda (iesiti din functie).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
ll_node_t *
ll_remove_nth_node(linked_list_t *list, unsigned int n)
{
	if (n < 0)
		return NULL;
	if (n > list->size)
		n = list->size - 1;

	ll_node_t *ret_node = NULL;
	list->size--;

	if (n == 0) {
		ret_node = list->head;
		list->head = list->head->next;
		return ret_node;
	}

	int curr_pos = 0;
	ll_node_t *temp = list->head;
	while (curr_pos < n - 1) {
		temp = temp->next;
		curr_pos++;
	}

	ret_node = temp->next;
	temp->next = ret_node->next;
	return ret_node;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t *list)
{
	return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t **pp_list)
{
	ll_node_t *temp = (*pp_list)->head;
	while (temp) {
		ll_node_t *to_delete = temp;
		temp = temp->next;
		free(to_delete->data);
		to_delete->data = NULL;
		free(to_delete);
		to_delete = NULL;
	}
	free((*pp_list));
	(*pp_list) = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t *list)
{
	ll_node_t *temp = list->head;
	while (temp) {
		int data = *(int *)temp->data;
		printf("%d ", data);
		temp = temp->next;
	}
	printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t *list)
{
	ll_node_t *temp = list->head;
	while (temp) {
		char *data = malloc(MAX_STRING_SIZE);
		DIE(!data, "malloc() failed");
		strncpy(data, temp->data, MAX_STRING_SIZE);
		printf("%s ", data);
		temp = temp->next;
	}

	printf("\n");
}