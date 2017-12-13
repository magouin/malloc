#include "inc/malloc.h"
#include <unistd.h>
#include "inc/libft.h"
#define NB_MALLOC 1200

void *malloc(size_t size);

int main()
{
	int x;
	char *tmp;
	char *str[NB_MALLOC];

	x = 0;
	while (x < NB_MALLOC)
	{
		str[x] = malloc(5);
		strcpy(str[x], (tmp = ft_itoa(x)));
		free(tmp);
		printf("allocated and freed\n");
		x++;
	}
	x = 0;
	while (x < NB_MALLOC)
	{
		// printf("x = %d et str = %s\n", x , str[x]);
		free(str[x]);
		x++;
	}
	str[0] = malloc(255);
	free(str[0]);
	str[0] = malloc(1000);
	// free(str[0]);
	printf("getpagesize = %d\n", getpagesize());
	show_alloc_mem();
	return (0);
}