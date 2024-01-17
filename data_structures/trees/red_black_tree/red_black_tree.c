

#include <stdio.h>
#include <stdlib.h>

// RED BLACK TREES: type of self-balancing BST
//--------------------------------------------
// 0. Binary tree with keys/satellite data
// 1. Each node is black or red
// 2. Root is black
// 3. Sentinel* leaves are black *(do not contain data)
// 4. Children of red node are black
// 5. n black nodes equal for all paths from node to leaves 

// Here is just use nodes as sentinel leaves
// these node have isSentinel == 1;

struct node {

	char color;
	int key;
	struct node * parent;
	struct node * left;
	struct node * right;

};

struct rbtree {
	struct node * root;
	struct node * nil;
};

// LEFT ROTATE:

//  p                 p
//  x       ->        y
// a   y            x   c
//   b   c        a   b

// the asc order: a x b y c is maintained
void left_rotate(struct rbtree *T, struct node *x){

	// y originally right child of x
	struct node *y;

	// make b the right child of x instead:   x
	y = x->right;                      //   a   b
	x->right = y->left;

	// if the sub-tree is not a sentinel
	if (y->left != T->nil){

		// set the parent
		y->left->parent = x;

	}

	// we start to 'rotate':
	// both x and y temporarily have same parent
	y->parent = x->parent;

	// set y as replacing child of parent
	// Possibly: x was root, left-child, right-child
	if(x->parent == T->root){		
		
		T->root = y;

	} else if (x == x->parent->left){

		x->parent->left = y;

	} else {

		x->parent->right = y;	
	}

	// finish things up: set x left of y
	y->left = x;
	x->parent = y;
}

// RIGHT ROTATE:
// TO DO

void rb_insert(struct rbtree *T, struct node *z){

	struct node * y = T->nil;
	struct node * x = T->root;

	// move down y using x to scan ahead
	while(x != T->nil){
		y = x;
		if (z->key < x->key){
			x = x->left;
		} else {
			x = x->right;
		}
	}

	// now y points to insertion point (parent)
	z->parent = y;

	// case first node (y = nil, x = root = nil)
	if (y == T->nil){
	
		T->root = z;
	
	} else if (z->key < y->key){
	
		y->left = z;
	
	} else {
	
		y->right = z;
	}

	// finishing up
	z->left = T->nil;
	z->right = T->nil;
	z->color = 'r';
}

int main(void){


	return 0;
}