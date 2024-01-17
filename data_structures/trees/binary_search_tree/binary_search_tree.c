#include <stdio.h>
#include <stdlib.h>

struct node {

	int key;

	struct node * p;
	struct node * left;
	struct node * right;
};

void tree_insert(struct node **tree, struct node *z){
	
	// y stores the point of insertion
	struct node * y = NULL;

	// x walks the tree
	// by comparing keys
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
		free(*tree);
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

void tree_from_array(struct node **tree, int keys[], int n){

	for(int i = 0; i < n; i++){
		struct node *N = node_create(keys[i]);
		tree_insert(tree, N);
	}

}

struct node * tree_search(struct node *x, int key){

	if ((x == NULL) || (key == x->key)){
		return x;
	}
	if (key < x->key){
		return tree_search(x->left, key);
	} else {
		return tree_search(x->right, key);
	}

}

// walks the sub-tree pointed to by x
// prints out the values in ascending order
// with indent you can set the indenting (defualt = 0)
// to help visualize the tree height
// (negative values remove the indenting)
void inorder_walk(struct node *x, int indent){

	if (x != NULL){
		inorder_walk(x->right, indent + 1);
		
		for(int i = 0; i < indent; i++){
			printf("\t");
		}
		printf("%d \n", x->key);

		inorder_walk(x->left, indent + 1);
		
	}

}

struct node * tree_minimum(struct node *x){
	if (x == NULL){
		return x;
	} else {
		while(x->left != NULL){
			x = x->left;
		}
		return x;
	}
}

struct node * tree_maximum(struct node *x){
	if (x == NULL){
		return x;
	} else {
		while(x->right != NULL){
			x = x->right;
		}
		return x;
	}
}

struct node * tree_successor(struct node *x){
	
	if(x == NULL){
		return NULL;
	}

	// if has right tree:
	// successor has min key there

	if(x->right != NULL){
		return tree_minimum(x->right);
	}

	// otherwise...
	// maybe there is a rightward ancestor up in the tree
	// s.t. x is leftward descendant on a rightward branch

	// we can find the successor by
	// move up on this rightward branch
	// untill we find a parent which qualifies as the successor

	// move up using pointer y
	struct node * y = x->p;

	while((y != NULL) && (y->right == x)){
		x = y;
		y = y->p;
	}

	return y;

}

struct node * tree_delete(struct node **tree, struct node * z){

	// y will be spliced out at some point
	struct node * y;

	// x points to sub-tree of z	
	struct node * x;


	// 1 or 0 children!
	// splice out: the parent gets the sub-tree (possibly null)
	if ((z->left == NULL) || (z->right == NULL)){

		y = z;

	// 2 children! - difficult
	// idea: swap z with spliced out successor (aunt)
	// so there are no orphans
	} else {
	
		y = tree_successor(z);

		// NOTE: the tree structure should ensure(!)
		// in this particular case
		// that the successor has 0/1 children
		// special property of BST !?
	}

	// acquire pointer x to the relevant sub-tree of y
	// if it's located left
	if (y->left != NULL){

		x = y->left;

	// if it's located right or empty
	} else {

		// NOTE: y->right may be NULL
		x = y->right;

	}

	// if there is a non-trivial sub-tree to take care of
	// assign "adoption parents" = "grandpa"
	if (x != NULL){

		x->p = y->p;

		// note if y == root;
		// y->p == NULL
		// so there is no "adoption parent"
		// but a new root! - a new tree, in a way
	}

	// check if x-sub-tree becomes new root
	if (y->p == NULL){
		*tree = x;
	
	// otherwise "adoption parents"
	// figure out where to put x-sub-tree:
	// left or right of parent
	} else if (y == y->p->left) {

		// splice out y		
		y->p->left = x;

	} else {

		y->p->right = x;

	}

	// in the case of swapping
	// transmitting responsibilities
	// copy key/satellite data from successor
	// into node to be removed
	if (y != z){
		z->key = y->key;
	} 

	free(y);

}

int main(void){

	// points to the root
	struct node *tree = NULL;

    int keys[] = {5,8,7,2,3,1,5};
    int n = sizeof(keys) / sizeof(keys[0]);

    tree_from_array(&tree, keys, n);

	inorder_walk(tree,0);
	printf("\n");

	struct node *p = NULL;
	p = tree_search(tree, 3);

	p = tree_minimum(tree);
	p = tree_maximum(tree->left->left);

	p = tree_successor(tree);
	p = tree_successor(p);		

	printf("p points to: ");
	if(p != NULL){
		printf("%d\n", p->key);	
	}

	printf("deleting node pointed by p\n");
	
	tree_delete(&tree, p);

	inorder_walk(tree,0);
	printf("\n");


	return 0;
}