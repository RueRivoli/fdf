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
	char **sp;

	i = 0;
	sp = NULL;
	err44 = -42;
	len = ft_splitlen(split);
	ft_putstr(" Ligne ");
	ft_putnbr(j);
	ft_putstr(" : ");
	//ft_putchar('\n');
	map[j] = ft_memalloc(sizeof(t_node) * (len + 1));
	if (!(map[j]))
	{
		free(map);
		return (NULL);
	}
	while (i < len)
	{
		if (ft_strchr(split[i], ',') == NULL)
		{
			new = init_node(i, j, ft_atoi(split[i]), 16777215);
			//get_color(split[i])
		}
		else
		{
			sp = ft_strsplit(split[i], ',');
			new = init_node(i, j, ft_atoi(sp[0]), get_color(sp[1]));
		}
		ft_memcpy(map[j], new, sizeof(new));
		map[j][i] = *new;
		//display_node(&map[j][i]);
		//ft_putnbr(map[j][i].z);
		//ft_putchar('\n');
		i++;
	}
	j++;
	return (map);
}

t_node		**get_map(int fd, int len)
{
	char *line;
	int length;
	char **split;
	t_node **map;
	int count;

	map = NULL;
	line = NULL;
	length = 0;
	count = 1;
	if (!(map = ft_memalloc(sizeof(t_node*) * count)))
		return (NULL);
	split = NULL;
	if (fd < 0)
		return (NULL);
	if (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line,' ');	
		length = ft_splitlen(split);
		map = convert_map(split, map);
	}
	else
		ft_putstr("Erreur dans l'ouverture du fichier");
	while (get_next_line(fd, &line) > 0)
	{
		map = (t_node**)ft_realloc((void*)map,sizeof(t_node*) * (count + 1), sizeof(t_node*) * count);
		split = ft_strsplit(line, ' ');
		if (ft_splitlen(split) != length)
			ft_putstr("error");
		map = convert_map(split, map);
		ft_putchar('\n');
		count++;
	}
	len = length;
	//display_map(map, leng);
	return (map);
}
