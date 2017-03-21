#include "fdf.h"
#include <stdio.h>

int     mouse_funct(int button, int x, int y, t_env *env)
{
    printf("button : %d \n", button);
    print_coord(x, y, env);
    return (0);
}
