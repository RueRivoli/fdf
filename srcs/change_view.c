/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:01:56 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/10 15:08:25 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**number 0 : translation to left
**number 1 : translation to down
**number 2 : translation to right
**number 3 : translation to up
**rotation 0 : rotation on x positive
**rotation 1 : rotation on x negative
**rotation 2 : rotation on y positive
**rotation 3 : rotation on y negative
**rotation 4 : rotation on z positive
**rotation 5 : rotation on z negative
*/

void		moove_z(t_env *env, int i)
{
	if (i == 1)
		env->moove_z = env->moove_z * COEFF_Z;
	else if (i == 0)
		env->moove_z = env->moove_z * COEFF_ZD;
	refresh(env);
}

void		translation(t_env *env, int number)
{
	if (number == 0)
		env->trans_x--;
	else if (number == 2)
		env->trans_x++;
	else if (number == 3)
		env->trans_y--;
	else if (number == 1)
		env->trans_y++;
	else
		;
	refresh(env);
}

void		rotation(t_env *env, int i)
{
	if (i == 0)
		env->rot_x++;
	else if (i == 1)
		env->rot_x--;
	else if (i == 2)
		env->rot_y++;
	else if (i == 3)
		env->rot_y--;
	else if (i == 4)
		env->rot_z++;
	else if (i == 5)
		env->rot_z--;
	refresh(env);
}

void		zoom(t_env *env)
{
	env->zoom = env->zoom * COEFF_ZOOM;
	refresh(env);
}

void		dezoom(t_env *env)
{
	env->zoom = env->zoom / COEFF_ZOOM;
	refresh(env);
}
