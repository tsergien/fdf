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

void			clear_all(t_ptrs *p)
{
	int		i;

	i = -1;
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	while (++i < WW)
		p->img[i] = 0;
}

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
	if (key == 126)//up
		a.x = M_PI / 20;
	else if (key == 125)//down
		a.x = -M_PI / 20;
	else if (key == 123)//left
		a.z = M_PI / 20;
	else if (key == 124)//right
		a.z = -M_PI / 20;
	clear_all(f->p);
	rotate(f->m, a);
	my_draw(f);
	return (0);
}

static int	shift_key(int key, t_fdf *f)
{
	int		shift;
	int		i;
	int		j;

	shift = f->m->scale / 5;
	clear_all(f->p);
	if (key == 87 || key == 88)//down
		shift = -shift;;
	i = -1;
	while (++i < f->m->rows)
	{
		j = -1;
		while (++j < f->m->cols)
		{
			if (key == 91 || key == 87)
				f->m->rot_m[i][j].y += shift;
			else
				f->m->rot_m[i][j].x += shift;
		}
	}
	my_draw(f);
	return (0);
}

static int		zooming(int key, t_fdf *f)
{
	int		new_scale;

	new_scale = ft_abs(f->m->scale - f->m->scale * 0.3) < 1 ? 10 : f->m->scale * 0.3;
	clear_all(f->p);
	if (key == 24)//+
		f->m->scale += new_scale;
	else if (key == 27)//-
		f->m->scale -= new_scale;
	my_draw(f);
	return (0);
}

static int		darken_color(t_fdf *f)
{
	clear_all(f->p);
	darken(&(f->p->color), 0.4);
	my_draw(f);
	return (0);
}

static int		change_color(t_fdf *f)
{
	clear_all(f->p);
	if (f->p->color == GREY_BLUE)
		f->p->color = L_PURPLE;
	else if (f->p->color == L_PURPLE)
		f->p->color = PINK;
	else if (f->p->color == PINK)
		f->p->color = L_RED;
	else if (f->p->color == L_RED)
		f->p->color = L_BLUE;
	else if (f->p->color == L_BLUE)
		f->p->color = D_BLUE;
	else if (f->p->color == D_BLUE)
		f->p->color = GREEN;
	else if (f->p->color == GREEN)
		f->p->color = YELLOW;
	else if (f->p->color == YELLOW)
		f->p->color = ORANGE;
	else if (f->p->color == ORANGE)
		f->p->color = RED;
	else if (f->p->color == RED)
		f->p->color = RASPBERRY;
	else
		f->p->color = GREY_BLUE;
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
	mult = 0.75;
	if (key == 4)
		mult = 1.25;
	clear_all(f->p);
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
	else if (key >= 123 && key <= 126)
		return (rotate_key(key, f));
	else if (key == 24 || key == 27)
		return (zooming(key, f)); 
	else if (key == 2)
		return (darken_color(f));
	else if ((key >= 86 && key <= 88) || key == 91)
		return (shift_key(key, f));
	else if (key == 53)
		return (deal_key(key, f));
	else if (key == 4 || key == 37)
		return (high_key(key, f));
	return (0);
}