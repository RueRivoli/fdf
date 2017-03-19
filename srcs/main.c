/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 11:04:35 by fgallois          #+#    #+#             */
/*   Updated: 2017/03/02 18:22:39 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "fdf.h"


int		main(int argc, char **argv)
{
	int fd;
	t_env *env;

	fd = 0;
	if (argc != 2)
	{
		ft_putstr("usage: fdf [map.fdf]");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_putstr("erreur dans le fichier");

	//Initiation de l'environnement
	//Récupération de la map
	
				
	env = init_env(fd);
	
	rescale(env);
	
	//env->map = rotation_y(env->map, env->len_x, env->len_y);
	env->map = rotation_z(env->map, env->len_x, env->len_y);
	env->map = proj_z(env->map, env->len_x, env->len_y);
	get_extreme(env);
	ft_putnbr(env->min_x);
	scale(env);
	

	//display_map(env->map, env);

	draw_map(env);
	
	draw_link(env);

	mlx_put_image_to_window(env->mlx, env->win, (env->img)->img, 0, 0);
	//mlx_string_put(env->mlx, env->win, 695, 791, 0xAEECFE, "Current zoom x");
	//mlx_string_put(env->mlx, env->win, 839, 791, 0xAEECFE, "Magic");
	
	mlx_loop(env->mlx);
	return (0);
}
