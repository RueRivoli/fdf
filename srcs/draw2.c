#include "fdf.h"



char    *hex_altitude(int rn, int gn, int bn)
{
    char *hex;
    char *str;


    if (!(str = ft_strnew(8)))
        return (NULL);
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


char     *altitude_color(t_env *env, t_node *node)
{
    float delta;
    float deltab;
    int r;
    int g;
    int b;
    int rn;
    int gn;
    int bn;

    t_ext *ext;
    ext = env->extr;
    delta = (float) node->z - ext->min_z;
    deltab = (float) ext->max_z - ext->min_z;
    delta = (float) delta / deltab;
   
    
    r = ft_hextoint(ft_strsub("0xFFFFFF", 2, 2)) - ft_hextoint(ft_strsub("0xFF0000", 2, 2));
    g = ft_hextoint(ft_strsub("0xFF0000", 4, 2)) - ft_hextoint(ft_strsub("0xFFFFFF", 4, 2));
    b = ft_hextoint(ft_strsub("0xFF0000", 6, 2)) - ft_hextoint(ft_strsub("0xFFFFFF", 6, 2));

    rn = (int)(ft_hextoint(ft_strsub("0xFF0000", 2, 2)) + delta * r);
    gn = (int)(ft_hextoint(ft_strsub("0xFFFFFF", 4, 2)) + delta * g);
    bn = (int) (ft_hextoint(ft_strsub("0xFFFFFF", 6, 2)) + delta * b);
    return (hex_altitude(rn, gn, bn));
}


t_node *new_coord(t_env *env, t_node *node)
{
        t_mat mat;
        int x_cen;
        int y_cen;
        int z_cen;
        t_ext *ext;

        ext = env->extr;
       
            x_cen = FENE_X / 2;
            y_cen = FENE_Y / 2;
   
            z_cen = 0;
            which_proj(env, &mat, node);
            

            mat.c = mat.x;
            mat.x = x_cen + (mat.x - x_cen) * cos(THETA * env->rot_z) - (mat.y - y_cen) * sin(THETA * env->rot_z);
            mat.y = y_cen + (mat.c - x_cen) * sin(THETA * env->rot_z) + (mat.y - y_cen) * cos(THETA * env->rot_z);

            

            mat.a = mat.y;
            mat.y =  y_cen + (mat.y - y_cen) * cos(THETA * env->rot_x) - (mat.z - z_cen) * sin(THETA * env->rot_x);
            mat.z =  z_cen - (mat.a - y_cen) * sin(THETA * env->rot_x) + (mat.z - z_cen) * cos(THETA * env->rot_x);

            mat.b = mat.z;
            mat.z =  z_cen + (mat.z - z_cen) * cos(THETA * env->rot_y) - (mat.x - x_cen) * sin(THETA * env->rot_y);
            mat.x =  x_cen + (mat.b - z_cen) * sin(THETA * env->rot_y) + (mat.x - x_cen) * cos(THETA * env->rot_y);


            mat.c = mat.x;
            mat.x = env->zoom * mat.x + 15 * env->trans_x;
            mat.y = env->zoom * mat.y + 15 * env->trans_y;
            mat.z = env->zoom * mat.z;
        
        return (init_node((int)mat.x, (int)mat.y, (int)mat.z , node->color_num));
}

void				get_extreme_after_transform(t_env *env, t_node **map)
{
	int i;
	int j;
    t_node *new;
    t_node *start;
    t_ext  *ext;

    ext = env->extr;
	j = 0;
    start = new_coord(env, &map[0][0]);
    ext->min_z = start->z;
	ext->max_z = start->z;
	while (j < env->len_y)
	{
		i = 0;
		while (i < env->len_x)
		{
            new = new_coord(env, &map[j][i]);
			if (new->z > ext->max_z)
				ext->max_z = new->z;
			if (new->z < ext->min_z)
				ext->min_z = new->z;
			i++;
		}
		j++;
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
