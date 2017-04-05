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
    float delta;
    float deltab;
    int r;
    int g;
    int b;
    int rn;
    int gn;
    int bn;
    char *str;
    char *hex;
    
    t_ext *ext;
    ext = env->extr;
    delta = (float) node->z - ext->min_z;
    deltab = (float) ext->max_z - ext->min_z;
    delta = (float) delta / deltab;
   
    if (!(str = ft_strnew(8)))
        return (NULL);
    r = ft_hextoint(ft_strsub("0xFFFFFF", 2, 2)) - ft_hextoint(ft_strsub("0xFF0000", 2, 2));
    g = ft_hextoint(ft_strsub("0xFF0000", 4, 2)) - ft_hextoint(ft_strsub("0xFFFFFF", 4, 2));
    b = ft_hextoint(ft_strsub("0xFF0000", 6, 2)) - ft_hextoint(ft_strsub("0xFFFFFF", 6, 2));

    rn = (int)(ft_hextoint(ft_strsub("0xFF0000", 2, 2)) + delta * r);
    gn = (int)(ft_hextoint(ft_strsub("0xFFFFFF", 4, 2)) + delta * g);
    bn = (int) (ft_hextoint(ft_strsub("0xFFFFFF", 6, 2)) + delta * b);
    /*if (gn != 0)
        printf("%d\n", gn);*/
    hex = ft_itohex(rn);
    str[0] = '0';
    str[1] = 'x';
    str[2] = hex[0];
    str[3] = hex[1];
    
    /*ft_putstr("A\n");    
    ft_putnbr(rn);
    ft_putchar('\n');*/

    hex = ft_itohex(gn);
    str[4] = hex[0];
    str[5] = hex[1];
   /*ft_putstr("B\n");  
    ft_putstr(hex);
    ft_putchar('\n');*/

    hex = ft_itohex(bn);
    str[6] = hex[0];
    str[7] = hex[1];
    /*ft_putstr("C\n");  
    ft_putstr(hex);
    ft_putchar('\n');*/
    
        //ft_putstr(hex1);
        /*if (strcmp(str, "0xFFFFFF") != 0)
        {
			ft_putstr(str);
			ft_putstr("\n");
        }*/
    return (str);
}

float   proportion_altitude(t_env *env, t_node *node)
{
    printf("%d\n", node->z);
    return ((node->z - env->extr->min_z) / (env->extr->max_z - env->extr->min_z));
}

/*char     *progressive_color(t_node *node1, t_node *node2, int i)
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
    ft_putchar('C');
    b = ft_hextoint(ft_strsub(node2->color, 6, 2)) - ft_hextoint(ft_strsub(node1->color, 6, 2));
    
    
    rn = (int)ft_hextoint(ft_strsub(node1->color, 2, 2)) + (i / delta) * r;
    gn = (int)ft_hextoint(ft_strsub(node1->color, 4, 2)) + (i / delta) * g;
    bn = (int)ft_hextoint(ft_strsub(node1->color, 6, 2)) + (i / delta) * b;
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
}*/

t_node *new_coord(t_env *env, t_node *node)
{
        t_mat mat;
        int x_cen;
        int y_cen;
        int z_cen;
        t_ext *ext;

        ext = env->extr;
        /*x_cen = (ext->min_xl + ext->max_xl) / 2;
        y_cen = (ext->min_yl + ext->max_yl) / 2;
        z_cen = (ext->min_zl + ext->max_zl) / 2;*/

            x_cen = FENE_X / 2;
        y_cen = FENE_Y / 2;
        //z_cen = (ext->min_zl + ext->max_zl) / 2;
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

            /*mat.x = mat.x * cos(THETA * env->rot_z) + mat.y * sin(THETA * env->rot_z);
            mat.y =  - mat.c * sin(THETA * env->rot_z) + mat.y * cos(THETA * env->rot_z);//rot z
*/
            /*mat.a = mat.y;
            mat.y =  mat.y * cos(THETA * env->rot_x) + mat.z * sin(THETA * env->rot_x);
            mat.z =  - mat.a * sin(THETA * env->rot_x) + mat.z * cos(THETA * env->rot_x);//rot x
            mat.b = mat.z;

            mat.z =  mat.z * cos(THETA * env->rot_y) - mat.x * sin(THETA * env->rot_y);
            mat.x = - mat.b * sin(THETA * env->rot_y) + mat.x * cos(THETA * env->rot_y);//rot y*/
        
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
    ext->min_x = start->x;
	ext->max_x = start->x;
    ext->min_y = start->y;
	ext->max_y = start->y;
    ext->min_z = start->z;
	ext->max_z = start->z;
	while (j < env->len_y)
	{
		i = 0;
		while (i < env->len_x)
		{
            new = new_coord(env, &map[j][i]);
            if (new->x > ext->max_x)
				ext->max_x = new->x;
			if (new->x < ext->min_x)
				ext->min_x = new->x;
            if (new->y > ext->max_y)
				ext->max_y = new->y;
			if (new->y < ext->min_y)
				ext->min_y = new->y;
			if (new->z > ext->max_z)
				ext->max_z = new->z;
			if (new->z < ext->min_z)
				ext->min_z = new->z;
			i++;
		}
		j++;
	}
}


