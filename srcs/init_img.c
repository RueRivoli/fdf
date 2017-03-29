#include "struct.h"
#include "define.h"
#include "fdf.h"

/*char 	*set_color(t_env *env, t_node *node)
{
	int z;


	z = env->max_z - env->min_z;
	if (node->z - env->min_z < 0.1 * z)
		return (COLOR_Z_0);
	else if (node->z - env->min_z < 0.2 * z && node->z - env->min_z >= 0.1 * z)
		return (COLOR_Z_1);
	else if (node->z - env->min_z < 0.3 * z && node->z - env->min_z >= 0.2 * z)
		return (COLOR_Z_2);
	else if (node->z - env->min_z < 0.4 * z && node->z - env->min_z >= 0.3 * z)
		return (COLOR_Z_3);
	else if (node->z - env->min_z < 0.5 * z && node->z - env->min_z >= 0.4 * z)
		return (COLOR_Z_4);
	else if (node->z - env->min_z < 0.6 * z && node->z - env->min_z >= 0.5 * z)
		return (COLOR_Z_5);
	else if (node->z - env->min_z < 0.7 * z && node->z - env->min_z >= 0.6 * z)
		return (COLOR_Z_6);
	else if (node->z - env->min_z < 0.8 * z && node->z - env->min_z >= 0.7 * z)
		return (COLOR_Z_7);
	else if (node->z - env->min_z < 0.9 * z && node->z - env->min_z >= 0.9 * z)
		return (COLOR_Z_8);
	else if (node->z - env->min_z > 0.9)
		return (COLOR_Z_9);
	return ("");
}*/

void    mlx_put_pixel_to_image(t_env *env, t_node *node)
{
    int octet;
	char *color_new;
    octet = env->img->bpp / 8;
	if (env->bool_color == 0)
		color_new = altitude_color(env, node);		
	else
		color_new = node->color;
    if (node->x >= 0 && node->y >= 0 && node->x < FENE_X && node->y < FENE_Y)
    {
		/*&(node->color)*/
        ft_memcpy(&env->img->data[octet * node->x + env->img->sizeline *
    node->y], &(color_new), octet);
    }
}

t_img		*init_img(t_env *env, int height, int width)
{
	t_img	*image;
	
	if (!(image = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	
	image->img = mlx_new_image(env->mlx, height, width);
	image->data = mlx_get_data_addr(image->img,\
	 &image->bpp, &image->sizeline, &image->endian);
	 
	return (image);
}

void	fill_img(t_env *env, int *h, int *w)
{
	env->back_img->img = mlx_xpm_file_to_image(env->mlx, "images/magnifique.xpm", w, h);
	env->church_img->img = mlx_xpm_file_to_image(env->mlx, "images/church.xpm", w, h);
	env->sup_img->img = mlx_xpm_file_to_image(env->mlx, "images/blancdim.xpm", w, h);	
}

