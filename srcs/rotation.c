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

/*t_node **rotation(t_node **map, int len)
{
    t_node **new;
    t_node *add;
    int i;
    int j;
    int z;
    int y;

    z = 0;
    x = 0;
    if (len == 0 || !(new = ft_memalloc(sizeof(t_node*) * len))
        return (NULL);
    i = 0;
    j = 0;
    while (map[i])
    {
        new[i] = ft_memalloc(sizeof(t_node) * ft_strlen(map[0]));
        while (map[i][j])
        {
            y = cos(theta) * map[i][j].y + sin(theta) * map[i][j].z;
            z = -sin(theta) * map[i][j].y + cos(theta)* map[i][j].z;
            add = init_node(i, y, z , map[i][j].color);
            new[i][j] = add;
            j++;
        }
        i++;
    }
    return (new);
}*/
