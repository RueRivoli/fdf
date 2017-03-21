#include "fdf.h"

int     key_funct(int keycode, t_env *env)
{
    keycode++;
    env->x = 1;
    return (0);
}
