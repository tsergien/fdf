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

static void	connect_next(t_ptrs *p, t_matrix *m, int i, int j)
{
	t_dotd	start;
	t_dotd	cur;
	t_dotd	next;

	start.x = WIN_WIDTH / 2 - m->rot_m[m->cols / 2][m->cols / 2].x / 2 * m->scale;
	start.y = WIN_HEIGHT / 2 - m->rot_m[m->rows / 2][m->rows / 2].y / 2 * m->scale;
	cur.x = start.x + (double)m->scale * m->rot_m[i][j].x;
	cur.y = start.y + (double)m->scale * m->rot_m[i][j].y;
	if (j + 1 < m->cols)// next to the right
	{
		next.x = start.x + (double)m->scale * m->rot_m[i][j + 1].x;
		next.y = start.y + (double)m->scale * m->rot_m[i][j + 1].y;
		line_wu(p, cur, next);
	}
	if (i + 1 < m->rows)// next down
	{
		next.x = start.x + (double)m->scale * m->rot_m[i + 1][j].x;
		next.y = start.y + (double)m->scale * m->rot_m[i + 1][j].y;
		line_wu(p, cur, next);
	}
}

void		my_draw(t_fdf *f)
{
	int		i;
	int		j;

	i = -1;
	while (++i < f->m->rows)
	{
		j = -1;
		while (++j < f->m->cols)
			connect_next(f->p, f->m, i, j);
	}
	mlx_put_image_to_window(f->p->mlx_ptr, f->p->win_ptr, f->p->img_ptr, 0, 0);////////
}
