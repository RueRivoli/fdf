#include "fdf.h"

int    print_title(t_env *env)
{
    mlx_string_put(env->mlx, env->win, 900, 10, 0x3A5FCD, "File name : ");
    mlx_string_put(env->mlx, env->win, 1050, 10, 0x3A5FCD, env->filename);
    mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");
    mlx_string_put(env->mlx, env->win, 50, 360, 0x3A5FCD, "Current y : ");
    return (0);
}

void     print_image(t_env *env)
{
    mlx_put_image_to_window(env->mlx, env->win, (env->back_img)->img, 0, 0);
	mlx_put_image_to_window(env->mlx, env->win, (env->sup_img)->img, 360, 80);
	mlx_put_image_to_window(env->mlx, env->win, (env->img)->img, 400, 100);
}
void    print_coord(int x, int y, t_env *env)
{
    char *c;
    char *d;

    print_image(env);
    print_title(env);
    env->x = x - 400;
    env->y = y - 100;
    c = ft_itoa(env->x);
    d = ft_itoa(env->y);
    mlx_string_put(env->mlx, env->win, 190, 300, 0x3A5FCD, c);
    mlx_string_put(env->mlx, env->win, 190, 360, 0x3A5FCD, d);
    
}
