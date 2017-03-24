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

void	error_no_conform(void)
{
	ft_putstr("Le fichier n'est pas conforme \n");
}

void	error_no_file(void)
{
	ft_putstr("Le fichier n'existe pas\n");
}

char 	*get_file_name(char *av1)
{
	char *st;
	
	st = NULL;
	if (ft_ispresent(av1, '/') == 1)
	{
		st = ft_strrchr(av1, '/');
		st++;
	}
	else
		st = av1;
	return (ft_strsub(st, 0, ft_strlen(st) - 4));
}

int		main(int argc, char **argv)
{
	int fd;
	t_env *env;	
	t_node **pix;

	
	fd = 0;
	if (argc != 2)
	{
		ft_putstr("usage: fdf [map.fdf]\n");
		return (0);
	}
	if (!(ft_strstr(argv[1], ".fdf")))
	{
		error_no_conform();
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		error_no_file();
		return (0);
	}

	

	//Initiation de l'environnement
	//Récupération de la map : partie obligatoire
	
			
	if (!(env = init_env(fd, argv[1])))
	{
		error_no_conform();
		return (0);
	}
	ft_putstr("Point");
	rescale(env, env->map);
	//env->map = rotation_y(env->map, env->len_x, env->len_y);
	//env->map = rotation_z(env->map, env->len_x, env->len_y);
	pix = proj_iso(env, env->map);
	//env->map = proj_con(env->map, env, env->len_x, env->len_y);
	get_extreme(env, pix);
	//scale(env, env->map);
	//scale(env, pix);
	

	//display_map(env->map, env);

	draw_map(env, pix);
	
	draw_link(env, pix);
	
	print_all(env);

	

	mlx_key_hook(env->win, key_funct, &env->mlx);
	mlx_mouse_hook(env->win, &mouse_funct, &env->mlx);
	mlx_expose_hook(env->win, &print_title, &env->mlx);
	
	mlx_loop(env->mlx);
	free(env->map);
	free(env->img);
	free(env);
	return (0);
}
