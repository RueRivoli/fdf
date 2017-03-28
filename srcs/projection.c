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


void    transform(t_env *env, t_node **map, t_node **new, int j)
{
    int i;
    t_node *add;
    t_mat mat;

    mat = env->mat;
    i = 0;
    while (i < env->len_x)
    {
            mat.z = map[j][i].z * env->moove_z;
            mat.x = CTE1 * map[j][i].x - CTE2 * map[j][i].y;
            mat.y = -2 * mat.z + (CTE1/2) * map[j][i].x + (CTE2/2) * map[j][i].y;

            mat.c = mat.x;
            mat.x = env->zoom * mat.x + 15 * env->trans_x;
            mat.y = env->zoom * mat.y + 15 * env->trans_y;
            mat.z = mat.z * env->zoom;
            mat.x = mat.x * cos(THETA * env->rot_z) + mat.y * sin(THETA * env->rot_z);
            mat.y =  - mat.c * sin(THETA * env->rot_z) + mat.y * cos(THETA * env->rot_z);

            mat.a = mat.y;
            mat.y =  mat.y * cos(THETA * env->rot_x) + mat.z * sin(THETA * env->rot_x);
            mat.z =  - mat.a * sin(THETA * env->rot_x) + mat.z * cos(THETA * env->rot_x);
            mat.b = mat.z;

            mat.z =  mat.z * cos(THETA * env->rot_y) - mat.x * sin(THETA * env->rot_y);
            mat.x = - mat.b * sin(THETA * env->rot_y) + mat.x * cos(THETA * env->rot_y);
            add = init_node((int)mat.x, (int)mat.y, (int)mat.z , map[j][i].color);
            new[j][i] = *add;
            i++;
        }
}


t_node  **proj_iso(t_env *env, t_node **map)
{
    t_node **new;
    int j;
    
    if (env->len_x == 0 || !(new = ft_memalloc(sizeof(t_node*) * env->len_x)))
        return (NULL);
    j = 0;
    while (j < env->len_y)
    {
        new[j] = ft_memalloc(sizeof(t_node) * env->len_x);
        transform(env, map, new, j);
        j++;
    }
    return (new);
}

t_node  **proj_para(t_env *env, t_node **map)
{
    
    t_node **new;
    t_node *add;
    int x;
    int y;
    int z;
    int i;
    int j;
    int b;
    int a;
    int c;
    if (env->len_x == 0 || !(new = ft_memalloc(sizeof(t_node*) * env->len_x)))
        return (NULL);
    j = 0;
    while (j < env->len_y)
    {
        new[j] = ft_memalloc(sizeof(t_node) * env->len_x);
        i = 0;
        while (i < env->len_x)
        {
            z = map[j][i].z * env->moove_z;
            x = map[j][i].x - CTE * z;
            y = map[j][i].y + (CTE/2) * z;

            x = env->zoom * x + 15 * env->trans_x;
            y = env->zoom * y + 15 * env->trans_y;
            z = z * env->zoom;

            c = x;
            x = x * cos(THETA * env->rot_z) + y * sin(THETA * env->rot_z);
            y =  - c * sin(THETA * env->rot_z) + y * cos(THETA * env->rot_z);

            a = y;
            y =  y * cos(THETA * env->rot_x) + z * sin(THETA * env->rot_x);
            z =  - a * sin(THETA * env->rot_x) + z * cos(THETA * env->rot_x);

            b = z;
            z =  z * cos(THETA * env->rot_y) - x * sin(THETA * env->rot_y);
            x = - b * sin(THETA * env->rot_y) + x * cos(THETA * env->rot_y);
            
            add = init_node((int)x, (int)y, (int)z , map[j][i].color);
            new[j][i] = *add;
            i++;
        }
        j++;
    }
    return (new);
}

/*t_node  **proj_con(t_node **map, t_env *env, int len_x, int len_y)
{
    
    t_node **new;
    t_node *add;
    int x;
    int y;
    int i;
    int j;
    int x_mil;
    int y_mil;

    x_min = (min_x + max_x) / 2;
    y_mil = (min_y + max_y) / 2;
    if (len_x == 0 || !(new = ft_memalloc(sizeof(t_node*) * len_x)))
        return (NULL);
   
    }
    return (new);
}*/
