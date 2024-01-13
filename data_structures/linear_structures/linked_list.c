
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

	// same as:
	// s = head -> next;
	// p = s -> next;
	struct node * p;
	p = head->next->next;
	
	// same as:
	// s -> next = s->next->next
	p->prev->next = p->next;

	// s->prev = s->next->prev
	p->next->prev = p->prev;

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

struct node * create(void){
	
}

int main()
{

	struct node *head = NULL;
	struct node *sentinel = NULL;
	struct node *n1, *n2, *n3;

	n1 = malloc(sizeof(struct node));
	n2 = malloc(sizeof(struct node));
	n3 = malloc(sizeof(struct node));
	sentinel = malloc(sizeof(struct node));
	head = malloc(sizeof(struct node));
	
	n1->key = 1;
	n2->key = 2;
	n3->key = 3;
	sentinel->key = -1;
	
	// works
	print_node(n1);
	print_node(n2);
	print_node(n3);
	print_node(sentinel);
	print_node(head);
	printf("\n");
	
	// creates a linked list
	head->next = sentinel;

	sentinel->next = sentinel;
	sentinel->prev = sentinel;

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

}