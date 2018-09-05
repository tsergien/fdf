/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 14:52:45 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/28 14:52:46 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void		x_axis(t_matrix *m, double a)
{
	int		i;
	int		j;
	double	y;
	double	z;

	i = -1;
	while (++i < m->rows)
	{
		j = -1;
		while (++j < m->cols)
		{
			y = m->rot_m[i][j].y;
			z = m->rot_m[i][j].z;
			m->rot_m[i][j].y = y * cos(a) + z * sin(a);
			m->rot_m[i][j].z = z * cos(a) - y * sin(a);
		}
	}
}

static void		y_axis(t_matrix *m, double b)
{
	int		i;
	int		j;
	double	x;
	double	z;

	i = -1;
	while (++i < m->rows)
	{
		j = -1;
		while (++j < m->cols)
		{
			x = m->rot_m[i][j].x;
			z = m->rot_m[i][j].z;
			m->rot_m[i][j].x = x * cos(b) + z * sin(b);
			m->rot_m[i][j].z = -x * sin(b) + z * cos(b);
		}
	}
}

static void		z_axis(t_matrix *m, double g)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = -1;
	while (++i < m->rows)
	{
		j = -1;
		while (++j < m->cols)
		{
			x = m->rot_m[i][j].x;
			y = m->rot_m[i][j].y;
			m->rot_m[i][j].x = x * cos(g) - y * sin(g);
			m->rot_m[i][j].y = x * sin(g) + y * cos(g);
		}
	}
}

void		rotate_to_start(t_matrix *m)
{
	t_vector	v;

	v.x = 0 - m->angle.x;
	v.y = 0 - m->angle.y;
	v.z = 0 - m->angle.z;
	rotate(m, v);
}

void		rotate(t_matrix *m, t_vector angle)
{
	x_axis(m, angle.x);
	y_axis(m, angle.y);
	z_axis(m, angle.z);
	m->angle.x += angle.x;
	m->angle.y += angle.y;
	m->angle.z += angle.z;
}
