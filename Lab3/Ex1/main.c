#include "lab3_ex1_utils.h"

int main()
{
	doubly_linked_list_t* list, *primes_list, *non_primes_list;

	long size;

	primes_list = dll_create(sizeof(int));
	non_primes_list = dll_create(sizeof(int));

	list = dll_create(sizeof(int));
	scanf("%ld", &size);

	long int curr_nr;
	for (int i = 0; i < size; ++i) {
		scanf("%ld", &curr_nr);
		dll_add_nth_node(list, size, &curr_nr);
	}

	split_prime(list, primes_list, non_primes_list);

	dll_print_int(primes_list);

	dll_print_int(non_primes_list);

	dll_free(&list);

	return 0;
}