#include "fdf.h"
#include <stdio.h>

int     mouse_funct(int button, int x, int y, t_env *env)
{
    printf("button : %d \n", button);
    if (button == SCROLL_UP)
        zoom(env, x, y);
    else if (button == SCROLL_DOWN)
        dezoom(env, x, y);
    print_coord(x, y, env);
    return (0);
}

int     key_funct(int keycode, t_env *env)
{
    printf("keycode : %d\n", keycode);
    if (keycode == TOUCH_ESC)
        exit(1);
    else if (keycode == ARROW_LEFT)
        translation(env, 0);
    else if (keycode == ARROW_DOWN)
        translation(env, 1);
    else if (keycode == ARROW_RIGHT)
        translation(env, 2);
    else if (keycode == ARROW_UP)
        translation(env, 3);
    else if (keycode == TOUCH_O)
        recenter(env);
    else if (keycode == TOUCH_PLUS)
        recenter(env);
    else if (keycode == TOUCH_LESS)
        recenter(env);
    return (0);
}
