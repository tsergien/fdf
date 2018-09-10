/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 15:12:46 by tsergien          #+#    #+#             */
/*   Updated: 2018/09/08 15:12:48 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		change_color(t_fdf *f)
{
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

int		zooming(int key, t_fdf *f)
{
	double			new_scale;

	if (key == 24)
	{
		new_scale = f->m->scale + f->m->scale * 0.3;
		if (new_scale * f->m->cols < WIN_WIDTH * 2 &&
		new_scale * f->m->rows < WIN_HEIGHT * 2)
			f->m->scale += f->m->scale * 0.3;
	}
	else if (key == 27)
	{
		new_scale = f->m->scale - f->m->scale * 0.3;
		if (new_scale > 3)
			f->m->scale -= f->m->scale * 0.3;
	}
	my_draw(f);
	return (0);
}

int		shift_key(int key, t_fdf *f)
{
	int		sh;
	int		i;
	int		j;

	sh = (key == 86 || key == 91) ? -1 : 1;
	i = -1;
	while (++i < f->m->rows)
	{
		j = -1;
		while (++j < f->m->cols)
		{
			if (key == 91 || key == 84)
				f->m->shift.y += sh;
			else
				f->m->shift.x += sh;
		}
	}
	if (key == 87)
		set_dot(&f->m->shift, 0, 0);
	if (f->m->cols * f->m->scale < WIN_WIDTH - 100 &&
		f->m->rows * f->m->scale < WIN_HEIGHT - 100)
	f->p->limit_turn_off = 1;
	my_draw(f);
	f->p->limit_turn_off = 0;
	return (0);
}

int		high_key(int key, t_fdf *f)
{
	int			i;
	int			j;
	double		mult;
	t_vector	v;

	i = -1;
	v = f->m->angle;
	rotate_to_start(f->m);
	mult = 0.95;
	if (key == 257)
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
