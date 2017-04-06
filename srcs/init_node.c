/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:55:13 by fgallois          #+#    #+#             */
/*   Updated: 2017/03/03 11:03:02 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node		*new_node()
{
	t_node *node;

	if (!(node = (t_node*)ft_memalloc(sizeof(t_node))))
		return (NULL);
	node->x = 0;
	node->y = 0;
	node->z = 0;
	node->color_num = 0;
	node->rap = 0.0;
	return (node);
}

t_node		*init_node(int x0, int y0, int z0, int color_num0)
{
	t_node *node;

	if (!(node = new_node()))
		return (NULL);
	node->x = x0;
	node->y = y0;
	node->z = z0;
	node->color_num = color_num0;
	return (node);
}

void		display_node(t_node *node)
{
	ft_putstr("x : ");
	ft_putnbr(node->x);
	ft_putstr(" y : ");
	ft_putnbr(node->y);
	ft_putstr(" z : ");
	ft_putnbr(node->z);
	ft_putstr(" color : ");
	ft_putnbr(node->color_num);
}

void		display_map(t_node **map, t_env *env)
{
	int x;
	int y;
	ft_putstr("fre");
	y = 0;
	if (!map)
		ft_putstr("Erreur dans la map");
	while (y < env->len_y)
	{
		 x = 0;
		while (x < env->len_x)
		{		
			ft_putnbr(map[y][x].z);
			ft_putchar(',');
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
