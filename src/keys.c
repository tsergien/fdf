/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:58:05 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/29 14:58:06 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		deal_key(int key, void *param)
{
	(void)param;
	if (key == 53)
		exit(1);
	return (0);
}

static int		rotate_key(int key, t_fdf *f)
{
	t_vector	a;

	a.x = 0;
	a.y = 0;
	a.z = 0;
	if (key == 126)
		a.x = M_PI / 40;
	else if (key == 125)
		a.x = -M_PI / 40;
	else if (key == 123)
		a.z = M_PI / 40;
	else if (key == 124)
		a.z = -M_PI / 40;
	else if (key == 82)
		a.y = -M_PI / 40;
	else if (key == 65)
		a.y = M_PI / 40;
	rotate(f->m, a);
	my_draw(f);
	return (0);
}

static int		darken_color(t_fdf *f)
{
	darken(&(f->p->color), 0.4);
	my_draw(f);
	return (0);
}

static int	high_key(int key, t_fdf *f)
{
	int			i;
	int			j;
	double		mult;
	t_vector	v;

	i = -1;
	v = f->m->angle;
	rotate_to_start(f->m);
	mult = 0.95;
	if (key == 4)
		mult = 1.05;
	while (++i < f->m->rows)
	{
		j = -1;
		while (++j < f->m->cols)
			f->m->rot_m[i][j].z *= mult;
	}
	rotate(f->m, v);
	my_draw(f);
	return (0);
}

int			deal_keys(int key, t_fdf *f)
{
	if (key == 8)
		return (change_color(f));
	else if ((key >= 86 && key <= 88) || key == 91 || key == 84)
		return (shift_key(key, f));
	else if ((key >= 123 && key <= 126) || key == 82 || key == 65)
		return (rotate_key(key, f));
	else if (key == 24 || key == 27)
		return (zooming(key, f)); 
	else if (key == 2)
		return (darken_color(f));
	else if (key == 53)
		return (deal_key(key, f));
	else if (key == 4 || key == 37)
		return (high_key(key, f));
	return (0);
}