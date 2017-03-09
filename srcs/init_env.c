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

t_img		*init_img(t_env *env)
{
	t_img	*image;

	if (!(image = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	image->img = mlx_new_image(env, SIZE_X, SIZE_Y);
	image->data = mlx_get_data_addr(env, &image->bpp, &image->sizeline, &image->endian);
	return (image);
}

t_env		*new_env()
{
	t_env *env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx = NULL;
	env->win = NULL;
	env->img = init_img(env);
	return (env);
}

t_env	*init_env(int fd)
{
	t_env *env;

	if (!(env = new_env()))
		return (NULL);
	//env->mlx = mlx_init();
	//env->win = mlx_new_window(env, SIZE_X, SIZE_Y, "notre fenetre");
	//env->img = init_img(env);
	env->map = get_map(fd);
	return (env);
}
