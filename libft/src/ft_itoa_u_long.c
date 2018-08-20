/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:05:03 by magouin           #+#    #+#             */
/*   Updated: 2016/01/06 12:33:45 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned long int	ft_calc_u_long(unsigned long int n, int *len)
{
	unsigned long int	k;

	k = n;
	while (k)
	{
		k /= 10;
		len[0]++;
	}
	return (n);
}

void				fln_u_long(char *str, int *len)
{
	if (len[1])
		str[0] = '-';
	str[len[0] + len[1]] = '\0';
}

char				*ft_itoa_u_long(unsigned long int n)
{
	int		len[2];
	char	str[64];

	len[0] = 0;
	len[1] = 0;
	if (n == 0)
	{
		ft_putstr("0");
		return (NULL);
	}
	n = ft_calc_u_long(n, len);
	fln_u_long(str, len);
	while (n)
	{
		str[len[0] - 1 + len[1]] = n % 10 + '0';
		n /= 10;
		len[0]--;
	}
	ft_putstr(str);
	return (NULL);
}
