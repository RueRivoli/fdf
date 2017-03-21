/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:55:13 by fgallois          #+#    #+#             */
/*   Updated: 2017/03/02 17:24:37 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "define.h"
#include "fdf.h"

t_env		*new_env()
{
	t_env *env;
	
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->back_img = NULL;
	env->sup_img = NULL;
	env->len_x = 0;
	env->len_y = 0;
	env->min_x = SIZE_X;
	env->min_y = SIZE_Y;
	env->max_x = 0;
	env->max_y = 0;
	env->x = 0;
	env->y = 0;
	env->filename = "";
	return (env);
}

t_env	*init_env(int fd, char *av1)
{
	t_env *env;
	int h;
	int w;

	h = HEIGHT_DRAW;
	w = WIDTH_DRAW;
	if (!(env = new_env()))
		return (NULL);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, SIZE_X, SIZE_Y, "Fdf de fgallois");
	env->map = get_map(fd, env);
	env->img = init_img(env, FENE_X, FENE_Y);
	env->back_img = init_img(env, SIZE_X, SIZE_Y);
	env->sup_img = init_img(env, SUPP_X, SUPP_Y);
	env->filename = get_file_name(av1);
	ft_putstr(env->filename);
	fill_img(env, &h, &w);
	/*ft_putstr("Data :");
	ft_putstr((env->img)->data);
	ft_putstr(" Bpp :");
	ft_putnbr((env->img)->bpp);
	ft_putstr(" Sizeline :");
	ft_putnbr((env->img)->sizeline);
	ft_putstr(" Endian :");
	ft_putnbr(env->img->endian);*/
	
	
	return (env);
}
