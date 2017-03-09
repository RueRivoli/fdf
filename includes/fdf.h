#ifndef FDF_H
#define FDF_H

# include <mlx.h>
# include "define.h"
# include "struct.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

t_img	*init_img(t_env *env);
t_env	*init_env();
t_node	*new_node();
t_node	*init_node(int x0, int y0, int z0, int color0);
t_env	*new_env();
t_env	*init_env(int fd);
t_node	**get_map(int fd);
t_node	*insert_node(t_node *node, t_node *new);
void	display_map(t_node **map, int len);
void	display_node(t_node *node);
#endif