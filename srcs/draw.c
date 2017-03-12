#include "fdf.h"

void    draw_map(t_env *env)
{
    int i;
    int j;

    i = 0;
    while (env->map[i])
    {
        j = 0;
        while (j < env->len)
        {
            mlx_put_pixel_to_image(env,&env->map[i][j]);
            j++;
        }
        i++;
    }
}