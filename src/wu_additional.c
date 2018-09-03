/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:49:10 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/27 14:49:11 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				my_round(double x)
{
	return (int)(x + 0.5);
}
/*
** fractional part
*/
double			my_fpart(double x)
{
	 if (x < 0)
		return 1 - (x - (int)x);
	return (x - (int)x);
}

void			darken(int *col, double c)
{
	int		R;
	int		G;
	int		B;
	int		keyFactor;

	keyFactor = (double)c * 100;
	R = *col >> 16;
	G = (*col & 0xff00) >> 8;
	B = *col & 0xff;
	R = (R - R * keyFactor / 0x100) << 16;
	G = (G - G * keyFactor / 0x100) << 8;
	B = B - B * keyFactor / 0x100;
	*col = R + G + B;
}

void			my_plot(t_ptrs *p, int x, int y, double c)
{
	int		color;
	
	c = 1 - c;
	color = p->color;
	darken(&color, c);
	if (x + WIN_WIDTH * y < WW)
		p->img[x + WIN_WIDTH * y] = color;
}
