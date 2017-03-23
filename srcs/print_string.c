#include "fdf.h"


int prevent_large_zoom(t_env *env, int x, int y)
{
    print_all(env);
    print_title(env);
    print_coord(x, y, env);
    mlx_string_put(env->mlx, env->win, 50, 400, 0xFF0000, "Le zoom est a ");
    mlx_string_put(env->mlx, env->win, 50, 440, 0xFF0000, "consommer avec moderation !");
    return (0);
}

int prevent_large_dezoom(t_env *env, int x, int y)
{
    print_all(env);
    print_title(env);
     print_coord(x, y, env);
    mlx_string_put(env->mlx, env->win, 50, 480, 0xFF0000, "Le dezoom est a ");
    mlx_string_put(env->mlx, env->win, 50, 520, 0xFF0000, "consommer avec moderation !");
    return (0);
}

int    print_title(t_env *env)
{
    mlx_string_put(env->mlx, env->win, 900, 10, 0x3A5FCD, "File name : ");
    mlx_string_put(env->mlx, env->win, 1050, 10, 0x3A5FCD, env->filename);
    mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");
    mlx_string_put(env->mlx, env->win, 50, 360, 0x3A5FCD, "Current y : ");
   /*mlx_string_put(env->mlx, env->win, 50, 400, 0xFF0000, "Le zoom est a ");
    mlx_string_put(env->mlx, env->win, 50, 440, 0xFF0000, "consommer avec moderation !");*/
    return (0);
}

void    print_all(t_env *env)
{
    print_image_back(env);
    print_image_supp(env);
    print_image_graph(env);
}

void    print_image_back(t_env *env)
{
        mlx_put_image_to_window(env->mlx, env->win, (env->back_img)->img, 0, 0);
}

void     print_image_supp(t_env *env)
{
	    mlx_put_image_to_window(env->mlx, env->win, (env->sup_img)->img, 360, 80);
}
void    print_image_graph(t_env *env)
{
	    mlx_put_image_to_window(env->mlx, env->win, (env->img)->img, 400, 100);
}


void    print_coord(int x, int y, t_env *env)
{
    char *c;
    char *d;

    print_all(env);
    print_title(env);
    env->x = x - 400;
    env->y = y - 100;
    c = ft_itoa(env->x);
    d = ft_itoa(env->y);
    mlx_string_put(env->mlx, env->win, 190, 300, 0x3A5FCD, c);
    mlx_string_put(env->mlx, env->win, 190, 360, 0x3A5FCD, d);
 
}
