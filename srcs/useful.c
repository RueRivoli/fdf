/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:50:35 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/14 17:38:21 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			which_proj(t_env *env, t_mat *mat, t_node *node)
{
	if (env->type_proj == 0)
	{
		mat->z = node->z * env->moove_z;
		mat->x = CTE1 * node->x - CTE2 * node->y;
		mat->y = -2 * mat->z + (CTE1 / 2) * node->x + (CTE2 / 2) * node->y;
		if (env->type_proj == 0)
		{
			mat->x += 540;
			mat->y += 140;
		}
	}
	else if (env->type_proj == 1)
	{
		mat->z = node->z * env->moove_z;
		mat->x = node->x - CTE * mat->z;
		mat->y = node->y + (CTE / 2) * mat->z;
	}
}

float			proportion_altitude(t_env *env, t_node *node)
{
	return ((node->z - env->extr->min_z)\
			/ (env->extr->max_z - env->extr->min_z));
}

char			*hex_altitude(int rn, int gn, int bn)
{
	char	*hex;
	char	*str;

	if (!(str = ft_strnew(8)))
		return (NULL);
	hex = ft_itohex(rn);
	str[0] = '0';
	str[1] = 'x';
	str[2] = hex[0];
	str[3] = hex[1];
	if (hex != NULL)
		free(hex);
	hex = ft_itohex(gn);
	str[4] = hex[0];
	str[5] = hex[1];
	if (hex != NULL)
		free(hex);
	hex = ft_itohex(bn);
	str[6] = hex[0];
	str[7] = hex[1];
	if (hex != NULL)
		free(hex);
	return (str);
}

char			*altitude_color(t_env *env, t_node *node)
{
	float		delta;
	float		deltab;
	int			g;
	char		*st1;
	char		*st;

	delta = (float)node->z - env->extr->min_z;
	deltab = (float)env->extr->max_z - env->extr->min_z;
	if (deltab == 0.0)
		return (hex_altitude(255, 255, 255));
	delta = (float)delta / deltab;
	g = -255;
	st1 = ft_strsub("0xFFFFFF", 4, 2);
	g = (int)(ft_hextoint(st1) + delta * g);
	free(st1);
	st1 = ft_strsub("0xFFFFFF", 6, 2);
	free(st1);
	st1 = ft_strsub("0xFF0000", 2, 2);
	st = hex_altitude(ft_hextoint(st1),\
				g, (int)(ft_hextoint(st1) + delta * (-255)));
	free(st1);
	return (st);
}

int				temporaire(int fd, char *line, t_env *env, t_node **map)
{
	int		length;
	char	**split;

	split = NULL;
	if (fd < 0)
		return (0);
	if (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		free(line);
		length = ft_splitlen(split);
		if (!(map = convert_map(split, map, &env->bool_color)))
		{
			ft_freetab(split);
			return (0);
		}
	}
	else
		return (0);
	ft_freetab(split);
	return (length);
}
