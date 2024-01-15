#include <stdio.h>
#include <stdlib.h>

struct node {

	int key;

	struct node * p;
	struct node * left;
	struct node * right;
};

void assign_func(struct node **db, struct node * p){
	*db = p;
}

int main(void){

	// points to the root
	struct node * A = NULL;
	struct node * B = NULL;
	
	assign_func(&A, B);

	printf("%d", A == B);


	return 0;
}