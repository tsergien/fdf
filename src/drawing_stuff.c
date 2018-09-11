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

void			wu_cycles(t_fdf *f, t_dotd *ig, double x, t_dotd *pxl)
{
	int		col;
	int		dif;
	double	start;

	dif = pxl[1].x - x;
	col = f->p->color;
	start = x;
	while (++x < pxl[1].x)
	{
		f->p->color = handle_color(f->m->grad.y, dif, x - start, f->m->grad.x);
		my_plot(f, x, (int)ig->x, 1 - my_fpart(ig->x));
		my_plot(f, x, (int)ig->x + 1, my_fpart(ig->x));
		ig->x += ig->y;
		f->p->color = col;
	}
}

void			wu_cycles_steep(t_fdf *f, t_dotd *ig, double x, t_dotd *pxl)
{
	int		col;
	int		dif;
	double	start;

	dif = pxl[1].x - x;
	start = x;
	col = f->p->color;
	while (++x < pxl[1].x)
	{
		f->p->color = handle_color(f->m->grad.y, dif, x - start, f->m->grad.x);
		my_plot(f, (int)ig->x, x, 1 - my_fpart(ig->x));
		my_plot(f, (int)ig->x + 1, x, my_fpart(ig->x));
		ig->x += ig->y;
		f->p->color = col;
	}
}

static void		manage_scale(t_matrix *m, t_dotd max, t_dotd min)
{
	t_dotd	start;

	set_dotd(&start, WIN_WIDTH / 2 - m->rot_m[m->rows
			/ 2][m->cols / 2].x * m->scale,
	WIN_HEIGHT / 2 - m->rot_m[m->rows / 2][m->cols / 2].y * m->scale);
	while (min.x * m->scale + start.x < 0 || min.y * m->scale + start.y < 0
		|| max.x * m->scale + start.x > WIN_WIDTH ||
		max.y * m->scale + start.y > WIN_HEIGHT)
	{
		m->scale--;
		set_dotd(&start, WIN_WIDTH / 2 - m->rot_m[m->rows / 2]
												[m->cols / 2].x * m->scale,
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
