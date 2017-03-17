#include "fdf.h"

void    draw_map(t_env *env)
{
    int y;
    int x;

    y = 0;
    while (env->map[y])
    {
        x = 0;
        while (x < env->len)
        {
            //ft_putnbr(env->map[i][j].z);
            mlx_put_pixel_to_image(env,&env->map[y][x]);
            x++;
        }
        y++;
    }
}
