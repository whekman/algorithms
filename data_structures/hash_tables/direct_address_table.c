
// As described on page 222 of CLRS

// This version uses a contiguous array and sentinel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
	int key;
	char* value;
};

void print_table(struct item table[]){

	int i = 0;

	while(table[i].value != NULL){

		printf("%d: %s\n", i, (table[i]).value);
		i++;
	}
}

int search_table(struct item table[], char* value){

	int i = 0;

	while((table[i]).value != NULL){
		if (strcmp(table[i].value, value) == 0) {
	        return i;
	    }
	    i++;
    }

    return -1;
}

int main(void){

	struct item table[] = {{0,"hi"},
					 {1,"you"},
					  {2, "there"},
					  {3, NULL}};


	print_table(table);

	int i = search_table(table, "there");

	printf("%d", i);

	printf("\n");

	return 0;
}
