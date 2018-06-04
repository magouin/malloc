/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:05:52 by magouin           #+#    #+#             */
/*   Updated: 2017/11/29 19:31:04 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include "libft.h"
# define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))
# define MAX(x1, x2) ((x1) > (x2) ? (x1) : (x2))
# define PMAX 1024
# define SMALL 256
# define MEDIUM 4096

struct				s_head
{
	size_t			size;
	char			used;
}					;

struct				s_mem
{
	int				type;
	void			*memory[PMAX];
}					;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
#endif
