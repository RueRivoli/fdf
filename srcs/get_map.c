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


void				rescale(t_env *env)
{
	int x;
	int y;
	y = 0;
	while (env->map[y])
	{
		x = 0;
		while (x < env->len)
		{
			env->map[y][x].x = x * FENE_X / (env->len - 1);
			env->map[y][x].y = y * FENE_Y / (env->len - 1);
			x++; 
		}

		y++;
	}
}

static t_node		**convert_map(char **split, t_node **map)
{
	int len;
	static int y;
	int x;
	t_node *new;
	char **sp;

	sp = NULL;
	len = ft_splitlen(split);
	ft_putstr(" Ligne ");
	ft_putnbr(y);
	ft_putstr(" : ");
	//ft_putchar('\n');
	map[y] = ft_memalloc(sizeof(t_node) * (len + 1));
	map[y + 1] = NULL; 
	x = 0;
	if (!(map[y]))
	{
		free(map);
		return (NULL);
	}
	while (x < len)
	{

		if (ft_strchr(split[x], ',') == NULL)
		{
			
			new = init_node(x, y, ft_atoi(split[x]), 16777215);
		}
		else
		{
			sp = ft_strsplit(split[x], ',');
			new = init_node(x, y, ft_atoi(sp[0]), get_color(sp[1]));
		}
		ft_memcpy(map[y], new, sizeof(new));
		map[y][x] = *new;
		
		ft_putstr(" ");
		//display_node(&map[j][i]);
		//ft_putnbr(map[j][i].z);
		//ft_putchar('\n');
		x++;
	}
	y++;
	return (map);
}

t_node		**get_map(int fd, t_env *env)
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
	
	env->len = length;
	//ft_putnbr(env->len);	
	
	display_map(map, env->len);
	return (map);
}
