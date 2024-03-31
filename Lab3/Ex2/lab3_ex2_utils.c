#include "lab3_ex2_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// TODO: USE DIE() MACRO

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii list).
 */
doubly_linked_list_t *
dll_create(unsigned int data_size)
{
	doubly_linked_list_t *new_list = malloc(sizeof(*new_list));
	new_list->data_size = data_size;
	new_list->size = 0;
	new_list->head = NULL;

	return new_list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere?
 * Atentie: n>=0 (nu trebuie tratat cazul in care n este negativ).
 */
dll_node_t *
dll_get_nth_node(doubly_linked_list_t *list, unsigned int n)
{
	n = n % list->size;
	dll_node_t *temp = list->head;
	int curr_pos = 0;
	while (curr_pos < n) {
		temp = temp->next;
		curr_pos++;
	}

	return temp;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei.
 * Atentie: n>=0 (nu trebuie tratat cazul in care n este negativ).
 */
void
dll_add_nth_node(doubly_linked_list_t *list, unsigned int n, const void *data)
{
	if (n > list->size)
		n = list->size;

	list->size++;

	dll_node_t *new_node = malloc(sizeof(*new_node));
	DIE(!new_node, "malloc() failed");
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, "malloc() failed");
	memcpy(new_node->data, data, list->data_size);

	// TODO: Use dll_get_nth_node();

	if (n == 0) {
		if (list->head == NULL) {
			list->head = new_node;
			new_node->next = new_node->prev = new_node;
			return;
		}
		new_node->next = list->head;
		new_node->prev = list->head->prev;
		new_node->prev->next = new_node;
		list->head->prev = new_node;
		list->head = new_node;
		return;
	}


	int curr_pos = 0;
	dll_node_t *temp = list->head;
	while (curr_pos < n - 1) {
		temp = temp->next;
		curr_pos++;
	}


	if (temp)
		new_node->next = temp->next;
	else
		new_node->next = list->head;
	new_node->prev = temp;
	if (temp->next)
		temp->next->prev = new_node;
	temp->next = new_node;

	if (n == list->size - 1) {
		list->head->prev = new_node;
		new_node->next = list->head;
	}
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Este responsabilitatea apelantului sa elibereze memoria
 * acestui nod.
 * Atentie: n>=0 (nu trebuie tratat cazul in care n este negativ).
 */
dll_node_t *
dll_remove_nth_node(doubly_linked_list_t *list, unsigned int n)
{
	if (n >= list->size)
		n = list->size - 1;

	dll_node_t *ret_node = NULL;
	list->size--;

	// TODO: Use dll_get_nth_node();

	if (n == 0) {
		if (list->size == 0) {
			ret_node = list->head;
			list->head = NULL;
			return ret_node;
		}
		ret_node = list->head;
		list->head = list->head->next;
		ret_node->prev->next = list->head;
		list->head->prev = ret_node->prev;

		ret_node->next = NULL;
		ret_node->prev = NULL;
		return ret_node;
	}

	int curr_pos = 0;
	dll_node_t *temp = list->head;
	while (curr_pos < n - 1) {
		temp = temp->next;
		curr_pos++;
	}

	ret_node = temp->next;
	temp->next = ret_node->next;
	ret_node->next->prev = temp;

	return ret_node;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t *list)
{
	return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t **pp_list)
{
	dll_node_t *temp = (*pp_list)->head;
	do {
		dll_node_t *to_delete = temp;
		temp = temp->next;
		free(to_delete->data);
		to_delete->data = NULL;
		free(to_delete);
		to_delete = NULL;
	} while (temp != (*pp_list)->head);
	free((*pp_list));
	(*pp_list) = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
dll_print_int_list(doubly_linked_list_t *list)
{
	dll_node_t *temp = list->head;
	do {
		printf("%d ", *(int *)temp->data);
		temp = temp->next;
	} while (temp != list->head);
	printf("\n");
}

void
dll_print_string_list(doubly_linked_list_t *list)
{
	dll_node_t *temp = list->head->prev;
	do {
		printf("%s ", (char *)temp->data);
		temp = temp->prev;
	} while (temp != list->head->prev);
	printf("\n");
}