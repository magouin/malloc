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

void			*calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
