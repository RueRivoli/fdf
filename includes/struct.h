#ifndef STRUCT_H

# define STRUCT_H

typedef struct s_img
{
	void	*img;
	char	*data;
	int	bpp;
	int	sizeline;
	int	endian;
}		t_img;

typedef struct s_node
{
	int		x;
	int		y;
	int		z;
	int		color;
}		t_node;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_node	**map;
	int		len;
}			t_env;


#endif
