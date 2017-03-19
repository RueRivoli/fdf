/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:11:10 by fgallois          #+#    #+#             */
/*   Updated: 2017/03/10 15:11:16 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node  **rotation_y(t_node **map, int len_x, int len_y)
{
    
    t_node **new;
    t_node *add;
    int z;
    int x;
    int i;
    int j;

    if (len_x == 0 || !(new = ft_memalloc(sizeof(t_node*) * len_x)))
        return (NULL);
    j = 0;
    while (j < len_y)
    {
        new[j] = ft_memalloc(sizeof(t_node) * len_x);
        i = 0;
        
        while (i < len_x)
        {
            
            x = map[j][i].x + CTE * map[j][i].y;
            z = map[j][i].z + (CTE / 2 ) * map[j][i].y;
            
            /*ft_putnbr((int)x);
            ft_putstr(" , ");
            ft_putnbr((int)z);*/
            add = init_node((int)x, map[j][i].y, (int)z , map[j][i].color);
            new[j][i] = *add;
            i++;
        }
        j++;
    }
    return (new);
}

t_node  **proj_z(t_node **map, int len_x, int len_y)
{
    
    t_node **new;
    t_node *add;
    int x;
    int y;
    int i;
    int j;

    if (len_x == 0 || !(new = ft_memalloc(sizeof(t_node*) * len_x)))
        return (NULL);
    j = 0;
    while (j < len_y)
    {
        new[j] = ft_memalloc(sizeof(t_node) * len_x);
        i = 0;
        while (i < len_x)
        {
            x = map[j][i].x - CTE * map[j][i].z;
            y = map[j][i].y - CTE * map[j][i].z;
            //y = map[j][i].y + cos(THETA) * map[j][i].y + sin(THETA) * map[j][i].y;
            //x = map[j][i].x -sin(THETA) * map[j][i].y + cos(THETA)* map[j][i].x;
            add = init_node((int)x, (int)y, map[j][i].z , map[j][i].color);
            new[j][i] = *add;
            i++;
        }
        j++;
    }
    return (new);
}

t_node  **rotation_z(t_node **map, int len_x, int len_y)
{
    
    t_node **new;
    t_node *add;
    int x;
    int y;
    int i;
    int j;

    if (len_x == 0 || !(new = ft_memalloc(sizeof(t_node*) * len_x)))
        return (NULL);
    j = 0;
    while (j < len_y)
    {
        new[j] = ft_memalloc(sizeof(t_node) * len_x);
        i = 0;
        while (i < len_x)
        {
            y =  map[j][i].y + cos(THETA) * map[j][i].y + sin(THETA) * map[j][i].x;
            x =  map[j][i].x  + -sin(THETA) * map[j][i].y + cos(THETA)* map[j][i].x;
            add = init_node((int)x, (int)y, map[j][i].z , map[j][i].color);
            new[j][i] = *add;
            i++;
        }
        j++;
    }
    return (new);
}