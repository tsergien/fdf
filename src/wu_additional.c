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

/*
**	else if (x + y * WIN_WIDTH < WW && f->p->limit_turn_off)
**	{
**		f->m->shift.x %= WIN_WIDTH;
**		f->m->shift.y %= WIN_HEIGHT;
**		if (y < 0)
**			y = WIN_HEIGHT + y;
**		else if (y >= WIN_HEIGHT)
**			y = y - WIN_HEIGHT;
**		if (x < 0 || x >= WIN_WIDTH)
**			y = y - 1;
**		f->p->img[x + y * WIN_WIDTH] = color;
**	}
*/

void			put_pixel_to_image(t_fdf *f, int x, int y, int color)
{
	if (x > -1 && y > -1 && x < WIN_WIDTH && y < WIN_HEIGHT)
		f->p->img[x + y * WIN_WIDTH] = color;
}

int				my_round(double x)
{
	return ((int)(x + 0.5));
}

/*
** fractional part
*/

double			my_fpart(double x)
{
	if (x < 0)
		return (1 - (x - (int)x));
	return (x - (int)x);
}

void			my_plot(t_fdf *f, int x, int y, double c)
{
	int		color;

	c = 1 - c;
	color = f->p->color;
	darken(&color, c);
	put_pixel_to_image(f, x, y, color);
}
