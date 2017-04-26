/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 14:52:14 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/10 16:51:59 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "define.h"
# include "struct.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

/*
** change_view.c
*/
void				moove_z(t_env *env, int i);
void				translation(t_env *env, int number);
void				rotation(t_env *env, int i);
void				zoom(t_env *env);
void				dezoom(t_env *env);

/*
** draw1.c
*/
void				draw_map(t_env *env, t_node **map);
void				draw_vertical(t_env *env, t_node *node1, t_node *node2);
void				draw_horizontal(t_env *env, t_node *node1, t_node *node2);
void				draw_soft_rise(t_env *env, t_node *node1, t_node *node2);
void				draw_high_rise(t_env *env, t_node *node1, t_node *node2);

/*
** draw2.c
*/
float				proportion_altitude(t_env *env, t_node *node);
t_node				*new_coord(t_env *env, t_node *node);
void				get_extreme_after_transform(t_env *env, t_node **map);
void				draw_segment(t_env *env, t_node *node1, t_node *node2);

/*
** error.c
*/
void				error_no_conform(void);
void				error_no_file(void);

/*
** event_funct.c
*/
int					mouse_funct(int button, int x, int y, t_env *env);
void				key_funct_2(int keycode, t_env *env);
int					key_funct(int keycode, t_env *env);

/*
** ft_itohex.c
*/

char				*ft_itohex(int i);

/*
** getmap.c
*/

int					get_color(char *str);
void				rescale(t_env *env, t_node **map);
t_node				**convert_map(char **split, t_node **map, int *bool_color);
t_node				**get_map(int fd, t_env *env);

/*
** init_env.c
*/
void				new_one(t_env *env);
void				new_two(t_env *env);
t_env				*new_env();
t_env				*init_env(int fd, char *av1);

/*
** init_img.c
*/

void				mlx_put_pixel_to_image(t_env *env, t_node *node);
t_img				*init_img(t_env *env, int height, int width);
void				fill_img(t_env *env, int *h, int *w);

/*
** init_node.c
*/
t_node				*new_node();
t_node				*init_node(int x0, int y0, int z0, int color_num0);
void				display_node(t_node *node);
void				display_map(t_node **map, t_env *env);

/*
** main.c
*/

char				*get_file_name(char *av1);
t_env				*handle_error(int argc, char **argv);
void				ft_hook(t_env *env);

/*
** print1.c
*/
int					print_menu(t_env *env);
int					print_title(t_env *env);
void				print_all(t_env *env);

/*
** print2.c
*/

void				print_image_back(t_env *env);
void				print_image_supp(t_env *env);
void				print_image_graph(t_env *env);
void				print_image_sign(t_env *env);
void				print_coord(int x, int y, t_env *env);

/*
** refresh.c
*/

void				refresh(t_env *env);
void				to_other(t_env *env, int i);
void				reinitialise(t_env *env);
void				fill_length(t_env *env, \
int length, int count);
int 		convertion(char **split, t_node **map, int *bo, char *line);

/*
** useful.c
*/

void				which_proj(t_env *env, t_mat *mat, t_node *node);
float				proportion_altitude(t_env *env, t_node *node);
char				*hex_altitude(int rn, int gn, int bn);
char				*altitude_color(t_env *env, t_node *node);
int					temporaire(int fd, char *line, t_env *env, t_node **map);

#endif
