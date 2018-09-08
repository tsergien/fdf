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

static void		manage_scale(t_matrix *m, t_dotd max, t_dotd min)
{
	t_dotd	start;

	set_dotd(&start, WIN_WIDTH / 2 - m->rot_m[m->rows / 2][m->cols / 2].x  * m->scale,
	WIN_HEIGHT / 2 - m->rot_m[m->rows / 2][m->cols / 2].y * m->scale);
	while (min.x * m->scale + start.x < 0 || min.y * m->scale + start.y < 0
	|| max.x * m->scale + start.x > WIN_WIDTH - 200 || max.y * m->scale + start.y > WIN_HEIGHT - 200)
	{
		m->scale--;
		set_dotd(&start, WIN_WIDTH / 2 - m->rot_m[m->rows / 2][m->cols / 2].x  * m->scale,
		WIN_HEIGHT / 2 - m->rot_m[m->rows / 2][m->cols / 2].y * m->scale);
	}
}

void			set_scale(t_matrix *m)
{
	int		i;
	int		j;
	t_dotd	max;
	t_dotd	min;

	m->scale = 27;
	i = -1;
	set_dotd(&max, m->rot_m[0][0].x, m->rot_m[0][0].y);
	set_dotd(&min, m->rot_m[0][0].x, m->rot_m[0][0].y);
	while (++i < m->rows)
	{
		j = -1;
		while (++j < m->cols)
		{
			max.x = fmax(m->rot_m[i][j].x, max.x);
			max.y = fmax(m->rot_m[i][j].y, max.y);
			min.x = fmin(m->rot_m[i][j].x, min.x);
			min.y = fmin(m->rot_m[i][j].y, min.y);
		}
	}
	manage_scale(m, max, min);
}