void				get_extreme_local_after_transform(t_env *env, t_node **map)
{
	int i;
	int j;
    t_node *new;
    t_node *start;
    t_ext  *ext;

    ext = env->extr;

	j = 0;
    start = new_coord(env, &map[0][0]);
    ext->min_xl = start->x;
	ext->max_xl = start->x;
    ext->min_yl = start->y;
	ext->max_yl = start->y;
    ext->min_zl = start->z;
	ext->max_zl = start->z;
	while (j < env->len_y)
	{
		i = 0;
		while (i < env->len_x)
		{
            new = new_coord(env, &map[j][i]);
            if (new->x > ext->max_xl)
				ext->max_xl = new->x;
			if (new->x < ext->min_xl)
				ext->min_xl = new->x;
            if (new->y > ext->max_yl)
				ext->max_yl = new->y;
			if (new->y < ext->min_yl)
				ext->min_yl = new->y;
			if (new->z > ext->max_zl)
				ext->max_zl = new->z;
			if (new->z < ext->min_zl)
				ext->min_zl = new->z;
			i++;
		}
		j++;
	}
}



/*void				get_extreme_after_transform(t_ext *env, t_node **map)
{
	int i;
	int j;
    t_node *new;
    t_node *start;

	j = 0;
    start = new_coord(env, &map[0][0]);
    env->min_z = start->z;
	env->max_z = start->z;
	while (j < env->len_y)
	{
		i = 0;
		while (i < env->len_x)
		{
            new = new_coord(env, &map[j][i]);
			if (new->z > env->max_z)
				env->max_z = new->z;
			if (new->z < env->min_z)
				env->min_z = new->z;
			i++;
		}
		j++;
	}
}*/

/*void				get_extreme_xy_after_transform(t_env *env, t_node **map)
{
	int i;
	int j;
    t_node *new;
    t_node *start;

	j = 0;
    start = new_coord(env, &map[0][0]);
    env->min_x = start->x;
	env->max_x = start->x;
    env->min_y = start->y;
	env->max_y = start->y;
	while (j < env->len_y)
	{
		i = 0;
		while (i < env->len_x)
		{
            new = new_coord(env, &map[j][i]);
            if (new->x > env->max_x)
				env->max_x = new->x;
			if (new->x < env->min_x)
				env->min_x = new->x;
            if (new->y > env->max_y)
				env->max_y = new->y;
			if (new->y < env->min_y)
				env->min_y = new->y;
			i++;
		}
		j++;
	}
}*/

void    draw_map(t_env *env, t_node **map)
{
    int y;
    int x;
    t_node *new;
    
    y = 0;
    new = NULL;
    get_extreme_after_transform(env, map);
    while (y < env->len_y)
    {
        x = 0;
        while (x < env->len_x)
        {   
            new = NULL;
            //map[y][x].rap = proportion_altitude(env, &map[y][x]);
            //printf("%f\n", map[y][x].rap);
           
            new = new_coord(env, &map[y][x]);
            
            if (x != env->len_x - 1)         
            {  
                //map[y][x + 1].rap = proportion_altitude(env, &map[y][x + 1]);
                draw_segment(env, new, new_coord(env, &map[y][x + 1]));
                 
            }
            if (y != env->len_y - 1)
            {            
                //map[y + 1][x].rap = proportion_altitude(env, &map[y + 1][x]);
                draw_segment(env, new, new_coord(env, &map[y + 1][x]));
            }
            mlx_put_pixel_to_image(env, new);
            free(new);
            x++;
        }
        y++;
    }
    //get_extreme_xy_after_transform(env,map);
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
            //new.color = progressive_color(node1, node2, y);
            new.color_num = node1->color_num;
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
            //new.color = progressive_color(node1, node2, x);
            new.color_num = node1->color_num;
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
                //new.color = progressive_color(node1, node2, x);
                
                new.color_num = node1->color_num;
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
                 //new.color = progressive_color(node1, node2, y);
                 new.color_num = node1->color_num;
                 mlx_put_pixel_to_image(env, &new);
                 y++;
             }
        }
}

void    draw_segment(t_env *env, t_node *node1, t_node *node2)
{
    if (node1->x == node2->x && node1->y != node2->y)
    {
        draw_vertical(env, node1, node2);
    }
    else if (node1->y == node2->y && node1->x != node2->x)
    {
        draw_horizontal(env, node1, node2);
    }
    else if (node1->x != node2->x && abs((node2->y - node1->y)/(node2->x - node1->x)) < 1)
    { 
        
        draw_soft_rise(env, node1, node2);
        
    }
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
