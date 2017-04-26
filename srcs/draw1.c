/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:45:45 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/10 11:52:16 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_vertical(t_env *env, t_node *node1, t_node *node2)
{
	int		y;
	int		x;
	int		z;
	t_node	new;

	x = node1->x;
	if (node1->y < node2->y)
	{
		y = node1->y + 1;
		while (y < node2->y)
		{
			z = node1->z + (y - node1->y) * \
				(node2->z - node1->z) / (node2->y - node1->y);
			new.x = x;
			new.y = y;
			new.z = (int)z;
			new.color_num = node1->color_num;
			mlx_put_pixel_to_image(env, &new);
			y++;
		}
	}
	else
		draw_vertical(env, node2, node1);
}

void			draw_horizontal(t_env *env, t_node *node1, t_node *node2)
{
	int		x;
	int		y;
	int		z;
	t_node	new;

	y = node1->y;
	if (node1->x < node2->x)
	{
		x = node1->x + 1;
		while (x < node2->x)
		{
			z = node1->z + (x - node1->x) * \
				(node2->z - node1->z) / (node2->x - node1->x);
			new.x = x;
			new.y = y;
			new.z = (int)z;
			new.color_num = node1->color_num;
			mlx_put_pixel_to_image(env, &new);
			x++;
		}
	}
	else
		draw_horizontal(env, node2, node1);
}

void			draw_soft_rise(t_env *env, t_node *node1, t_node *node2)
{
	int			x;
	int			y_new;
	int			z;
	t_node		new;

	if (node2->x < node1->x)
		draw_soft_rise(env, node2, node1);
	else
	{
		x = node1->x + 1;
		while (x < node2->x)
		{
			y_new = node1->y + ((node2->y - node1->y) * \
					(x - node1->x) / (node2->x - node1->x));
			z = node1->z + sqrt(pow(x - node1->x, 2) + \
				pow(y_new - node1->y, 2)) * (node2->z - node1->z) / \
				sqrt(pow(node2->x - node1->x, 2) + pow(node2->y - node1->y, 2));
			new.x = x;
			new.y = y_new;
			new.z = (int)z;
			new.color_num = node1->color_num;
			mlx_put_pixel_to_image(env, &new);
			x++;
		}
	}
}

void			draw_high_rise(t_env *env, t_node *node1, t_node *node2)
{
	int		x_new;
	int		y;
	int		z;
	t_node	new;

	if (node2->y < node1->y)
		draw_high_rise(env, node2, node1);
	else
	{
		y = node1->y + 1;
		while (y < node2->y)
		{
			x_new = node1->x + ((node2->x - node1->x) * \
					(y - node1->y) / (node2->y - node1->y));
			z = node1->z + sqrt(pow(x_new - node1->x, 2) +\
				pow(y - node1->y, 2)) * (node2->z - node1->z) / \
				sqrt(pow(node2->x - node1->x, 2) + pow(node2->y - node1->y, 2));
			new.x = (int)x_new;
			new.y = y;
			new.z = (int)z;
			new.color_num = node1->color_num;
			mlx_put_pixel_to_image(env, &new);
			y++;
		}
	}
}
