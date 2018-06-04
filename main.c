#include "inc/malloc.h"
#include <unistd.h>
#include "inc/libft.h"
#define NB_MALLOC 1200

void *malloc(size_t size);

int main()
{
	malloc(42);
	malloc(84);
	malloc(3725);
	malloc(48847);
	show_alloc_mem();
	return (0);
}