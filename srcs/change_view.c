#include "fdf.h"


/*
number 0 : translation to left
number 1 : translation to down
number 2 : translation to right
number 3 : translation to up
*/

void    trace(t_env *env, t_node **pix)
{
    mlx_destroy_image(env->mlx, env->img);
    env->img = NULL;
    env->img = init_img(env, FENE_X, FENE_Y);
	draw_map(env, pix);
	draw_link(env, pix);
    print_image_graph(env);
}

t_node     **choose(t_env *env)
{
    t_node **pix;

    pix = NULL;
     if (env->type_proj == 0)
        pix = proj_iso(env, env->map);
    else if (env->type_proj == 1)
         pix = proj_para(env, env->map);
    return (pix);
}

void    to_other(t_env *env, int i)
{
    t_node **pix;

    if (i != env->type_proj)
    {
        env->type_proj = i;
        env->zoom = 1.0;
        env->trans_x = 0;
        env->trans_y = 0;
        env->moove_z = 1.0;
        pix = choose(env);
        get_extreme(env, pix);
        trace(env, pix);
        free(pix);
    }
}

void   moove_z(t_env *env, int i)
{
    t_node **pix;
    pix = NULL;
    if (i == 1)
        env->moove_z = env->moove_z *  COEFF_Z;
    else if (i == 0)
        env->moove_z = env->moove_z *  COEFF_ZD;
    pix = choose(env);
    get_extreme(env, pix);
    trace(env, pix);
    free(pix);
}

int    translation(t_env *env, int number)
{
    t_node **pix;

    if (number > 4 || number < 0)
        return (-1);
    if (number == 0)
       env->trans_x--;
    else if (number == 2)
       env->trans_x++;
    else if (number == 3)
       env->trans_y--;
    else if (number == 1)
      env->trans_y++;
      
    pix = choose(env);
    get_extreme(env, pix);
    trace(env, pix);
    free(pix);
    return (1);
}

void     reinitialise(t_env *env)
{       
        t_node **pix;
        pix = NULL;
        env->min_x = SIZE_X;
	    env->min_y = SIZE_Y;
	    env->max_x = 0;
	    env->max_y = 0;
        env->trans_x = 0;
        env->trans_y = 0;
        env->zoom = 1.0;
        env->moove_z = 1.0;
        pix = choose(env);
        get_extreme(env, pix);
        scale(env, pix);
        trace(env, pix);
        free(pix);
}

void    zoom(t_env *env)
{
    /*int x;
	int y;
    int a;
    int b;

	y = 0;
	t_node **map;*/
    t_node **pix;
    pix = NULL;
    env->zoom = env->zoom * COEFF_ZOOM;
    pix = choose(env);
    get_extreme(env, pix);
    /*map = env->map;*/	
	/*while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
            a = COEFF_ZOOM * env->map[y][x].x;
            b = COEFF_ZOOM * env->map[y][x].y;
            env->map[y][x].x = (int)a;
            env->map[y][x].y = (int)b;
            env->map[y][x].x = (int) (env->map[y][x].x + COEFF_ZOOM * (env->map[y][x].x - (a - ORIGIN_GRAPH_X)));
            env->map[y][x].y = (int) (env->map[y][x].y + COEFF_ZOOM * (env->map[y][x].y - (b - ORIGIN_GRAPH_Y))); 
			x++; 
		}
		y++;
	}*/
        trace(env, pix);
        free(pix);
}

void    dezoom(t_env *env)
{
  /* int x;
	int y;
    int a;
    int b;
	y = 0;*/
	t_node **pix;
    pix = NULL;
    /*map = env->map;*/
    env->zoom = env->zoom / COEFF_ZOOM;
    pix = choose(env);
    get_extreme(env, pix);
/*	while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
            a = COEFF_DEZOOM * env->map[y][x].x;
            b = COEFF_DEZOOM * env->map[y][x].y;
            env->map[y][x].x = (int)a;
            env->map[y][x].y = (int)b;
            env->map[y][x].x = (int) (env->map[y][x].x - COEFF_ZOOM * (env->map[y][x].x - (a - ORIGIN_GRAPH_X)));
            env->map[y][x].y = (int) (env->map[y][x].y - COEFF_ZOOM * (env->map[y][x].y - (b - ORIGIN_GRAPH_Y)));
			x++; 
		}
		y++;
	}
    */
        trace(env, pix);
        free(pix);
}
