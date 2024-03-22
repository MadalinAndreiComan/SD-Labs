#include "lab3_ex1_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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
	if (n <= 0)
		return NULL;

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
	if (n <= 0)
		return;

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
		new_node->next = list->head;
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

	new_node->next = temp->next;
	new_node->prev = temp;
	temp->next->prev = new_node;
	temp->next = new_node;
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
	/* TODO */
	if (n < 0)
		return NULL;
	if (n > list->size)
		n = list->size - 1;

	dll_node_t *ret_node = NULL;
	list->size--;

	// TODO: Use dll_get_nth_node();

	if (n == 0) {
		ret_node = list->head;
		list->head = list->head->next;
		list->head->prev = NULL;
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
	ret_node->prev = NULL;
	ret_node->next = NULL;

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
	/* TODO */
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
dll_print_int(doubly_linked_list_t *list)
{
	/* TODO */
}

/*
 * Procedura returneaza 1 daca numarul primit este prim, respectiv 0, altfel.
 * Exemplu: pentru 3, functia va returna 1, iar pentru 8, va returna 0.
 */
int is_prim(unsigned int n)
{
	int i;
	for (i = 2; i * i <= n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

/*
 * Procedura primește ca parametru un pointer la începutul unei liste dublu
 * înlănțuite și construiește două liste în care se vor afla toate elementele
 * prime, respectiv neprime.
 */
void
split_prime(doubly_linked_list_t *list, doubly_linked_list_t *prime_list,
			doubly_linked_list_t *rest_list)
{
	/* TODO */
}