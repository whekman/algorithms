#include <stdio.h>
#include <stdlib.h>

struct node {

	int key;

	struct node * p;
	struct node * left;
	struct node * right;
};

void insert_node(struct node **tree, struct node * z){
	
	// y stores the point of insertion
	struct node * y = NULL;

	// x walks the tree
	struct node * x = *tree;

	while(x != NULL){

		y = x;
		if (z->key < x->key){
			x = x->left;
		} else {
			x = x->right;
		}
	}

	// insert the new node z as a child of y
	// sets the pointer FROM z to p
	z->p = y;

	// empty tree
	if (y == NULL){

		printf("Tree is Empty..\n");

		// z become the root of the tree

		*tree = z;

		printf("New root of tree has key: %d\n", z->key);

	// sets the pointer FROM y to p
	} else {
		if (z->key < y->key){
			y->left = z;
		} else {
			y->right = z;
		}
	}

}

struct node * node_create(int key){
	
	struct node * n = NULL;
	
	n = malloc(sizeof(struct node));

	n->key = key;

	return n;

}

// walks the sub-tree pointed to by x
void inorder_walk(struct node * x){
	if (x != NULL){
		inorder_walk(x->left);
		printf("%d -> ", x->key);
		inorder_walk(x->right);
	}
}

int main(void){

	// points to the root
	struct node * tree = NULL;

	struct node * n1 = node_create(4);
	struct node * n2 = node_create(5);
	struct node * n3 = node_create(3);

	insert_node(&tree, n1);
	insert_node(&tree, n2);
	insert_node(&tree, n3);

	printf("%d\n", tree == n1);

	inorder_walk(tree);

	printf("KEY\n");
	printf("%d\n", tree->right->key);

	return 0;
}