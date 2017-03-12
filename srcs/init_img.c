#include "fdf.h"

void    mlx_put_pixel_to_image(t_env *env, t_node *node)
{
    int octet;

    octet = env->img->bpp / 8;
    ft_memcpy(&env->img->data[octet * node->x + env->img->sizeline *
    node->y], &(node->color), octet);
}

