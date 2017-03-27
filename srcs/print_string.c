#include "fdf.h"

int    print_title(t_env *env)
{
    /*
    * Partie gauche 
    */
    mlx_string_put(env->mlx, env->win, 850, 30, 0x3A5FCD, "File name : ");
    mlx_string_put(env->mlx, env->win, 1000, 30, 0x3A5FCD, env->filename);
    mlx_string_put(env->mlx, env->win, 50, 300, 0x3A5FCD, "Current x : ");
    mlx_string_put(env->mlx, env->win, 50, 360, 0x3A5FCD, "Current y : ");
    mlx_string_put(env->mlx, env->win, 40, 600, 0x0F9F8C, " \" Success consists of going");
     mlx_string_put(env->mlx, env->win, 40, 650, 0x0F9F8C, "from failure to failure \"");
    mlx_string_put(env->mlx, env->win, 40, 700, 0x0F9F8C, "without loss of enthusiasm ");
    mlx_string_put(env->mlx, env->win, 30, 1030, 0x3A5FCD, "http://github.com/RueRivoli");

     /*
    * Partie droite 
    */
    mlx_string_put(env->mlx, env->win, 1680, 150, 0xD3D3D3, " M E N U ");
    mlx_string_put(env->mlx, env->win, 1650, 200, 0xD3D3DA, "Sortir : Echap");
    mlx_string_put(env->mlx, env->win, 1650, 250, 0xD3D3DA, "Projection Para : P");
    mlx_string_put(env->mlx, env->win, 1650, 300, 0xD3D3DA, "Projection Iso : I");
    mlx_string_put(env->mlx, env->win, 1650, 350, 0xD3D3DA, "Start : O");
    mlx_string_put(env->mlx, env->win, 1650, 400, 0xD3D3DA, "Plus d'altitude : +");
    mlx_string_put(env->mlx, env->win, 1650, 450, 0xD3D3DA, "Moins d'altitude : -");
    mlx_string_put(env->mlx, env->win, 1650, 500, 0xD3D3DA, "Zoom : scroll avant");
    mlx_string_put(env->mlx, env->win, 1650, 550, 0xD3D3DA, "Dezoom : scroll arriere");
    mlx_string_put(env->mlx, env->win, 1650, 600, 0xD3D3DA, "Deplacement : fleches");
    return (0);
}

void    print_all(t_env *env)
{
     
    print_image_back(env);
   	
    print_image_sign(env);
    print_image_supp(env);
    print_image_graph(env);
}

void    print_image_back(t_env *env)
{
        mlx_put_image_to_window(env->mlx, env->win, (env->back_img)->img, 0, 0);
}

void     print_image_supp(t_env *env)
{
	    mlx_put_image_to_window(env->mlx, env->win, (env->sup_img)->img, 320, 80);
}
void    print_image_graph(t_env *env)
{
	    mlx_put_image_to_window(env->mlx, env->win, (env->img)->img, 360, 100);
}

void    print_image_sign(t_env *env)
{
    mlx_put_image_to_window(env->mlx, env->win, (env->church_img)->img, 30, 750);
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
