## Memory Allocator

The purpose of that repository is to help developers to manage their memories. It tracks your malloc functions and frees your all allocated memory blocks automatically if one malloc fails. Use safe_malloc and safe_free to handle memory easily.

> 42 students should feel free to use the library because it obeys the Norminette rules. 

### Usage
```c
/* anywhere of your code */
char *string = safe_malloc(sizeof(char) * 10);
if (!string)
	return;
/* ... */
/* another corner of your code */
char *new_string = safe_malloc(sizeof(char) * 10);
if (!new_string)
	return; /* there is no need to free old pointers. */
```

### Handle aborting
The library allows you to register 2 handler functions. Just give a pointer
of your handler function.

And of course, you don't have to register a function. It is optional.
```c
void abort_start_func() {
	printf("I know my memory started to being aborted.\n");
}

void abort_stop_func() {
	printf("I know all my malloc pointers freed now.\n");
	exit(1);
}

int main() {
	register_pre_abort_func(abort_start_func);
	register_post_abort_func(abort_stop_func);
	/* ... */
}
```

If you exit in abort_stop function, you can assume
that your safe_malloc functions are non-null functions.
```c
/* anywhere of your code */
char *string = safe_malloc(sizeof(char) * 10);
string[0] = 'a'; // it is safe! 
```

### Testing

#### Automatic Bruteforce Testing
1. Clone this repository. `git clone git@github.com:hamza-cskn/memory-allocator.git`
2. Run tester: `sh tester.sh`

#### Manual Compiling for testing
1. Clone this repository. `git clone git@github.com:hamza-cskn/memory-allocator.git`
2. Set TESTER_MODE macro to 1 and compile: `gcc -DTESTER_MODE=1 allocator.c tester.c -o allocator`

### About Norminette
Norminette's rules force me to write testable codes. So I prepared `norm-fixer.sh`.

When you decide to include the memory allocator in your project follow these steps.

1. Clone the repository.
2. Run `sh norm-fixer.sh`.
3. Move allocator.h, allocator.c, aborter.c to your project.
4. Do not forget to add these files to your Makefile.
5. You are ready to use `safe_malloc()` and `safe_free`.
