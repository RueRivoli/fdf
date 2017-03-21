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
	scale(env);
	

	//display_map(env->map, env);

	draw_map(env);
	
	draw_link(env);

	print_image(env);
	/*mlx_put_image_to_window(env->mlx, env->win, (env->back_img)->img, 0, 0);
	mlx_put_image_to_window(env->mlx, env->win, (env->sup_img)->img, 360, 80);
	mlx_put_image_to_window(env->mlx, env->win, (env->img)->img, 400, 100);*/
	/*mlx_string_put(env->mlx, env->win, 900, 10, 0x3A5FCD, "FDF");
	mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");
	mlx_string_put(env->mlx, env->win, 70, 300, 0x3A5FCD, ft_itoa());
	mlx_string_put(env->mlx, env->win, 50, 360, 0x3A5FCD, "Current y : ");
	mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");
	mlx_string_put(env->mlx, env->win, 50, 420, 0x3A5FCD, "Altitude : ");
	mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");*/
	//mlx_key_hook(env->win, key_funct, &env->mlx);
	mlx_mouse_hook(env->win, &mouse_funct, &env->mlx);
	mlx_expose_hook(env->win, &print_title, &env->mlx);
	//mlx_string_put(env->mlx, env->win, 839, 791, 0xAEECFE, "Magic");
	
	mlx_loop(env->mlx);
	return (0);
}
