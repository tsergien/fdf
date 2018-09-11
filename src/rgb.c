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
	int		r_comp;
	int		g_comp;
	int		b_comp;
	int		key_factor;

	key_factor = (double)c * 100;
	r_comp = *col >> 16;
	g_comp = (*col & 0xff00) >> 8;
	b_comp = *col & 0xff;
	r_comp = (r_comp - r_comp * key_factor / 0x100) << 16;
	g_comp = (g_comp - g_comp * key_factor / 0x100) << 8;
	b_comp = b_comp - b_comp * key_factor / 0x100;
	*col = r_comp + g_comp + b_comp;
}

int				handle_color(int col, int dif, int pos, int other_col)
{
	int		r_comp;
	int		g_comp;
	int		b_comp;
	double	k;
	int		res;

	k = (double)pos / dif;
	r_comp = k * (col >> 16) + (1 - k) * (other_col >> 16);
	g_comp = k * ((col & 0xff00) >> 8) + (1 - k) * ((other_col & 0xff00) >> 8);
	b_comp = k * (col & 0xff) + (1 - k) * (other_col & 0xff);
	res = (r_comp << 16) + (g_comp << 8) + b_comp;
	return (res);
}
