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

t_env 		*handle_error(int argc, char **argv)
{
	int fd;
	t_env *env;

	fd = 0;
	if (argc != 2)
	{
		ft_putstr("usage: fdf [map.fdf]\n");
		return (NULL);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		error_no_file();
		return (NULL);
	}	

	if (!(ft_strstr(argv[1], ".fdf")) || !(env = init_env(fd, argv[1])))
	{
		error_no_conform();
		return (NULL);
	}
	return (env);
}

void	ft_hook(t_env *env)
{
	mlx_key_hook(env->win, key_funct, &env->mlx);
	mlx_mouse_hook(env->win, &mouse_funct, &env->mlx);
	mlx_expose_hook(env->win, &print_title, &env->mlx);
	mlx_loop(env->mlx);
}

int		main(int argc, char **argv)
{
	//t_node **pix;
	t_env *env;

	//pix = NULL;
	if (!(env = handle_error(argc, argv)))
		return (0);
	
	//ft_putstr("champion");
	rescale(env, env->map);
	//env->map = proj_iso(env, env->map);
	//pix = proj_iso(env, env->map);
	//get_extreme(env, env->map);
	//scale(env, env->map);
	

	//display_map(pix, env);

	draw_map(env, env->map);
	//draw_link(env, env->map);
	print_all(env);

	ft_hook(env);
	//free(pix);
	free(env);
	free(env->map);
	free(env->img);
	free(env);
	return (0);
}
