/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 21:21:53 by magouin           #+#    #+#             */
/*   Updated: 2017/12/03 21:21:54 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern struct s_mem	page[3];

static void		*search_for_realloc2(struct s_norm a, void *ptr, size_t size,
	struct s_head *curr)
{
	struct s_head	*next;
	void			*rez;

	next = (struct s_head*)(page[a.y].memory[a.x] + *(a.z) +
	curr->size + sizeof(struct s_head));
	if (!next->used && size + 16 - (size % 16) < next->size + curr->size)
	{
		curr->size += next->size + sizeof(struct s_head);
		rez = curr;
	}
	else
	{
		rez = malloc(size);
		ft_memcpy(rez, ptr, curr->size);
		free(ptr);
	}
	return (rez);
}

static void		*search_for_realloc(struct s_norm a, void *ptr, size_t size)
{
	struct s_head	*curr;
	void			*rez;

	curr = (struct s_head *)(page[a.y].memory[a.x] + *(a.z));
	if (curr + sizeof(struct s_head) == ptr && curr->used)
	{
		if (*(a.z) + curr->size < ((page[a.y].type + sizeof(struct s_head)) *
100 / getpagesize() + 1) * getpagesize() - sizeof(struct s_head))
			rez = search_for_realloc2(a, ptr, size, curr);
		else
		{
			rez = malloc(size);
			ft_memcpy(rez, ptr, curr->size);
			free(ptr);
		}
		return (rez);
	}
	*(a.z) = *(a.z) + curr->size + sizeof(struct s_head);
	return (NULL);
}

void			*realloc_large(int y, void *ptr, size_t size)
{
	int		x;
	void	*rez;

	x = 0;
	while (x < PMAX)
	{
		if (page[y].memory[x] + sizeof(struct s_head) == ptr)
		{
			if (((struct s_head *)page[y].memory[x])->size < size + 16 - (size % 16))
				return (page[y].memory[x]);
			else
			{
				rez = malloc(size);
				ft_memcpy(rez, page[y].memory[x] + sizeof(struct s_head),
					((struct s_head *)page[y].memory[x])->size);
				free(ptr);
			}
		}
		x++;
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	int		y;
	int		x;
	size_t	z;
	void	*rez;

	y = 0;
	if (ptr == NULL)
		return (malloc(size));
	while (y < 2)
	{
		x = 0;
		while (page[y].memory[x])
		{
			z = 0;
			while (z < getpagesize() * ((page[y].type +
				sizeof(struct s_head)) * 100 / getpagesize() + 1))
			{
				if ((rez = search_for_realloc((struct s_norm)
					{x, y, &z}, ptr, size)))
					return (rez);
			}
			x++;
		}
		y++;
	}
	return (realloc_large(y, ptr, size));
}
