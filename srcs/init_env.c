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


void	new_one(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->back_img = NULL;
	env->sup_img = NULL;
	env->church_img = NULL;
	env->len_x = 0;
	env->len_y = 0;
	env->min_x = SIZE_X;
	env->min_y = SIZE_Y;
	env->max_x = 0;
	env->max_y = 0;
	env->min_z = 0;
	env->max_z = 0;

}

void	new_two(t_env *env)
{
	env->x = 0;
	env->y = 0;
	env->zoom = 1.0;
	env->trans_x = 0;
	env->trans_y = 0;
	env->moove_z = 1.0;
	env->rot_x = 0;
	env->rot_y = 0;
	env->rot_z = 0;
	env->filename = "";
	env->type_proj = 0;
	env->bool_color = 0;
	env->mat.x = 0;
	env->mat.y = 0;
	env->mat.z = 0;
	env->mat.a = 0;
	env->mat.b = 0;
	env->mat.c = 0;
}

t_env		*new_env()
{
	t_env *env;
	
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new_one(env);
	new_two(env);
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
	if (!(env->map = get_map(fd, env)))
		return (NULL);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, SIZE_X, SIZE_Y, "Fdf de fgallois");
	env->img = init_img(env, FENE_X, FENE_Y);
	env->back_img = init_img(env, SIZE_X, SIZE_Y);
	env->sup_img = init_img(env, SUPP_X, SUPP_Y);
	env->church_img = init_img(env, CHURCH, CHURCH);
	env->filename = get_file_name(av1);
	fill_img(env, &h, &w);
	return (env);
}
