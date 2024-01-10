
#include <math.h>
#include <stdio.h>

#include <time.h> 

void print_array(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

void insertion_sort(int A[], int n){
    
    int j;

    // First pointer j; forward moving
    for (j = 1; j < n; j++){

        int key = A[j];

        // Second pointer i; backward moving
        int i = j - 1;

        while(i >= 0 && A[i] > key){

            A[i+1] = A[i];
            i--;
           
        }

        A[i+1] = key;

    }
}

int main()
{
 
    int A[] = {10, 8, 7, 5, 2, 4, 6, 1, 3};
    int n = sizeof(A) / sizeof(A[0]);

    clock_t begin = clock();

    print_array(A, n);
    insertion_sort(A, n);
    print_array(A, n);

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time_spent *= 1000000;

    printf("%f us", time_spent);

    return 0;
}
