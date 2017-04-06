/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:45:45 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/06 17:01:01 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			which_proj(t_env *env, t_mat *mat, t_node *node)
{
	if (env->type_proj == 0)
	{
		mat->z = node->z * env->moove_z;
		mat->x = CTE1 * node->x - CTE2 * node->y;
		mat->y = -2 * mat->z + (CTE1 / 2) * node->x + (CTE2 / 2) * node->y;
		if (env->type_proj == 0)
		{
			mat->x += 540;
			mat->y += 140;
		}
	}
	else if (env->type_proj == 1)
	{
		mat->z = node->z * env->moove_z;
		mat->x = node->x - CTE * mat->z;
		mat->y = node->y + (CTE / 2) * mat->z;
	}
}

float			proportion_altitude(t_env *env, t_node *node)
{
	return ((node->z - env->extr->min_z)\
			/ (env->extr->max_z - env->extr->min_z));
}

void			draw_map(t_env *env, t_node **map)
{
	int		y;
	int		x;
	t_node	*new;

	y = 0;
	new = NULL;
	get_extreme_after_transform(env, map);
	while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
			new = NULL;
			new = new_coord(env, &map[y][x]);
			if (x != env->len_x - 1)
				draw_segment(env, new, new_coord(env, &map[y][x + 1]));
			if (y != env->len_y - 1)
				draw_segment(env, new, new_coord(env, &map[y + 1][x]));
			mlx_put_pixel_to_image(env, new);
			free(new);
			x++;
		}
		y++;
	}
}

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
