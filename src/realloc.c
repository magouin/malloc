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

void			*realloc(void *ptr, size_t size)
{
	size_t	old_size;
	void	*newptr;
	size_t	taille;

	if (!ptr)
		return (malloc(size));
	taille = *(size_t *)(ptr - sizeof(struct s_head));
	if (taille > size)
		return (ptr);
	old_size = *(size_t *)(ptr - sizeof(struct s_head));
	newptr = malloc(size);
	ft_memcpy(newptr, ptr, old_size);
	free(ptr);
	return (newptr);
}
