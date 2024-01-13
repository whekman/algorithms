
#include <stdio.h>
#include <stdlib.h>

struct node {
	
	int key;

	// pointers
	struct node *next;
	struct node *prev;
};


// dereference and access the field
// using the -> operator
void print_node(struct node *n){

	printf("(%d) - next: %p - prev: %p\n",
			n->key, n->next, n->prev);
}

void print_list(struct node *head){

	struct node* p;

	// pointer starts at sentinel
	p = head->next;
	
	printf("LL: head -> sentinel <-> ");
	while(p->next->key != -1){
		printf("(%d) <-> ", p->next->key);
		p = p->next;
	}
	printf(" sentinel \n");

}

void delete(struct node *head){

	// points to first element
	struct node * p;
	p = head->next->next;

	// used to free up memory
	struct node * tmp;
	tmp = p;
	
	// redirecting the pointers
	p->prev->next = p->next;
	p->next->prev = p->prev;

	// freeing
	if (tmp->key != -1){
		free(tmp);
	}

}

void delete_wrong(struct node *head){
	// this spectacularly doesnt work
	// creates a circular structure:
	// H->S<->n1<->n2->n1
	// fails to run back to the sentinel

	struct node * s;
	
	s->next = s->next->next;
	s->prev = s->next->prev;

}

void insert(struct node *head, struct node *n){

	struct node *sentinel = head->next;

	// insertion
	n->next = sentinel->next;
	sentinel->next->prev = n;
	sentinel->next = n;
	n->prev = sentinel;
}

// CONSTRUCTOR
// Seems to work
struct node * construct_list(void){

	struct node *head = NULL;
	struct node *sentinel = NULL;

	sentinel = malloc(sizeof(struct node));
	head = malloc(sizeof(struct node));

	sentinel->key = -1;

	// creates a linked list
	head->next = sentinel;

	sentinel->next = sentinel;
	sentinel->prev = sentinel;

	return head;

}

// the destructor...
// PROBABLY NOT CORRECT YET!!!
void destruct_list(struct node * head){

	struct node* p;
	struct node* d;

	// pointer starts at sentinel
	p = head->next;
	
	printf("Destructing...\n");
	while(p->next->key != -1){
		printf("Freeing (%d)\n", p->next->key);
		d = p;
		p = p->next;
		free(d);
	}

	printf("Freeing sentinel (%d)\n", head->next->key);
	free(head->next);
	printf("Freeing head\n");
	free(head);
}

int main()
{

	struct node *head = construct_list();

	// creates nodes
	struct node *n1, *n2, *n3;

	n1 = malloc(sizeof(struct node));
	n2 = malloc(sizeof(struct node));
	n3 = malloc(sizeof(struct node));
	
	n1->key = 1;
	n2->key = 2;
	n3->key = 3;

	// works
	print_node(n1);
	print_node(n2);
	print_node(n3);
	print_node(head->next);
	print_node(head);
	printf("\n");
	
	// insertion
	insert(head, n1);
	insert(head, n2);
	insert(head, n3);
	
	print_node(head->next->next);
	printf("\n");

	printf("linked list:\n");
	print_list(head);

	delete(head);
	print_list(head);

	delete(head);
	print_list(head);

	delete(head);
	print_list(head);

	destruct_list(head);

}