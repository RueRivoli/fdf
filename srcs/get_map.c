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

void				get_extreme(t_env *env)
{
	int i;
	int j;
	t_node **map;
	//int min_x;
	//int min_y;
	//int max_x;
	//int max_y;

	//min_x = SIZE_X;
	//min_y = SIZE_Y;
	//max_x = 0;
	//max_y = 0;
	map = env->map;
	j = 0;
	while (j < env->len_y)
	{
		i = 0;
		while (i < env->len_x)
		{
			if (map[j][i].x < env->min_x)
				env->min_x = map[j][i].x;
			if (map[j][i].x > env->max_x)
				env->max_x = map[j][i].x;
			if (map[j][i].y < env->min_y)
				env->min_y = map[j][i].y;
			if (map[j][i].y > env->max_y)
				env->max_y = map[j][i].y;
			i++;
		}
		j++;
	}
}

void				scale(t_env *env)
{
	int x;
	int y;
	y = 0;
	t_node **map;
	map = env->map;
	while (y < env->len_y)
	{
		x = 0;
		ft_putnbr(y);
		while (x < env->len_x)
		{
			env->map[y][x].x = FENE_X / 8 + (map[y][x].x - env->min_x) * 7 * FENE_X /  (8 * (env->max_x - env->min_x));
			env->map[y][x].y = FENE_Y / 8  + (map[y][x].y - env->min_y) * 7 * FENE_Y / (8 * (env->max_y - env->min_y));
			x++; 
		}
		y++;
	}
}

void				rescale(t_env *env)
{
	int x;
	int y;
	y = 0;
	while (env->map[y])
	{
		x = 0;
		while (x < env->len_x)
		{
			env->map[y][x].x = FENE_X / 8 + x * FENE_X * 7 / (8 * env->len_x - 1);
			env->map[y][x].y = FENE_Y / 8 + y * FENE_Y * 7 / (8 * env->len_y - 1);
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
		//ft_memcpy(map[y], new, sizeof(new));
		map[y][x] = *new;
		
		//ft_putstr(" ");
		//display_node(&map[j][i]);
		//ft_putnbr(map[y][x].x);
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
	
	env->len_x = length;
	env->len_y = count;
	
	//display_map(map, env->len_x);
	return (map);
}
