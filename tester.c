#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *fake_malloc(int size) {
	static int seed = -1; 

	if (seed < 0) {
		seed = time(NULL);
		srand(seed);
	}

	int chance = rand() % 100;

	if (chance < 1){
		return NULL;
	} else { 
		void *ptr = malloc(size);
		printf("MALLOC %p\n", ptr);
		return ptr;
	}
}

void fake_free(void *ptr) {
	printf("FREE %p\n", ptr);
	free(ptr);
}

void test() {
	int **test = (int **) safe_malloc(50 * sizeof(int *));
	if (test == NULL) {
		printf("PROGRAM LEVEL malloc failed\n");
		return;
	}
	for (int i = 0; i < 50; i++) {
		test[i] = safe_malloc(sizeof(int) * i);
		if (test[i] == NULL) {
			printf("PROGRAM LEVEL malloc(2) failed\n");
			return;
		}
	}
	
	abort_memory();
}

void abort_start_func() {
	printf("PROGRAM LEVEL i know that memory of my program started to being aborted\n");
}

void abort_stop_func() {
	printf("PROGRAM LEVEL i know that memory of my program completely aborted.\n");
	// exit() will fit here perfectly
}


int main() {
	register_pre_abort_func(abort_start_func);
	register_post_abort_func(abort_stop_func);
    test();
    return 0;
}
