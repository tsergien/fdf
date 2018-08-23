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

int				my_round(double x)
{
	return (x + 0.5);
}

double			my_fpart(double x)
{
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
	double	i;
	
	c = 1 - c;
	i = c;
	color = p->color;
	darken(&color, c);
	mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, color);
}

t_dotd			*handle_dot_start(t_ptrs *p, t_dot *o, double gradient)
{
	double	xend;
	double	yend;
	double	xgap;
	double	intery;
	t_dotd	*pxl;

	pxl = (t_dotd *)malloc(sizeof(t_dotd));
	xend = my_round(o->x);
	yend = o->y + gradient * (xend - o->x);
	xgap = 1 - my_fpart(o->x + 0.5);
	pxl->x = xend;
	pxl->y = (int)(yend + 0.5);
	my_plot(p, pxl->x, pxl->y, (1 - my_fpart(yend)) * xgap );
	my_plot(p, pxl->x, pxl->y + 1, my_fpart(yend) * xgap);
	intery = yend + gradient;
	return (pxl);
}

t_dotd			*handle_dot_end(t_ptrs *p, t_dot *o, double gradient)
{
	double	xend;
	double	yend;
	double	xgap;
	t_dotd	*pxl;

	pxl = (t_dotd *)malloc(sizeof(t_dotd));
	xend = my_round(o->x);
	yend = o->y + gradient * (xend - o->x);
	xgap = my_fpart(o->x + 0.5);
	pxl->x = xend;
	pxl->y = (int)(yend + 0.5);
	my_plot(p, pxl->x, pxl->y, (1 - my_fpart(yend)) * xgap);
	my_plot(p, pxl->x, pxl->y + 1, my_fpart(yend) * xgap);
	return (pxl);
}

static int		xxyy(t_ptrs *p, t_dot *a, t_dot *b)
{
	int		i;
	int		y1;

	i = -1;
	if (b->x < a->x)
		ft_swap(b, a, sizeof(a));
	if (a->x == b->x)
	{
		i = a->y < b->y ? a->y : b->y;
		y1 = a->y > b->y ? a->y : b->y;
		while (i++ <= y1)
			mlx_pixel_put(p->mlx_ptr, p->win_ptr, a->x, i, p->color);
	}
	else if (a->y == b->y)
	{
		i = a->x;
		while (i++ <= b->x)
			mlx_pixel_put(p->mlx_ptr, p->win_ptr, i, a->y, p->color);
	}
	return (i == -1 ? 0 : 1);
}

void			line_wu(t_ptrs *p, t_dot a, t_dot b)
{
	t_dotd		*pxl1;
	t_dotd		*pxl2;
	double		x;
	double		intery;
	double		gradient;

	if (xxyy(p, &a, &b))
		return ;
	if (b.x - a.x == 0)
		gradient = 1.0;
	else
		gradient = (double)(b.y - a.y) / (double)(b.x - a.x);
	pxl1 = handle_dot_start(p, &a, gradient);
	pxl2 = handle_dot_end(p, &b, gradient);
	x = pxl1->x;
	intery = a.y + gradient * (my_round(a.x) - a.x) + gradient;
	while (++x < pxl2->x)
	{
		my_plot(p, x, (int)intery, 1 - my_fpart(intery));
		my_plot(p, x, (int)intery + 1, my_fpart(intery));
		intery = intery + gradient;
	}
}


/// just in case
void		put_line(t_ptrs *p, t_dot o1, t_dot o2)
{
	int		dx;
	int		dy;
	int		D;

	if (o1.x < o2.x)
		ft_swap(&o1, &o2, sizeof(o1));
	dx = o2.x - o1.x;
	dy = o2.y - o1.y;
	D = 2 * dy - dx;
	while (o1.x++ <= o2.x)
	{
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, o1.x, o2.y, p->color);
		if (D > 0)
		{
			o1.y = o1.y + 1;
			D = D - 2 * dx;
		}
		else
			D = D + 2 * dy;
	}
}
