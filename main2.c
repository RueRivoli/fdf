#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img_ptr;
}				t_env;

void	draw(void *mlx,  void *win)
{
	int x;
	int y;

	y = 100;
	while (y < 200)
	{
		x = 100;
		while (x < 200)
		{
			mlx_pixel_put(mlx, win, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

int		key_hook(int keycode, t_env *e)
{
	printf("key : %d\n", keycode);
	if (keycode == 53)
		exit(0);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_env *e)
{
	printf("mouse : %d : (%d, %d)\n", button, x, y);
	return (0);
}

int		expose_hook(t_env *e)
{
	draw(e->mlx, e->win);
	return (0);
}

int		main()
{
	t_env e;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 400, 400, "mlx 42");
	e.img_ptr = mlx_new_image(e.mlx, 300, 300);
	mlx_put_image_to_window(e.mlx, e.win, e.img_ptr, 50, 50);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_mouse_hook(e.win, mouse_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
