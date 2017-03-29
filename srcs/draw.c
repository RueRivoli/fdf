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

void    which_proj(t_env *env, t_mat *mat, t_node *node)
{
        if (env->type_proj == 0)
        {
            mat->z = node->z * env->moove_z;
            mat->x = CTE1 * node->x - CTE2 * node->y;
            mat->y = -2 * mat->z + (CTE1/2) * node->x + (CTE2/2) * node->y; //proj
            if (env->type_proj == 0){
             mat->x += 540;
             mat->y += 140;   
            }
        }
        else if (env->type_proj == 1)
        {
             mat->z = node->z * env->moove_z;
            mat->x = node->x - CTE * mat->z;
            mat->y = node->y + (CTE/2) * mat->z;
        }
}

char     *altitude_color(t_env *env, t_node *node)
{
    int delta;
    int r;
    int g;
    int b;
    int rn;
    int gn;
    int bn;
    char *str;
    char *hex;

    if (!(str = ft_strnew(8)))
        return (NULL);
    delta = (node->z - env->min_z) / (env->max_z - env->min_z);
    r = ft_hextoint(ft_strsub("0xFFFFFF", 2, 2)) - ft_hextoint(ft_strsub("0xFF0000", 2, 2));
    g = ft_hextoint(ft_strsub("0xFFFFFF", 4, 2)) - ft_hextoint(ft_strsub("0xFF0000", 4, 2));
    b = ft_hextoint(ft_strsub("0xFFFFFF", 6, 2)) - ft_hextoint(ft_strsub("0xFF0000", 6, 2));

    rn = ft_hextoint(ft_strsub("0xFF0000", 2, 2)) + (delta) * r;
    gn = ft_hextoint(ft_strsub("0xFF0000", 4, 2)) + (delta) * g;
    bn = ft_hextoint(ft_strsub("0xFF0000", 6, 2)) + (delta) * b;
    hex = ft_itohex(rn);
    str[0] = '0';
    str[1] = 'x';
    str[2] = hex[0];
    str[3] = hex[1];
    hex = ft_itohex(gn);
    str[4] = hex[0];
    str[5] = hex[1];
    hex = ft_itohex(bn);
    str[6] = hex[0];
    str[7] = hex[1];
    return (str);
}

char     *progressive_color(t_node *node1, t_node *node2, int i)
{
    int delta;
    int r;
    int g;
    int b;
    int rn;
    int gn;
    int bn;
    char *str;
    char *hex;

    if (!(str = ft_strnew(8)))
        return (NULL);
    delta = sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2));
    r = ft_hextoint(ft_strsub(node2->color, 2, 2)) - ft_hextoint(ft_strsub(node1->color, 2, 2));
    g = ft_hextoint(ft_strsub(node2->color, 4, 2)) - ft_hextoint(ft_strsub(node1->color, 4, 2));
    b = ft_hextoint(ft_strsub(node2->color, 6, 2)) - ft_hextoint(ft_strsub(node1->color, 6, 2));

    rn = ft_hextoint(ft_strsub(node1->color, 2, 2)) + (i / delta) * r;
    gn = ft_hextoint(ft_strsub(node1->color, 4, 2)) + (i / delta) * g;
    bn = ft_hextoint(ft_strsub(node1->color, 6, 2)) + (i / delta) * b;
    hex = ft_itohex(rn);
    str[0] = '0';
    str[1] = 'x';
    str[2] = hex[0];
    str[3] = hex[1];
    hex = ft_itohex(gn);
    str[4] = hex[0];
    str[5] = hex[1];
    hex = ft_itohex(bn);
    str[6] = hex[0];
    str[7] = hex[1];
    return (str);
}

t_node *new_coord(t_env *env, t_node *node)
{
        t_mat mat;
        
            which_proj(env, &mat, node);
            mat.c = mat.x;
            mat.x = env->zoom * mat.x + 15 * env->trans_x;
            mat.y = env->zoom * mat.y + 15 * env->trans_y;
            mat.z = mat.z * env->zoom;//trans et zoom

            mat.x = mat.x * cos(THETA * env->rot_z) + mat.y * sin(THETA * env->rot_z);
            mat.y =  - mat.c * sin(THETA * env->rot_z) + mat.y * cos(THETA * env->rot_z);//rot z

            mat.a = mat.y;
            mat.y =  mat.y * cos(THETA * env->rot_x) + mat.z * sin(THETA * env->rot_x);
            mat.z =  - mat.a * sin(THETA * env->rot_x) + mat.z * cos(THETA * env->rot_x);//rot x
            mat.b = mat.z;

            mat.z =  mat.z * cos(THETA * env->rot_y) - mat.x * sin(THETA * env->rot_y);
            mat.x = - mat.b * sin(THETA * env->rot_y) + mat.x * cos(THETA * env->rot_y);//rot y
        
        return (init_node((int)mat.x, (int)mat.y, (int)mat.z , node->color));
}

