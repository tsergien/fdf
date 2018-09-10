/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:24:42 by tsergien          #+#    #+#             */
/*   Updated: 2018/09/10 15:24:44 by tsergien         ###   ########.fr       */
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

int				handle_color(int col, int dif, int pos, int other_col)
{
	int		R;
	int		G;
	int		B;
	double	k;
	int		res;

	k = (double)pos / dif;
	R = k * (col >> 16) + (1 - k) * (other_col >> 16);
	G = k * ((col & 0xff00) >> 8) + (1 - k) * ((other_col & 0xff00) >> 8);
	B = k * (col & 0xff) + (1 - k) * (other_col & 0xff);
	res = (R << 16) + (G << 8) + B;
	return (res);
}
