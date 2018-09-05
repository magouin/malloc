/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:37:44 by magouin           #+#    #+#             */
/*   Updated: 2018/09/05 19:37:45 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern struct s_mem	page[3];

static void	print_page(size_t type, void *b)
{
	if (type == SMALL)
	{
		ft_putstr("TINY : 0x");
		ft_itoa_base_long((size_t)b, 16);
	}
	else if (type == MEDIUM)
	{
		ft_putstr("SMALL : 0x");
		ft_itoa_base_long((size_t)b, 16);
	}
	else if (type == (size_t)-1)
	{
		ft_putstr("LARGE : 0x");
		ft_itoa_base_long((size_t)b, 16);
	}
	else
		return ;
	ft_putendl("");
}

static void	used(size_t *octets, struct s_head *head)
{
	if (head->used)
	{
		ft_putstr("0x");
		ft_itoa_base_long((size_t)((void *)head + sizeof(
			struct s_head)), 16);
		ft_putstr(" - 0x");
		ft_itoa_base_long((size_t)((void *)head + sizeof(
			struct s_head) + head->size - 1), 16);
		ft_putstr(" : ");
		ft_itoa_u_long(head->size);
		ft_putstr(" octets\n");
		*octets += head->size;
	}
}

static void	get_small_medium(int y, size_t *octets)
{
	int				x;
	struct s_head	*head;
	size_t			z;

	x = 0;
	while (page[y].memory[x])
	{
		z = 0;
		print_page((y ? SMALL : MEDIUM), page[y].memory[x]);
		head = (struct s_head *)(page[y].memory[x]);
		while (42)
		{
			used(octets, head);
			z += head->size + sizeof(struct s_head);
			if (z >= getpagesize() * ((page[y].type + sizeof(
				struct s_head)) * 100 / getpagesize() + 1))
				break ;
			head = (struct s_head *)(page[y].memory[x] + z);
		}
		x++;
	}
}

void		show_alloc_mem(void)
{
	struct s_head	*head;
	int				y;
	size_t			octets;

	y = 0;
	octets = 0;
	while (y < 2)
	{
		get_small_medium(y, &octets);
		y++;
	}
	y = 0;
	while (y < PMAX)
	{
		page[2].memory[y] ? print_page(-1, page[2].memory[y]) : 0;
		if (page[2].memory[y])
		{
			head = page[2].memory[y];
			used(&octets, head);
		}
		y++;
	}
	ft_putstr("Total : ");
	ft_putnbr(octets);
	ft_putstr(" octets\n");
}
