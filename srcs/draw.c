#include "fdf.h"
#include "define.h"

int    right_color(t_node *node1, t_node *node2)
{
    if (node1->z != node2->z)
        return (COLOR_RISE);
    else if (node1->z > 0)
        return (COLOR_HIGH_ALT);
    else
        return (COLOR_Z_0);
}

void    draw_map(t_env *env)
{
    int y;
    int x;

    y = 0;
    while (y < env->len_y)
    {
        x = 0;
        while (x < env->len_x)
        {        
            mlx_put_pixel_to_image(env,&env->map[y][x]);
            x++;
        }
        //ft_putchar('\n');
        y++;
    }
}

void    draw_vertical(t_env *env, t_node *node1, t_node *node2, int color)
{
    int y;
    int x;
    t_node *new;

    x = node1->x;
    if (node1->y < node2->y)
    { 
        y = node1->y + 1;
        while (y < node2->y)
        {
            new = init_node(x, y, 0, color);
            mlx_put_pixel_to_image(env, new);
            y++;
        }
    }
    else if (node2->y < node1->y)
    {
         y = node2->y + 1;
        while (y < node1->y)
        {
            new = init_node(x, y, 0, color);
            mlx_put_pixel_to_image(env, new);
            y++;
        }
    }
}

void    draw_horizontal(t_env *env, t_node *node1, t_node *node2, int color)
{
    int y;
    int x;
    t_node *new;
    
    y = node1->y;
    if (node1->x < node2->x)
    { 
        x = node1->x + 1;
        while (x < node2->x)
        {
            new = init_node(x, y, 0, color);
            mlx_put_pixel_to_image(env, new);
            x++;
        }
    }
    else if (node2->x < node1->x)
    {
         x = node2->x + 1;
        while (x < node1->x)
        {
            new = init_node(x, y, 0, color);
            mlx_put_pixel_to_image(env, new);
            x++;
        }
    }
}

void    draw_soft_rise(t_env *env, t_node *node1, t_node *node2, int color)
{
        int x;
        int y_new;
        t_node *new;
        if (node2->x < node1->x)
            draw_soft_rise(env, node2, node1, color);
        else{
              x = node1->x + 1;
              while (x < node2->x)
             {
                  y_new = node1->y + ((node2->y - node1->y) * (x - node1->x) / (node2->x - node1->x));
                 new = init_node(x, y_new, 0, color);
                 mlx_put_pixel_to_image(env, new);
                 x++;
             }
        }
}

void    draw_high_rise(t_env *env, t_node *node1, t_node *node2, int color)
{
        int y;
        int x_new;
        t_node *new;
        if (node2->y < node1->y)
            draw_soft_rise(env, node2, node1, color);
        else{
              y = node1->y + 1;
              while (y < node2->y)
             {
                x_new = node1->x + ((node2->x - node1->x) * (y - node1->y) / (node2->y - node1->y));
                 new = init_node(x_new, y, 0, color);
                 mlx_put_pixel_to_image(env, new);
                 y++;
             }
        }
}

void    draw_segment(t_env *env, t_node *node1, t_node *node2)
{
    int color;

    color = right_color(node1, node2);
    if (node1->x == node2->x)
        draw_vertical(env, node1, node2, color);
    else if (node1->y == node2->y)
        draw_horizontal(env, node1, node2, color);
    else if (abs((node2->y - node1->y)/(node2->x - node1->x)) < 1) 
        draw_soft_rise(env, node1, node2, color);
    else
        draw_high_rise(env, node1, node2, color);
}
     

void    draw_link(t_env *env)
{
    int x;
    int y;

    y = 0;
    while (y < env->len_y)
    {
        x = 0;
        while (x < env->len_x)
        { 
            if (x != env->len_x - 1)                
                draw_segment(env, &env->map[y][x], &env->map[y][x + 1]);
            if (y != env->len_y - 1)            
                draw_segment(env, &env->map[y][x], &env->map[y + 1][x]);
            x++;
        }
        y++;
    }
}