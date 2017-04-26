/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:01:13 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/26 14:02:33 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_no_conform(void)
{
	ft_putstr("Le fichier n'est pas conforme\n");
}

void	error_no_file(void)
{
	ft_putstr("Le fichier n'existe pas\n");
}

void	error_image(void)
{
	ft_putstr("Il semblerait que les images soient mal stockees.\
 A bon entendeur..");
}
