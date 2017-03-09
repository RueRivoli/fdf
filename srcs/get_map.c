/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:09:54 by fgallois          #+#    #+#             */
/*   Updated: 2017/03/03 11:07:23 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_color(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'x')
			return (ft_hextoint(&str[i + 1]));
		i++;
	}
	return (-1);
}

static t_node		**convert_map(char **split, t_node **map)
{
	int len;
	static int j;
	int i;
	t_node *new;
	int err44;

	i = 0;
	err44 = -42;
	len = ft_splitlen(split);
	ft_putstr("P : ");
	ft_putnbr(j);
	//ft_putchar('\n');
	map[j] = (t_node*)malloc(sizeof(t_node) * (len + 1));
	if (!(map[j]))
	{
		free(map);
		return (NULL);
	}
	while (i < len)
	{
		err44 = ft_atoi(split[i]);
		//ft_putnbr(get_color(split[i]));
		new = init_node(i, j, ft_atoi(split[i]), get_color(split[i]));
		ft_memcpy(map[j], new, sizeof(new));
		map[j][i] = *new;
		display_node(&map[j][i]);
		//ft_putchar('\n')
		i++;
	}

	j++;
	return (map);
}

t_node		**get_map(int fd)
{
	char *line;
	int leng;
	char **split;
	t_node **map;
	int count;

	map = NULL;
	line = NULL;
	leng = 0;
	count = 1;
	if (!(map = (t_node**)malloc(sizeof(t_node*) * count)))
		return (NULL);
	split = NULL;
	if (fd < 0)
		return (NULL);
	if (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line,' ');	
		leng = ft_splitlen(split);
		map = convert_map(split, map);
	}
	else
		ft_putstr("Erreur dans l'ouverture du fichier");
	
	while (get_next_line(fd, &line) > 0)
	{
		map = (t_node**)ft_realloc((void*)map,sizeof(t_node*) * (count + 1), sizeof(t_node*) * count);
		split = ft_strsplit(line, ' ');
		ft_putstr("Pass");
		if (ft_splitlen(split) != leng)
			//ft_putstr("error");
		map = convert_map(split, map);
		count++;
	}
	ft_putstr(" ess ; ");
	ft_putnbr(map[2][1].z);
	ft_putnbr(leng);
	display_map(map, leng);
	return (map);
}
