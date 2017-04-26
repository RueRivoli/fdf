/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:11:09 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/26 14:40:57 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		mlx_put_pixel_to_image(t_env *env, t_node *node)
{
	int		octet;
	char	*color_new;
	int		a;

	octet = env->img->bpp / 8;
	color_new = NULL;
	if (env->bool_color == 0)
	{
		color_new = altitude_color(env, node);
		a = get_color(color_new);
		free(color_new);
	}
	else
		a = node->color_num;
	if (node->x >= 0 && node->y >= 0 && node->x < FENE_X && node->y < FENE_Y)
	{
		ft_memcpy(&env->img->data[octet * node->x + env->img->sizeline * \
	node->y], &a, octet);
	}
}

t_img		*init_img(t_env *env, int height, int width)
{
	t_img	*image;

	if (!(image = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	image->img = mlx_new_image(env->mlx, height, width);
	image->data = mlx_get_data_addr(image->img,\
	&image->bpp, &image->sizeline, &image->endian);
	return (image);
}

int			fill_img(t_env *env)
{
	int		h;
	int		w;

	h = HEIGHT_DRAW;
	w = WIDTH_DRAW;
	ft_putstr("automne");
	if (!(env->back_img->img = mlx_xpm_file_to_image(env->mlx, \
			"../../../../Users/fgallois/images/magnifique_black.xpm", &w, &h)))
		return (0);
	ft_putstr("hiver");
	if (!(env->church_img->img = mlx_xpm_file_to_image(env->mlx, \
			"../../../../Users/fgallois/images/church.xpm", &w, &h)))
		return (0);
	if (!(env->sup_img->img = mlx_xpm_file_to_image(env->mlx, \
			"../../../../Users/fgallois/images/blancdim.XPM", &w, &h)))
		return (0);
	return (1);
}
