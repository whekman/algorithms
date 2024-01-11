
#include <stdio.h>
#include <math.h>


int parent(int i){
	return floor(i/2);
}

int left(int i){
	return 2*(i+1)-1;
}

int right(int i){
	return 2*(i+1);
}

void _print_tabs(int n){

	for (int i = 0; i < n; i++){
		printf("\t");
	}

}

void print_heap(int A[],
				int n,
				int i,
				int indent,
				int hs){

	if (indent == -1){
		indent = 0;
	}

	if (hs == -1){
		hs = n;
	}

	// print root
	_print_tabs(indent);
	printf("%d (%d)\n", A[i], i);

	int l = left(i);
	int r = right(i);

	
	if (l < hs){
		print_heap(A, n, l, indent+1, hs);
	}

	if (r < hs){
		print_heap(A, n, r, indent+1, hs);
	}

}

void max_heapify(int A[], int n, int i, int hs){

	// make our way down to the leaves
	// assure v root > v branches
	// swap root <--> branch if necessary to do so
	
	// L <-- index of largest value in p, l, r
	// if L != i
	// swap A[i] <--> A[L]

	int l = left(i);
	int r = right(i);

	int L;

    // Swap down left?
    // 0-index thus hs-1
	if (l <= (hs-1) && A[l] > A[i]){
		
		L = l;

	} else {

		L = i;
	}

	// Swap down right?
    // Note: A[r] > A[L] saves us an if statement A[r] > A[i]
	if (r <= (hs-1) && A[r] > A[L]){

		L = r;

	}

	int _;

	if (L != i){

		_ = A[i];
		A[i] = A[L];
		A[L] = _;

		max_heapify(A, n, L, hs);
		
	}

}

void build_max_heap(int A[], int n){
	// Makes a max heap out of a random array
	// does so by iteratively moving up the tree to the root
	// (from left to right at some height, then moving up)
	// heapifying each underlying sub-tree

	// assume all values in the heap
	int hs = n;

	// index of first leaf
	int i = floor(hs/2);

	while(i >= 0){

		max_heapify(A, n, i, hs);

		i--;
	}

}

void heapsort(int A[], int n){
	// Swap right-most leaf (last leaf) with root
	// this makes last value of array sorted (max)
	// and decrease the heapsize
	// this removes it from the heap
	// and max-heapify

	// To dos we first build the max-heap
	// so max-heapify can do it's job
	// (otherwise our small value
	// that is swapped to the root might get stuck halfway)

	// we start out with the whole array as a heap
	int hs = n;

	build_max_heap(A, n);

	// get the last index
	int i = hs - 1;

	int tmp;

	while(i > 0){

		tmp = A[i];
		A[i] = A[0];
		A[0] = tmp;

		hs--;

		max_heapify(A, n, 0, hs);
		i--;

	}

}

void print_array(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}


int main(){

	int A[] = {1,2,3,4,5,6};

	int n = sizeof(A)/sizeof(A[0]); // array-length

	heapsort(A, n);

	print_array(A, n);

	return 0;
}