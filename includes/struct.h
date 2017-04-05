#ifndef STRUCT_H

# define STRUCT_H

typedef struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}		t_img;

typedef struct s_node
{
	int		x;
	int		y;
	int		z;
	int		color_num;
	float	rap;
}		t_node;

typedef struct s_mat
{
	int x;
    int y;
    int z;
    int a;
    int b;
	int c;
}				t_mat;

typedef struct	s_ext
{
	int 	min_x;
	int 	min_y;
	int 	max_x;
	int     max_y;
	int 	max_z;
	int		min_z;
	int		min_xl;
	int 	min_yl;
	int 	max_xl;
	int     max_yl;
	int 	max_zl;
	int		min_zl;
}				t_ext;


typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img 	*back_img;
	t_img	*sup_img;
	t_img	*church_img;
	t_node	**map;
	int		len_x;
	int 	len_y;
	t_ext *extr;
	int 	x;
	int 	y;
	float	zoom;
	int		trans_x;
	int		trans_y;
	float	moove_z;
	int 	rot_x;
	int 	rot_y;
	int 	rot_z;
	int		rot_ite;
	int		type_proj;
	int		bool_color;
	char	*filename;
	t_mat	mat;

}			t_env;


#endif
