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

 int		get_color(char *str)
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


char		*homogene_color(char *str)
{
	int i;
	int j;
	char *str_new;

	
	i = 0;
	while (str[i])
		i++;
	if (i == 8)
		return (str);
	else if (i < 8)
	{
		if (!(str_new = ft_strnew(8)))
			return (NULL);
		str_new = ft_strncpy(str_new, str, i);
		j = i;
		while (j < 8)
		{
			str_new[j] = '0';
			j++;
		}
		return (str_new);
	}
	return (NULL);
}

/*void				get_extreme(t_env *env, t_node **map)
{
	int i;
	int j;
	j = 0;
	env->extr->min_z = map[0][0].z;
	env->exmax_z = map[0][0].z;
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
			if (map[j][i].z > env->max_z)
				env->max_z = map[j][i].z;
			if (map[j][i].z < env->min_z)
				env->min_z = map[j][i].z;
			i++;
		}
		j++;
	}
}*/

/*void				scale(t_env *env, t_node **map)
{
	int x;
	int y;
	y = 0;
	while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
			map[y][x].x = FENE_X / 8 + (map[y][x].x - env->min_x) * 6 * FENE_X /  (8 * (env->max_x - env->min_x));
			map[y][x].y = FENE_Y / 8  + (map[y][x].y - env->min_y) * 6 * FENE_Y / (8 * (env->max_y - env->min_y));
			x++; 
		}
		y++;
	}
}*/

void				rescale(t_env *env, t_node **map)
{
	int x;
	int y;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (x < env->len_x)
		{
			map[y][x].x = FENE_X / 8 + x * FENE_X * 6 / (8 * env->len_x - 1);
			map[y][x].y = FENE_Y / 8 + y * FENE_Y * 6 / (8 * env->len_y - 1);
			x++; 
		}
		y++;
	}
}

static t_node		**convert_map(char **split, t_node **map, int *bool_color)
{
	int len;
	static int y;
	int x;
	t_node *new;
	char **sp;
	int k;

	sp = NULL;
	len = ft_splitlen(split);
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
			if (ft_isnumber(split[x]) == 0)
				return (NULL);
			new = init_node(x, y, ft_atoi(split[x]), get_color("0xFFFFFF"));
		}
		else
		{
			*bool_color = 1;
			k = 0;
			sp = ft_strsplit(split[x], ',');
			if (ft_isnumber(sp[0]) == 0)
				return (NULL);
			else if (get_color(sp[1]) == -1)
				new = init_node(x, y, ft_atoi(sp[0]), get_color("0xFFFFFF"));
			else
			{
				new = init_node(x, y, ft_atoi(sp[0]), get_color(sp[1]));
				//ft_putnbr(ft_get_color_mlx((const char)sp[1], &k));
				//ft_putchar('\n');
			}
		}
		map[y][x] = *new;
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
		if (!(map = convert_map(split, map, &env->bool_color)))
			return (NULL);
	}
	else
	{
		//ft_putstr("Erreur dans l'ouverture du fichier");
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
	{
		map = (t_node**)ft_realloc((void*)map,sizeof(t_node*) * (count + 1), sizeof(t_node*) * count);
		split = ft_strsplit(line, ' ');
		/*if (ft_splitlen(split) != length)
		{
			return (NULL);
		}*/
		if (!(map = convert_map(split, map, &env->bool_color)))
			return (NULL);
		count++;
	}
	
	env->len_x = length;
	env->len_y = count;
	free(split);
	//display_map(map, env->len_x);
	return (map);
}
