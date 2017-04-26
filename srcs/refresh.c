/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:32:57 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/14 17:53:57 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		refresh(t_env *env)
{
	ft_bzero(env->img->data, env->img->bpp * FENE_X \
			+ env->img->sizeline * FENE_Y);
	mlx_destroy_image(env->mlx, env->img);
	env->img = init_img(env, FENE_X, FENE_Y);
	draw_map(env, env->map);
	print_image_graph(env);
}

void		to_other(t_env *env, int i)
{
	if (i != env->type_proj)
	{
		env->type_proj = i;
		env->zoom = 1.0;
		env->trans_x = 0;
		env->trans_y = 0;
		env->moove_z = 1.0;
		env->rot_z = 0;
		refresh(env);
	}
}

void		reinitialise(t_env *env)
{
	env->rot_x = 0;
	env->rot_y = 0;
	env->rot_z = 0;
	env->trans_x = 0;
	env->trans_y = 0;
	env->zoom = 1.0;
	env->moove_z = 1.0;
	refresh(env);
}

void		fill_length(t_env *env, int length, int count)
{
	env->len_x = length;
	env->len_y = count;
}

int			convertion(char **split, t_node **map, int *bo, char *line)
{
	if (!(map = convert_map(split, map, bo)))
	{
		free(line);
		ft_freetab(split);
		free(map);
		return (0);
	}
	free(line);
	ft_freetab(split);
	return (1);
}
