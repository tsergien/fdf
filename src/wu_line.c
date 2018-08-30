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

static int		equal_coords(t_ptrs *p, t_dotd *a, t_dotd *b, int steep)
{
	double		y1;
	double		i;

	i = -1;
	if (a->x == b->x)
	{
		i = (a->y < b->y ? a->y : b->y) - 1;
		y1 = a->y > b->y ? a->y : b->y;
		while (++i <= y1)
			mlx_pixel_put(p->mlx_ptr, p->win_ptr, a->x, i, p->color);
	}
	else if (a->y == b->y)
	{
		i = a->x - 1;
		while (++i <= b->x)
		{
			if (steep)
				mlx_pixel_put(p->mlx_ptr, p->win_ptr, a->y, i, p->color);
			else
				mlx_pixel_put(p->mlx_ptr, p->win_ptr, i, a->y, p->color);

		}
	}
	return (i == -1 ? 0 : 1);
}

static int		xxyy(t_ptrs *p, t_dotd *a, t_dotd *b, int steep)
{
	if (steep)
	{
		ft_swap(&a->x, &a->y, sizeof(a->x));
		ft_swap(&b->x, &b->y, sizeof(a->x));
	}
	if (b->x < a->x)
		ft_swap(b, a, sizeof(a));
	return (equal_coords(p, a, b, steep));
}

static t_dotd	handle_dot_start(t_ptrs *p, t_dotd *o, double gradient, double *intery, int steep)/////////////5 vars
{
	double	xend;
	double	yend;
	double	xgap;
	t_dotd	pxl;

	xend = my_round(o->x);
	yend = o->y + gradient * (xend - o->x);
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
	*intery = yend + gradient;
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
		my_plot(p,  pxl.y, pxl.x,(1 - my_fpart(yend)) * xgap);
		my_plot(p, pxl.y + 1, pxl.x, my_fpart(yend) * xgap);
	}
	else
	{
		my_plot(p, pxl.x, pxl.y, (1 - my_fpart(yend)) * xgap);
		my_plot(p, pxl.x, pxl.y + 1, my_fpart(yend) * xgap);
	}
	return (pxl);
}

void			line_wu(t_ptrs *p, t_dotd a, t_dotd b)
{
	t_dotd		*pxl;
	double		x;
	double		intery;
	double		gradient;
	int			steep;

	pxl = (t_dotd *)malloc(sizeof(t_dotd) * 2);
	steep = ft_abs(b.y - a.y) > ft_abs(b.x - a.x) ? 1 : 0;
	if (xxyy(p, &a, &b, steep))
		return ;
	if (b.x - a.x == 0)
		gradient = 1.0;
	else
		gradient = (double)(b.y - a.y) / (double)(b.x - a.x);
	pxl[0] = handle_dot_start(p, &a, gradient, &intery, steep);
	pxl[1] = handle_dot_end(p, &b, gradient, steep);
	x = pxl[0].x;
	if (steep)
	{
		while (++x < pxl[1].x)
		{
			my_plot(p, (int)intery, x, 1 - my_fpart(intery));
			my_plot(p, (int)intery + 1, x, my_fpart(intery));
			intery += gradient;
		}
	}
	else
	{
		while (++x < pxl[1].x)
		{
			my_plot(p, x, (int)intery, 1 - my_fpart(intery));
			my_plot(p, x, (int)intery + 1, my_fpart(intery));
			intery += gradient;
		}
	}
}
