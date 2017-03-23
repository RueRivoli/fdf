#include "fdf.h"


/*
number 0 : translation to left
number 1 : translation to down
number 2 : translation to right
number 3 : translation to up
*/

void    trace(t_env *env)
{
    mlx_destroy_image(env->mlx, env->img);
    env->img = NULL;
    env->img = init_img(env, FENE_X, FENE_Y);
	draw_map(env);
	draw_link(env);
    print_image_graph(env);
}

int    translation(t_env *env, int number)
{
    t_node **map;
    int i;
    int j;
    map = env->map;
    if (number > 4 || number < 0)
        return (-1);
    j = 0;
    while (j < env->len_y)
    {
        i = 0;
        while (i < env->len_x)
        {   
            if (number == 0)
                map[j][i].x = map[j][i].x - COEFF_TRANS;
            else if (number == 2)
                map[j][i].x = map[j][i].x + COEFF_TRANS;
            else if (number == 3)
                map[j][i].y = map[j][i].y - COEFF_TRANS;
             else if (number == 1)
                map[j][i].y = map[j][i].y + COEFF_TRANS;
            i++;
        }
        j++;
    }
    
    ft_putstr("\n\n\n");
    get_extreme(env);
    trace(env);
    display_map(map, env);
    return (1);
}

void     reinitialise(t_env *env)
{       
        env->min_x = SIZE_X;
	    env->min_y = SIZE_Y;
	    env->max_x = 0;
	    env->max_y = 0;
        get_extreme(env);
	    scale(env);
        trace(env);
}

void    zoom(t_env *env)
{
    int x;
	int y;
    int a;
    int b;

	y = 0;
	t_node **map;
    
    get_extreme(env);
    map = env->map;	
	while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
            a = COEFF_ZOOM * env->map[y][x].x;
            b = COEFF_ZOOM * env->map[y][x].y;
            env->map[y][x].x = (int)a;
            env->map[y][x].y = (int)b;
            /*env->map[y][x].x = (int) (env->map[y][x].x + COEFF_ZOOM * (env->map[y][x].x - (a - ORIGIN_GRAPH_X)));
            env->map[y][x].y = (int) (env->map[y][x].y + COEFF_ZOOM * (env->map[y][x].y - (b - ORIGIN_GRAPH_Y))); */
			x++; 
		}
		y++;
	}
        trace(env);
}

void    dezoom(t_env *env)
{
    int x;
	int y;
    int a;
    int b;
	y = 0;
	t_node **map;
    map = env->map;
	get_extreme(env);
	while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
            a = COEFF_DEZOOM * env->map[y][x].x;
            b = COEFF_DEZOOM * env->map[y][x].y;
            env->map[y][x].x = (int)a;
            env->map[y][x].y = (int)b;
            /*env->map[y][x].x = (int) (env->map[y][x].x - COEFF_ZOOM * (env->map[y][x].x - (a - ORIGIN_GRAPH_X)));
            env->map[y][x].y = (int) (env->map[y][x].y - COEFF_ZOOM * (env->map[y][x].y - (b - ORIGIN_GRAPH_Y)));*/
			x++; 
		}
		y++;
	}
        trace(env);
}
