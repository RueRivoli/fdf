/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:21:37 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/14 17:18:02 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			print_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win, 1680, 115, 0xd6b017, " M E N U ");
	mlx_string_put(env->mlx, env->win, 1650, 150, 0xD3D3DA, "Sortir : Echap");
	mlx_string_put(env->mlx, env->win, 1650, 200, 0xD3D3DA,\
			"Projection Para : P");
	mlx_string_put(env->mlx, env->win, 1650, 250, 0xD3D3DA,\
			"Projection Iso : I");
	mlx_string_put(env->mlx, env->win, 1650, 300, 0xD3D3DA,\
			"Start : O");
	mlx_string_put(env->mlx, env->win, 1650, 350, 0xD3D3DA,\
			"Plus d'altitude : +");
	mlx_string_put(env->mlx, env->win, 1650, 400, 0xD3D3DA,\
			"Moins d'altitude : -");
	mlx_string_put(env->mlx, env->win, 1650, 450, 0xD3D3DA,\
			"Zoom : scroll arriere");
	mlx_string_put(env->mlx, env->win, 1650, 500, 0xD3D3DA,\
			"Dezoom : scroll avant");
	mlx_string_put(env->mlx, env->win, 1650, 550, 0xD3D3DA,\
			"Deplacement : fleches");
	mlx_string_put(env->mlx, env->win, 1650, 600, 0xD3D3DA,\
			"Rotation : R & T");
	return (0);
}

int			print_title(t_env *env)
{
	mlx_string_put(env->mlx, env->win, 850, 30, 0xd6b017, "File name : ");
	mlx_string_put(env->mlx, env->win, 1000, 30, 0xd6b017, env->filename);
	mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");
	mlx_string_put(env->mlx, env->win, 50, 360, 0x3A5FCD, "Current y : ");
	mlx_string_put(env->mlx, env->win, 30, 600, 0xFB9800, \
			" \"Success consists of going");
	mlx_string_put(env->mlx, env->win, 30, 650, 0xFB9800,\
			" from failure to failure ");
	mlx_string_put(env->mlx, env->win, 30, 700, 0xFB9800,\
			" without loss of enthusiasm\"");
	mlx_string_put(env->mlx, env->win, 30, 1030, 0x3A5FCD,\
			"http://github.com/RueRivoli");
	return (print_menu(env));
}

void		print_all(t_env *env)
{
	print_image_back(env);
	print_image_sign(env);
	print_image_supp(env);
	print_image_graph(env);
}
