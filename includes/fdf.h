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
int    translation(t_env *env, int number);
void    recenter(t_env *env);
void    zoom(t_env *env, int a, int b);
void    dezoom(t_env *env, int a, int b);


/*
* draw.c 
*/
int     right_color(t_node *node1, t_node *node2);
void    draw_map(t_env *env);
void    draw_vertical(t_env *env, t_node *node1, t_node *node2, int color);
void    draw_horizontal(t_env *env, t_node *node1, t_node *node2, int color);
void    draw_soft_rise(t_env *env, t_node *node1, t_node *node2, int color);
void    draw_high_rise(t_env *env, t_node *node1, t_node *node2, int color);
void    draw_segment(t_env *env, t_node *node1, t_node *node2);
void    draw_link(t_env *env);

/*
* getmap.c
*/
void	get_extreme(t_env *env);
void    scale(t_env *env);
void    rescale(t_env *env);
t_node		**get_map(int fd, t_env *env);

/*
* init_env.c
*/
t_env	*new_env();
t_env	*init_env(int fd, char *av1);

/*
* init_img.c
*/
void    mlx_put_pixel_to_image(t_env *env, t_node *node);
t_img	*init_img(t_env *env, int height, int width);
void	fill_img(t_env *env, int *h, int *w);

/*
* init_node.c
*/
t_node	*new_node();
t_node	*init_node(int x0, int y0, int z0, int color0);
void	display_map(t_node **map, t_env *env);
void	display_node(t_node *node);

/*
* main.c
*/
void    error_no_conform();
void	error_no_file();
char    *get_file_name(char *av1);

/*
* mouse_funct.c
*/
int     mouse_funct(int button, int x, int y, t_env *env);
int     key_funct(int keycode, t_env *env);

/*
* print_string.c
*/
int    print_title(t_env *env);
void    print_coord(int x, int y, t_env *env);
void     print_image_back(t_env *env);
void     print_image_supp(t_env *env);
void     print_image_graph(t_env *env);
void     print_all(t_env *env);

/*
* rotation.c
*/
t_node  **proj_para(t_node **map, int len_x, int len_y);
t_node  **proj_iso(t_node **map, int len_x, int len_y);
t_node **rotation_y(t_node **map, int len_x, int len_y);
t_node  **rotation_z(t_node **map, int len_x, int len_y);



t_node	*insert_node(t_node *node, t_node *new);

















#endif
