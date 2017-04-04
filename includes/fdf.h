#ifndef FDF_H
#define FDF_H

# include <mlx.h>
# include "define.h"
# include "struct.h"
# include <math.h>
#include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

/*
* change_view.c
*/
void    trace(t_env *env);
void    translation(t_env *env, int number);
void    reinitialise(t_env *env);
void    refresh(t_env *env);
void    zoom(t_env *env);
void    dezoom(t_env *env);
void    choose(t_env *env);
void   moove_z(t_env *env, int i);
void    to_other(t_env *env, int i);
void    rotation(t_env *env, int i);
t_node  **rotation_z(t_node **map, int len_x, int len_y);


/*
* draw.c 
*/
int     right_color(t_node *node1, t_node *node2);
char     *altitude_color(t_env *env, t_node *node);
void     get_extreme_xy_after_transform(t_env *env, t_node **map);
void    draw_map(t_env *env, t_node **map);
void    draw_vertical(t_env *env, t_node *node1, t_node *node2);
void    draw_horizontal(t_env *env, t_node *node1, t_node *node2);
void    draw_soft_rise(t_env *env, t_node *node1, t_node *node2);
void    draw_high_rise(t_env *env, t_node *node1, t_node *node2);
void    draw_segment(t_env *env, t_node *node1, t_node *node2);
void    draw_link(t_env *env, t_node **map);
t_node *new_coord(t_env *env, t_node *node);
char     *progressive_color(t_node *node1, t_node *node2, int i);
void    which_proj(t_env *env, t_mat *mat, t_node *node);
void				get_extreme_after_transform(t_env *env, t_node **map);



/*
* error.c
*/
void	error_no_conform(void);
void	error_no_file(void);

/*
* event_funct.c
*/
int     mouse_funct(int button, int x, int y, t_env *env);
int     key_funct(int keycode, t_env *env);


/*
* ft_itohex.c
*/

char	*ft_itohex(int i);

/*
* getmap.c
*/
void	get_extreme(t_env *env, t_node **map);
void    scale(t_env *env, t_node **map);
void    rescale(t_env *env, t_node **map);
t_node		**get_map(int fd, t_env *env);
 int		get_color(char *str);
 char		*homogene_color(char *str);

/*
* init_env.c
*/
void	new_one(t_env *env);
void	new_two(t_env *env);
t_env	*new_env();
t_env	*init_env(int fd, char *av1);

/*
* init_img.c
*/
int    set_color(t_env *env, t_node *node);
void    mlx_put_pixel_to_image(t_env *env, t_node *node);
t_img	*init_img(t_env *env, int height, int width);
void	fill_img(t_env *env, int *h, int *w);

/*
* init_node.c
*/
t_node	*new_node();
t_node	*init_node(int x0, int y0, int z0, char *color0, int color_num0);
void	display_map(t_node **map, t_env *env);
void	display_node(t_node *node);

/*
* main.c
*/

t_env	*handle_error(int argc, char **argv);
char    *get_file_name(char *av1);
void    ft_hook(t_env *env);


/*
* print_string.c
*/
int    print_title(t_env *env);
void    print_coord(int x, int y, t_env *env);
void     print_image_back(t_env *env);
void     print_image_supp(t_env *env);
void     print_image_graph(t_env *env);
void     print_all(t_env *env);
void    print_image_sign(t_env *env);

/*
* projection.c
*/
t_node  **proj_para(t_env *env, t_node **map);
t_node  **proj_iso(t_env *env, t_node **map);
t_node **rotation_y(t_node **map, int len_x, int len_y);
void    transform(t_env *env, t_node **map, t_node **new, int j);



















#endif
