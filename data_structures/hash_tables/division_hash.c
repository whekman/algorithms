
// A basic non-trivial example of hashing

#include <stdio.h>
#include <stdlib.h>

// K&R 2 Hash
// eg maps
// a -> 97 (ascii val)
// b -> 98
// ab -> 3105
// ba -> 3135
unsigned int hash_KR2(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;
    return hashval;
}

// prints the binary representation of a character
void printbincharpad(char *c)
{

	char d = *c;

	d = d + 3;

    for (int i = 7; i >= 0; --i)
    {
        putchar( (d & (1 << i)) ? '1' : '0' );
    }
    putchar('\n');
}


// given int A[n]
void print_array(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}


// division method: h(k) = k mod m
int divhash(int k, int m){

	return k%m;

}

void table_insert(int table[], int m, char *key, int value){

	unsigned int h = hash_KR2(key);

	int i = divhash(h, m);

	printf("s = %s, h = %d, i = %d \n", key, h, i);

	if (table[i] == 0){

		table[i] = value;
	} else {
		printf("error: collision - already containts value for hash(key).\n");
	} 

}

int table_search(int table[], int m, char *key){

	unsigned int h = hash_KR2(key);

	int i = divhash(h, m);

	return table[i];

}


int main(void){

	// number of slots - should be prime and ~1.3 x number of max expected entries
	int m = 13;
	int table[m];

	char *key = "a";
	int value = 1;

	print_array(table, m);

	table_insert(table, m, key, 1);

	print_array(table, m);

	key = "b";

	table_insert(table, m, key, 2);

	print_array(table, m);

	key = "ab";

	table_insert(table, m, key, 3);

	print_array(table, m);

	key = "shoop";

	table_insert(table, m, key, 4);

	key = "shoop";

	table_insert(table, m, key, 4);

	print_array(table, m);

	value = table_search(table, m, key);

	printf("%d", value);

	return 0;
}