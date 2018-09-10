/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 12:38:02 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/22 12:38:04 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		xxyy(t_fdf *f, t_dotd *a, t_dotd *b, int steep)
{
	if (steep)
	{
		ft_swap(&a->x, &a->y, sizeof(a->x));
		ft_swap(&b->x, &b->y, sizeof(a->x));
	}
	if (b->x < a->x)
	{
		ft_swap(&a->y, &b->y, sizeof(a->x));
		ft_swap(&a->x, &b->x, sizeof(a->x));
		ft_swap(&f->m->grad.x, &f->m->grad.y, sizeof(&f->m->grad.x));
	}
	return (0);
}

static t_dotd	handle_dot_start(t_ptrs *p, t_dotd *o, t_dotd *ig, int steep)
{
	double	xend;
	double	yend;
	double	xgap;
	t_dotd	pxl;

	xend = my_round(o->x);
	yend = o->y + ig->y * (xend - o->x);
	xgap = 1 - my_fpart(o->x + 0.5);
	pxl.x = xend;
	pxl.y = (int)(yend + 0.5);
	if (steep)
	{
		my_plot(p, pxl.y, pxl.x, (1 - my_fpart(yend)) * xgap);
		my_plot(p, pxl.y + 1, pxl.x, my_fpart(yend) * xgap);
	}
	else
	{
		my_plot(p, pxl.x, pxl.y, (1 - my_fpart(yend)) * xgap);
		my_plot(p, pxl.x, pxl.y + 1, my_fpart(yend) * xgap);
	}
	ig->x = yend + ig->y;
	return (pxl);
}

static t_dotd	handle_dot_end(t_ptrs *p, t_dotd *o, double gradient, int steep)
{
	double	xend;
	double	yend;
	double	xgap;
	t_dotd	pxl;

	xend = my_round(o->x);
	yend = o->y + gradient * (xend - o->x);
	xgap = my_fpart(o->x + 0.5);
	pxl.x = xend;
	pxl.y = (int)(yend + 0.5);
	if (steep)
	{
		my_plot(p, pxl.y, pxl.x, (1 - my_fpart(yend)) * xgap);
		my_plot(p, pxl.y + 1, pxl.x, my_fpart(yend) * xgap);
	}
	else
	{
		my_plot(p, pxl.x, pxl.y, (1 - my_fpart(yend)) * xgap);
		my_plot(p, pxl.x, pxl.y + 1, my_fpart(yend) * xgap);
	}
	return (pxl);
}

void			line_wu(t_fdf *f, t_dotd a, t_dotd b)
{
	t_dotd		*pxl;
	double		x;
	t_dotd		ig;
	int			steep;

	pxl = (t_dotd *)malloc(sizeof(t_dotd) * 2);
	steep = ft_abs(b.y - a.y) > ft_abs(b.x - a.x) ? 1 : 0;
	xxyy(f, &a, &b, steep);
	ig.y = (b.x - a.x == 0) ? 1.0 :(b.y - a.y) / (b.x - a.x);
	pxl[0] = handle_dot_start(f->p, &a, &ig, steep);
	pxl[1] = handle_dot_end(f->p, &b, ig.y, steep);
	x = pxl[0].x;
	if (steep)
		wu_cycles_steep(f, &ig, x, pxl);
	else
		wu_cycles(f, &ig, x, pxl);
	free(pxl);
}
