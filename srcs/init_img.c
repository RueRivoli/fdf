#include "fdf.h"

void    mlx_put_pixel_to_image(t_env *env, t_node *node)
{
    int octet;

    octet = env->img->bpp / 8;
    if (node->x > 0 && node->y > 0 && node->x < FENE_X && node->y < FENE_Y)
    {
        ft_memcpy(&env->img->data[octet * node->x + env->img->sizeline *
    node->y], &(node->color), octet);
    }
    //ft_memcpy(&env->img->data[octet * (node->x + env->img->sizeline /
                                           //octet * node->y)], &(node->color), octet);
    
}

