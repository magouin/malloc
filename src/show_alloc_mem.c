/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:17:09 by magouin           #+#    #+#             */
/*   Updated: 2017/11/30 17:11:35 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern struct s_mem	page[3];

void			print_page(size_t type, void *b)
{
	char		*tmp;

	if (type == SMALL)
	{
		ft_putstr("TINY : ");
		ft_putendl((tmp = ft_itoa_base_long((size_t)b, 16)));
		free(tmp);
	}
	else if (type == MEDIUM)
	{
		ft_putstr("SMALL : ");
		ft_putendl((tmp = ft_itoa_base_long((size_t)b, 16)));
		free(tmp);
	}
	else if (type == (size_t)-1)
	{
		ft_putstr("LARGE : ");
		ft_putendl((tmp = ft_itoa_base_long((size_t)b, 16)));
		free(tmp);
	}
}

void			show_alloc_mem(void)
{
	int				x;
	struct s_head	*head;
	int				y;
	size_t				z;
	size_t			octets;

	y = 0;
	while (y < 2)
	{
		x = 0;
		octets = 0;
		while (page[y].memory[x])
		{
			z = 0;
			print_page((y ? SMALL : MEDIUM), page[y].memory[x]);
			head = (struct s_head *)(page[y].memory[x]);
			while (42)
			{
				head->used ? printf("%p - %p : %zu octets\n", (void *)(head + sizeof(struct s_head)), (void *)(head + sizeof(struct s_head) + head->size - 1), head->size) : 0;
				head->used ? octets += head->size : 0;
				z += head->size + sizeof(struct s_head);
				if (z >= getpagesize() * ((page[y].type + sizeof(struct s_head)) * 100 / getpagesize() + 1))
					break ;
				head = (struct s_head *)(page[y].memory[x] + z);
			}
			x++;
		}
		y++;
	}
	x = 0;
	while (x < PMAX)
	{
		page[y].memory[x] ? print_page(-1, page[y].memory[x]) : 0;
		if (page[y].memory[x])
		{
			head = page[y].memory[x];
			printf("0x%p - 0x%p : %zu octets\n", (void *)(head + sizeof(struct s_head)), (void *)(page[y].memory[x] + sizeof(struct s_head) + head->size - 1), head->size);
			octets += head->size;
		}
		x++;
	}
	printf("Total : %zu octets\n", octets);
}
