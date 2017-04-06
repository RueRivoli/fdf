/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:07:15 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/06 17:10:18 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char		convert(int i)
{
	if (i >= 0 && i <= 9)
		return (i + 48);
	else if (i >= 10 && i <= 15)
		return (i + 55);
	return (-1);
}

static int		length(int i)
{
	int count;
	int nb;

	count = 1;
	while (i > 15)
	{
		nb = i / 16;
		i = i - nb * 16;
		count++;
	}
	return (count);
}

char			*ft_intermediate(int i, char *str, int fact, int k)
{
	int		a;
	int		len;
	char	*str_new;

	len = length(i);
	a = len;
	while (a > 0)
	{
		str[k] = convert(i / fact);
		i = i - (i / fact) * fact;
		fact = fact / 16;
		a--;
		k++;
	}
	if (ft_strlen(str) == 1)
	{
		if (!(str_new = ft_strnew(2)))
			return (NULL);
		str_new[0] = '0';
		str_new[1] = str[0];
		return (str_new);
	}
	return (str);
}

char			*ft_itohex(int i)
{
	int		fact;
	int		len;
	char	*str_new;
	char	*str;
	int		k;

	len = length(i);
	str_new = NULL;
	if (!(str = ft_strnew(len)))
		return (NULL);
	k = 0;
	fact = 1;
	while (len > 1)
	{
		fact = fact * 16;
		len--;
	}
	return (ft_intermediate(i, str, fact, k));
}
