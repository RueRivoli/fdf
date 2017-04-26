/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:07:32 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/10 12:11:24 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			mouse_funct(int button, int x, int y, t_env *env)
{
	ft_putstr("button :\n");
	ft_putnbr(button);
	if (button == SCROLL_UP || button == SCROLL_BIS || button == SCROLL_OTHER)
		zoom(env);
	else if (button == SCROLL_DOWN)
		dezoom(env);
	print_coord(x, y, env);
	return (0);
}

void		key_funct_2(int keycode, t_env *env)
{
	if (keycode == TOUCH_LESS)
		moove_z(env, 0);
	else if (keycode == TOUCH_P)
		to_other(env, 1);
	else if (keycode == TOUCH_I)
		to_other(env, 0);
	else if (keycode == TOUCH_S)
		rotation(env, 0);
	else if (keycode == TOUCH_D)
		rotation(env, 1);
	else if (keycode == TOUCH_Z)
		rotation(env, 2);
	else if (keycode == TOUCH_E)
		rotation(env, 3);
	else if (keycode == TOUCH_R)
		rotation(env, 4);
	else if (keycode == TOUCH_T)
		rotation(env, 5);
}

int			key_funct(int keycode, t_env *env)
{
	ft_putstr("keycode :\n");
	ft_putnbr(keycode);
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
		reinitialise(env);
	else if (keycode == TOUCH_PLUS)
		moove_z(env, 1);
	else
		key_funct_2(keycode, env);
	return (0);
}
