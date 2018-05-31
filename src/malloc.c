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

void			*get_space(unsigned char *mem, int type, size_t size)
{
	int				x;
	struct s_head	*head;

	x = 0;
	(void)size;
	head = (struct s_head *)(mem);
	while (!(head->used == 0 && (size == head->size || size +
		sizeof(struct s_head) <= head->size)))
	{
		x += head->size + sizeof(struct s_head);
		if ((size_t)x >= getpagesize() *
			((type + sizeof(struct s_head)) * 100 / getpagesize() + 1))
			return (NULL);
		head = (struct s_head *)(mem + x);
	}
	return (mem + x);
}

void			*get_mem(struct s_mem *memory, size_t size)
{
	int				x;
	void			*maloc;
	struct s_head	*head;
	void			*rez;

	x = 0;
	while (memory->memory[x] && !(maloc = get_space(memory->memory[
		x], memory->type, size)))
		x++;
	if (!(memory->memory[x]))
	{
		memory->memory[x] = mmap(0, getpagesize() * ((memory->type +
			sizeof(struct s_head)) * 100 / getpagesize() + 1),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		((struct s_head*)memory->memory[x])->size = getpagesize() *
		((memory->type + sizeof(struct s_head)) * 100 / getpagesize()
			+ 1) - sizeof(struct s_head);
		maloc = memory->memory[x];
	}
	head = (struct s_head *)(maloc);
	rez = maloc + sizeof(struct s_head);
	(!(head->size == size)) ? (*(struct s_head *)(rez + size) = (struct s_head)
{head->size - size - sizeof(struct s_head), 0}) : (struct s_head){0, 0};
	*head = (struct s_head){size, 1};
	return (rez);
}

void			*malloc(size_t size)
{
	int x;

	x = 0;
	if (size < MEDIUM)
		return (get_mem(&(page[size < SMALL ? 0 : 1]), size));
	while (page[2].memory[x])
		x++;
	page[2].memory[x] = mmap(0, size + sizeof(struct s_head),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	*(struct s_head*)page[2].memory[x] = (struct s_head){size, 1};
	return (page[2].memory[x] + sizeof(struct s_head));
}
