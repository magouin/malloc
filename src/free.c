/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 20:05:40 by magouin           #+#    #+#             */
/*   Updated: 2017/12/03 23:36:34 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <global.h>

static int		search_for_free(int y, int x, size_t *z, void *ptr)
{
	struct s_head			*curr;
	struct s_head			*next;
	static struct s_head	*prev = NULL;

	!*z ? prev = NULL : 0;
	curr = (struct s_head *)(page[y].memory[x] + *z);
	if (page[y].memory[x] + *z + sizeof(struct s_head) == ptr)
	{
		curr->used = 0;
		if (prev != NULL && prev->used == 0)
		{
			*z -= (void*)curr - (void*)prev;
			prev->size += sizeof(struct s_head) + curr->size;
			curr = prev;
		}
		if (*z + curr->size < ((page[y].type + sizeof(struct s_head)) * 100 /
getpagesize() + 1) * getpagesize() - sizeof(struct s_head) && ((next = (struct
s_head*)(page[y].memory[x] + *z + curr->size + sizeof(struct s_head))) || 1))
			!next->used ? curr->size += sizeof(struct s_head) + next->size : 0;
		return (1);
	}
	prev = curr;
	*z += curr->size + sizeof(struct s_head);
	return (0);
}

static void		free_large(int y, void *ptr)
{
	int	x;

	x = 0;
	while (x < PMAX)
	{
		if (page[y].memory[x] + sizeof(struct s_head) == ptr)
		{
			munmap(page[y].memory[x], ((struct s_head*)
		(page[y].memory[x]))->size + sizeof(struct s_head));
			page[y].memory[x] = NULL;
		}
		x++;
	}
}

void			free(void *ptr)
{
	int		y;
	int		x;
	size_t	z;

	y = 0;
	while (y < 2)
	{
		x = 0;
		while (page[y].memory[x])
		{
			z = 0;
			while (z < getpagesize() * ((page[y].type +
				sizeof(struct s_head)) * 100 / getpagesize() + 1))
			{
				if (search_for_free(y, x, &z, ptr))
					return ;
			}
			x++;
		}
		y++;
	}
	free_large(y, ptr);
}
