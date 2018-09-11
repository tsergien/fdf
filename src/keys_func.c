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

void			print_help(t_fdf *f)
{
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 0,
	PINK, "Press H to turn on and off help");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 14,
	PINK, "For rotating use arrows and 0 and . on num.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 28,
	PINK, "For move use 8, 4, 6, 2 on num.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 42,
	PINK, "Back to center - 5 in num.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 56,
	PINK, "For zoom use + and - or scroll.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 70,
	PINK, "You can also use mouse)");
}

int				change_color(t_fdf *f)
{
	if (f->p->color == GREY_BLUE)
		f->p->color = WHITE;
	else if (f->p->color == WHITE)
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

int				zooming(int key, t_fdf *f)
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

int				shift_key(int key, t_fdf *f)
{
	int		sh;

	sh = (key == 86 || key == 91) ? -10 : 10;
	if (key == 91 || key == 84)
		f->m->shift.y = f->m->shift.y + sh;
	else
		f->m->shift.x = f->m->shift.x + sh;
	if (key == 87)
		set_dot(&f->m->shift, 0, 0);
	if (f->m->cols * f->m->scale < WIN_WIDTH - 100 &&
		f->m->rows * f->m->scale < WIN_HEIGHT - 100)
		f->p->limit_turn_off = 1;
	my_draw(f);
	f->p->limit_turn_off = 0;
	return (0);
}

int				high_key(int key, t_fdf *f)
{
	double		mult;
	t_vector	v;

	set_vector(&v, f->m->angle->x, f->m->angle->y, f->m->angle->z);
	set_vector(f->m->angle, 0, 0, 0);
	mult = 0.7;
	if (key == 12)
		mult = 1.3;
	f->m->height *= mult;
	if (mult > 1 && f->m->height == 0)
		f->m->height = 0.3;
	if (f->m->height > 50)
		f->m->height = 50;
	reset_rot_matrix(f->m);
	rotate(f->m, v);
	my_draw(f);
	return (0);
}
