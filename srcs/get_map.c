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


static t_node			*intermediate(char **split, int x, int y, int *bool_color)
{
	char **sp;
	t_node *new;
	sp = NULL;
	
		if (ft_strchr(split[x], ',') == NULL)
		{
			
			if (ft_isnumber(split[x]) == 0)
				return (NULL);
				
			new = init_node(x, y, ft_atoi(split[x]), get_color("0xFFFFFF"));
		}
		else
		{
			
			*bool_color = 1;
			sp = ft_strsplit(split[x], ',');
			
			if (ft_isnumber(sp[0]) == 0)
				return (NULL);
			else if (get_color(sp[1]) == -1)
				new = init_node(x, y, ft_atoi(sp[0]), get_color("0xFFFFFF"));
			else
			{
				new = init_node(x, y, ft_atoi(sp[0]), get_color(sp[1]));
			}
		}
		//ft_freetab(sp);
		return (new);
}


static t_node		**convert_map(char **split, t_node **map, int *bool_color)
{
	int len;
	static int y;
	int x;
	

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
		
		map[y][x] = *intermediate(split, x, y, bool_color);
		
		x++;
	}
	y++;
	return (map);
}

static	int	temporaire(int fd, char *line, t_env *env, t_node **map)
{
	int length;
	char **split;

	split = NULL;
	if (fd < 0)
		return (0);
	if (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line,' ');	
		length = ft_splitlen(split);
		
		if (!(map = convert_map(split, map, &env->bool_color)))
			return (0);
	}
	else
		return (0);
	return (length);
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
	if ((length = temporaire(fd, line, env, map)) == 0)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		map = (t_node**)ft_realloc((void*)map,sizeof(t_node*) * (count + 1), sizeof(t_node*) * count);
		split = ft_strsplit(line, ' ');
		if (!(map = convert_map(split, map, &env->bool_color)))
			return (NULL);
		count++;
	}
	env->len_x = length;
	env->len_y = count;
	ft_freetab(split);
	return (map);
}
