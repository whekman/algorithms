
#include <math.h>
#include <stdio.h>

#include <time.h> 

/**
 * @brief Prints an array to the command-line using repeated us of printf
 *
 * Detailed explanation.
 */
void print_array(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}


/**
 * @brief Merge 2 adjacent sorted sub-arrays using l,m,r left/middle/right-most indices.
 * 
 * ! Assumes the sub-arrays are sorted...
 * eg int A[] = {3,4,1,2}; merge(A,0,2,4); A -> 1 2 3 4
 * 
 * ! Uses CLRS's sentinel trick with a hard-coded value of 1000...
 * 
 */
void merge(int A[], int l, int m, int r){

    // Define the left and right sub-arrays

    // number of values in each temporary L/R array
    int nL = m - l;
    int nR = r - m;

    // the sentinel
    int s = 1000;

    // Reserve +1 space for the sentinels
    int L[nL+1];
    int R[nR+1];

    // eg nL = 4 --> x x x x s; sentinel at i = 5
    L[nL] = s;
    R[nR] = s;

    for (int i = 0; i < nL; i++){
        L[i] = A[l+i];
    }

    for (int i = 0; i < nR; i++){
        R[i] = A[m+i];
    }

    // the actual merging
    int i = 0;
    int j = 0;

    for (int k = l; k < r; k++){

        if (L[i] <= R[j]){

            A[k] = L[i];
            i++;

        } else {


            A[k] = R[j];
            j++;

        }

    }
    
}

/**
 * @brief Merge sort an array with l and r left/right-most indices.
 * 
 * 
 * eg int A[] = {4,3,2,1}; merge_sort(A,0,4);
 * 
 */
void merge_sort(int A[], int l, int r){
    

    if ((r - l) > 1){

        int m = floor( ( (l + r) / 2) );
        //printf("%d \n", m);

        merge_sort(A, l, m);
        merge_sort(A, m, r);

        merge(A, l, m, r);
        
    }
}

// Test/run the above
int main()
{
 
    int A[] = {8, 7, 6, 5, 4, 3, 2, 1};

    int n = sizeof(A) / sizeof(A[0]);

    clock_t begin = clock();
    
    merge_sort(A, 0, 8);

    print_array(A, n);

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time_spent *= 1000000;

    printf("%f us", time_spent);

    return 0;
}
