/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:30:54 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/10 12:32:52 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			print_image_back(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, (env->back_img)->img, 0, 0);
}

void			print_image_supp(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, (env->sup_img)->img, 320, 80);
}

void			print_image_graph(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, (env->img)->img, 360, 100);
}

void			print_image_sign(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, \
			(env->church_img)->img, 30, 750);
}

void			print_coord(int x, int y, t_env *env)
{
	char *c;
	char *d;

	print_all(env);
	print_title(env);
	env->x = x - 360;
	env->y = y - 100;
	c = ft_itoa(env->x);
	d = ft_itoa(env->y);
	mlx_string_put(env->mlx, env->win, 190, 300, 0x3A5FCD, c);
	mlx_string_put(env->mlx, env->win, 190, 360, 0x3A5FCD, d);
	free(c);
	free(d);
}
