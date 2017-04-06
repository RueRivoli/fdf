#include "fdf.h"


void    refresh(t_env *env)
{
    mlx_destroy_image(env->mlx, env->img);
    env->img = NULL;
    env->img = init_img(env, FENE_X, FENE_Y);
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

void     reinitialise(t_env *env)
{       
        env->rot_x = 0;
	    env->rot_y = 0;
        env->rot_z = 0;
        env->trans_x = 0;
        env->trans_y = 0;
        env->zoom = 1.0;
        env->moove_z = 1.0;
        refresh(env);
}
