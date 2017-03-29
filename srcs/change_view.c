#include "fdf.h"


/*
number 0 : translation to left
number 1 : translation to down
number 2 : translation to right
number 3 : translation to up

rotation 0 : rotation on x positive
rotation 1 : rotation on x negative
rotation 2 : rotation on y positive
rotation 3 : rotation on y negative
rotation 4 : rotation on z positive
rotation 5 : rotation on z negative
*/


void    refresh(t_env *env)
{
    mlx_destroy_image(env->mlx, env->img);
    env->img = NULL;
    env->img = init_img(env, FENE_X, FENE_Y);
    get_extreme(env, env->map);
    draw_map(env, env->map);
    print_image_graph(env);
}

void    to_other(t_env *env, int i)
{
    if (i != env->type_proj)
    {
        env->type_proj = i;
        env->zoom = 1.0;
        env->trans_x = 0;
        env->trans_y = 0;
        env->moove_z = 1.0;
        env->rot_z = 0;
        refresh(env);
    }
}

void   moove_z(t_env *env, int i)
{
    if (i == 1)
        env->moove_z = env->moove_z *  COEFF_Z;
    else if (i == 0)
        env->moove_z = env->moove_z *  COEFF_ZD;
    refresh(env);
}

void    translation(t_env *env, int number)
{
    if (number == 0)
       env->trans_x--;
    else if (number == 2)
       env->trans_x++;
    else if (number == 3)
       env->trans_y--;
    else if (number == 1)
      env->trans_y++;
    else ;
    refresh(env);
}

void    rotation(t_env *env, int i)
{
    if (i == 0)
        env->rot_x++;
    else if (i == 1)
        env->rot_x--;
    else if (i == 2)
        env->rot_y++;
    else if (i == 3)
        env->rot_y--;
    else if (i == 4)
        env->rot_z++;
    else if (i == 5)
        env->rot_z--;
    refresh(env);
}

void     reinitialise(t_env *env)
{       
        env->min_x = SIZE_X;
	    env->min_y = SIZE_Y;
	    env->max_x = 0;
	    env->max_y = 0;
        env->trans_x = 0;
        env->trans_y = 0;
        env->zoom = 1.0;
        env->moove_z = 1.0;
        refresh(env);
}

void    zoom(t_env *env)
{
    env->zoom = env->zoom * COEFF_ZOOM;
    refresh(env);
}

void    dezoom(t_env *env)
{
    env->zoom = env->zoom / COEFF_ZOOM;
    refresh(env);
}
