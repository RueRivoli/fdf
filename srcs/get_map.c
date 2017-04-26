/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:09:54 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/14 17:50:51 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					get_color(char *str)
{
	int		i;

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
	int		x;
	int		y;

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

static t_node		*intermediate(char **split, int x, int y, int *bool_color)
{
	char	**sp;
	t_node	*new;

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
		{
			ft_freetab(sp);
			return (NULL);
		}
		else if (get_color(sp[1]) == -1)
			new = init_node(x, y, ft_atoi(sp[0]), get_color("0xFFFFFF"));
		else
			new = init_node(x, y, ft_atoi(sp[0]), get_color(sp[1]));
		ft_freetab(sp);
	}
	return (new);
}

t_node				**convert_map(char **split, t_node **map, int *bool_color)
{
	int			len;
	static int	y;
	int			x;
	t_node		*new;

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
		new = intermediate(split, x, y, bool_color);
		map[y][x] = *new;
		free(new);
		x++;
	}
	y++;
	return (map);
}

t_node				**get_map(int fd, t_env *env)
{
	char		*line;
	int			length;
	char		**split;
	t_node		**map;
	int			count;

	line = NULL;
	count = 1;
	if (!(map = ft_memalloc(sizeof(t_node*) * count)))
		return (NULL);
	if ((length = temporaire(fd, line, env, map)) == 0)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		map = (t_node**)ft_realloc((void*)map, sizeof(t_node*) \
				* (count + 1), sizeof(t_node*) * count);
		split = ft_strsplit(line, ' ');
		if (convertion(split, map, &env->bool_color, line) == 0)
			return (NULL);
		count++;
	}
	free(line);
	fill_length(env, length, count);
	return (map);
}
