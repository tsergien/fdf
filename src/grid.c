/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 17:04:50 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/23 17:04:53 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			clear_all(t_ptrs *p)
{
	int		i;

	i = -1;
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	while (++i < WW)
		p->img[i] = 0;
}

static void		set_vals(t_fdf *f, t_dotd *start)
{
	start->x = WIN_WIDTH / 2 - f->m->rot_m[f->m->rows / 2]
				[f->m->cols / 2].x * f->m->scale;
	start->y = WIN_HEIGHT / 2 - f->m->rot_m[f->m->rows / 2]
				[f->m->cols / 2].y * f->m->scale;
	start->x += f->m->shift.x;
	start->y += f->m->shift.y;
}

static void		connect_next(t_fdf *f, int i, int j)
{
	t_dotd	cur;
	t_dotd	next;
	t_dotd	start;

	set_vals(f, &start);
	cur.x = start.x + f->m->scale * f->m->rot_m[i][j].x;
	cur.y = start.y + f->m->scale * f->m->rot_m[i][j].y;
	if (j + 1 < f->m->cols)
	{
		f->m->grad.x = f->m->m[i][j].y == 0 ? f->p->color : f->m->m[i][j].y;
		f->m->grad.y = f->m->m[i][j + 1].y == 0 ? f->p->color :
		f->m->m[i][j + 1].y;
		next.x = start.x + f->m->scale * f->m->rot_m[i][j + 1].x;
		next.y = start.y + f->m->scale * f->m->rot_m[i][j + 1].y;
		line_wu(f, cur, next);
	}
	if (i + 1 < f->m->rows)
	{
		f->m->grad.x = f->m->m[i][j].y == 0 ? f->p->color : f->m->m[i][j].y;
		f->m->grad.y = f->m->m[i + 1][j].y == 0 ? f->p->color :
		f->m->m[i + 1][j].y;
		next.x = start.x + f->m->scale * f->m->rot_m[i + 1][j].x;
		next.y = start.y + f->m->scale * f->m->rot_m[i + 1][j].y;
		line_wu(f, cur, next);
	}
}

void			my_draw(t_fdf *f)
{
	int		i;
	int		j;

	i = -1;
	clear_all(f->p);
	while (++i < f->m->rows)
	{
		j = -1;
		while (++j < f->m->cols)
			connect_next(f, i, j);
	}
	mlx_put_image_to_window(f->p->mlx_ptr, f->p->win_ptr, f->p->img_ptr, 0, 0);
	if (f->p->help)
		print_help(f);
}
