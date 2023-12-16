#include <stdlib.h>
#include "allocator.h"
#define GOOD_EXIT 1
#define BAD_EXIT  0

/*
	Global variables are forbidden, so we used
	static variables to implement them.

	This function returns head of memory blocks
	list.
*/
memory_block *get_memory_blocks() {
	static memory_block memory_blocks = {NULL, NULL}; // head node always must be null and never be freed or removed
	return &memory_blocks;
}

/*
	This function basically adds new element to
	the our memory blocks list.

	Return values:
		if success, returns 1.
		otherwise, returns 0.
*/
int append_memory_block(void *ptr) {
	memory_block *memory_blocks;
	memory_block *new = ALLOCATE_MEMORY(sizeof(memory_block));
	if (!new)
		return BAD_EXIT;
	*new = (memory_block) {.ptr = ptr, .next = NULL};
	memory_blocks = get_memory_blocks();
	while (memory_blocks->next != NULL)
		memory_blocks = memory_blocks->next;
	memory_blocks->next = new;
	return GOOD_EXIT;
}

/*
	This function basically scans memory blocks
	to find pointer given and removes it.

	Return values:
		if success, returns 1.
		otherwise, returns 0.
*/
int remove_memory_block(void *ptr) {
	memory_block *cur; 
	memory_block *prev;
	
	cur = get_memory_blocks();
	while (cur->next != NULL) {
		if (cur->ptr == ptr) {
			prev->next = cur->next;
			FREE_MEMORY(cur);
			return GOOD_EXIT;
		}
		prev = cur;
		cur = cur->next;
	}
	return BAD_EXIT;
}

/*
	Allocates memory block using the malloc function
	which you know.

	However it stores every pointer and track them to
	abort the program gracefully.

	Return values:
		if success, returns allocated memory block.
		otherwise, frees ALL memory blocks and returns null pointer.
*/
void *safe_malloc(int size) {
	void *ptr = ALLOCATE_MEMORY(size);
	if (!ptr) {
		abort_memory();
		return NULL;
	}
	if (!append_memory_block(ptr)) {
		FREE_MEMORY(ptr); // free ptr manually because it is not added to memory blocks list
		abort_memory();
		return NULL;
	}

	return ptr;
}


/*
	Frees memory block which allocated by using safe_malloc
	function.
*/
void safe_free(void *ptr) {
	remove_memory_block(ptr); // free even if the pointer is not in memory blocks list
	FREE_MEMORY(ptr);
}

/*
	Frees all memory blocks which allocated by using safe_malloc
	function.
*/
void abort_memory() {
	register_pre_abort_func(NULL);
	memory_block *memory_blocks = get_memory_blocks();
	memory_blocks = memory_blocks->next; // head node is not allocated by malloc and does not contain any pointer
	while (memory_blocks != NULL) {
		memory_block *next = memory_blocks->next;
		FREE_MEMORY(memory_blocks->ptr);
		FREE_MEMORY(memory_blocks);
		memory_blocks = next;
	}
	get_memory_blocks()->next = NULL;
	register_post_abort_func(NULL);
}

/*
	Registers abort function to call before when abort_memory
	function is called.
*/
void register_pre_abort_func(void (*abort_func)(void)) {
	static void (*func)(void) = NULL;
	if (abort_func != NULL)
		func = abort_func;
	else if (func != NULL)
		func();
}

/*
	Registers abort function to call after when abort_memory
	function is called.
*/
void register_post_abort_func(void (*abort_func)(void)) {
	static void (*func)(void) = NULL;
	if (abort_func != NULL)
		func = abort_func;
	else if (func != NULL)
		func();
}

