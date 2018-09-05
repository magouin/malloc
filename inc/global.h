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

#ifndef GLOBAL_H
# define GLOBAL_H

struct s_mem	page[3] = {(struct s_mem){SMALL, {NULL}}, (struct s_mem)
	{MEDIUM, {NULL}}, (struct s_mem){0, {NULL}}};

#endif
