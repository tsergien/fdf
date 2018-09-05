/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:39:34 by tsergien          #+#    #+#             */
/*   Updated: 2018/09/05 13:39:36 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

void			wu_cycles(t_ptrs *p, t_dotd *ig, double x, t_dotd *pxl)
{
	while (++x < pxl[1].x)
	{
		my_plot(p, x, (int)ig->x, 1 - my_fpart(ig->x));
		my_plot(p, x, (int)ig->x + 1, my_fpart(ig->x));
		ig->x += ig->y;
	}
}

void			wu_cycles_steep(t_ptrs *p, t_dotd *ig, double x, t_dotd *pxl)
{
	while (++x < pxl[1].x)
	{
		my_plot(p, (int)ig->x, x, 1 - my_fpart(ig->x));
		my_plot(p, (int)ig->x + 1, x, my_fpart(ig->x));
		ig->x += ig->y;
	}
}
