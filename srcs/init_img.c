#include "struct.h"
#include "define.h"
#include "fdf.h"


void    mlx_put_pixel_to_image(t_env *env, t_node *node)
{
    int octet;
	char *color_new;
	int a;
	
    octet = env->img->bpp / 8;
	if (env->bool_color == 0)
	{
		color_new = altitude_color(env, node);
		a = get_color(color_new);
	}
	else
		a = node->color_num;
    if (node->x >= 0 && node->y >= 0 && node->x < FENE_X && node->y < FENE_Y)
    {
        ft_memcpy(&env->img->data[octet * node->x + env->img->sizeline *
	node->y], &a, octet);
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
	env->back_img->img = mlx_xpm_file_to_image(env->mlx, "images/magnifique_black.xpm", w, h);
	env->church_img->img = mlx_xpm_file_to_image(env->mlx, "images/church.xpm", w, h);
	env->sup_img->img = mlx_xpm_file_to_image(env->mlx, "images/blancdim.XPM", w, h);	
}