void    draw_map(t_env *env, t_node **map)
{
    int y;
    int x;
    t_node *new;
    
    y = 0;
    get_extreme(env, env->map);
    while (y < env->len_y)
    {
        x = 0;
        while (x < env->len_x)
        {   
            new = NULL;
            new = new_coord(env, &map[y][x]);
            
            if (x != env->len_x - 1)           
                draw_segment(env, new, new_coord(env, &map[y][x + 1]));
            if (y != env->len_y - 1)            
                draw_segment(env, new, new_coord(env, &map[y + 1][x]));
            mlx_put_pixel_to_image(env, new);
            free(new);
            x++;
        }
        y++;
    }
}

void    draw_vertical(t_env *env, t_node *node1, t_node *node2)
{
    int y;
    int x;
    int z;
    // t_node *new;
    t_node new;

    x = node1->x;
    
    if (node1->y < node2->y)
    { 
        y = node1->y + 1;
        while (y < node2->y)
        {   
            z = node1->z + (y - node1->y) * (node2->z - node1->z) / (node2->y - node1->y);
            new.x = x;
            new.y = y;
            new.z = (int)z;
            new.color = progressive_color(node1, node2, y);
            mlx_put_pixel_to_image(env, &new);
            y++;
        }
    }
    else
         draw_vertical(env, node2, node1);
}

void    draw_horizontal(t_env *env, t_node *node1, t_node *node2)
{
    int x;
    int y;
    int z;
    t_node new;
    
    y = node1->y;
    if (node1->x < node2->x)
    { 
        x = node1->x + 1;
        while (x < node2->x)
        {
            z = node1->z + (x - node1->x) * (node2->z - node1->z) / (node2->x - node1->x);
            new.x = x;
            new.y = y;
            new.z = (int)z;
            new.color = progressive_color(node1, node2, x);
            mlx_put_pixel_to_image(env, &new);
            x++;
        }
    }
    else
        draw_horizontal(env, node2, node1);
}

void    draw_soft_rise(t_env *env, t_node *node1, t_node *node2)
{
        int x;
        int y_new;
        int z;
        t_node new;
        if (node2->x < node1->x)
            draw_soft_rise(env, node2, node1);
        else{
              x = node1->x + 1;
              while (x < node2->x)
             {
                  y_new = node1->y + ((node2->y - node1->y) * (x - node1->x) / (node2->x - node1->x));
                  z = node1->z + sqrt(pow(x - node1->x, 2) + pow(y_new - node1->y, 2)) * (node2->z - node1->z) / sqrt(pow(node2->x - node1->x, 2) +  pow(node2->y - node1->y, 2));
                  new.x = x;
                new.y = y_new;
                new.z = (int)z;
                new.color = progressive_color(node1, node2, x);
                 mlx_put_pixel_to_image(env, &new);
                 x++;
             }
        }
}

void    draw_high_rise(t_env *env, t_node *node1, t_node *node2)
{
        int x_new;
        int y;
        int z;

        t_node new;
        if (node2->y < node1->y)
            draw_soft_rise(env, node2, node1);
        else{
              y = node1->y + 1;
              while (y < node2->y)
             {
                x_new = node1->x + ((node2->x - node1->x) * (y - node1->y) / (node2->y - node1->y));
                z = node1->z + sqrt(pow(x_new - node1->x, 2) + pow(y - node1->y, 2)) * (node2->z - node1->z) / sqrt(pow(node2->x - node1->x, 2) +  pow(node2->y - node1->y, 2));
                  new.x = x_new;
                    new.y = y;
                    new.z = (int)z;
                 new.color = progressive_color(node1, node2, y);
                 mlx_put_pixel_to_image(env, &new);
                 y++;
             }
        }
}

void    draw_segment(t_env *env, t_node *node1, t_node *node2)
{
    if (node1->x == node2->x && node1->y != node2->y)
        draw_vertical(env, node1, node2);
    else if (node1->y == node2->y && node1->x != node2->x)
        draw_horizontal(env, node1, node2);
    else if (node1->x != node2->x && abs((node2->y - node1->y)/(node2->x - node1->x)) < 1) 
        draw_soft_rise(env, node1, node2);
    else if (node1->y != node2->y)
        draw_high_rise(env, node1, node2);
}
     

void    draw_link(t_env *env, t_node **map)
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
                draw_segment(env, &map[y][x], &map[y][x + 1]);
            if (y != env->len_y - 1)            
                draw_segment(env, &map[y][x], &map[y + 1][x]);
            x++;
        }
        y++;
    }
}
