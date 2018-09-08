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

void			put_pixel_to_image(t_ptrs *p, int x, int y, int color)
{
	if (x > -1 && y > -1 && x < WIN_WIDTH && y < WIN_HEIGHT)
		p->img[x + y * WIN_WIDTH] = color;
	else if (x + y * WIN_WIDTH < WW && x + y * WIN_WIDTH  > -1
	&& p->limit_turn_off)
	{
		// y = y - x / WIN_WIDTH;
		p->img[x + y * WIN_WIDTH] = color;
	}
}

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

void			my_plot(t_ptrs *p, int x, int y, double c)
{
	int		color;
	
	c = 1 - c;
	color = p->color;
	darken(&color, c);
	put_pixel_to_image(p, x, y, color);
}
