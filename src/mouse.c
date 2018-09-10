/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 15:43:00 by tsergien          #+#    #+#             */
/*   Updated: 2018/09/07 15:43:01 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
**		Mouse button codes
**		Left button — 1
**		Right button —  2
**		Third (Middle) button — 3
**		Scroll Up — 4
**		Scroll Down — 5
**		Scroll Left — 6
**		Scroll Right — 7
*/

int		mouse_press(int button, int x, int y, t_fdf *f)
{
	x = y;
	if (button == 4)
		zooming(24, f);
	else if (button == 5)
		zooming(27, f);
	else if (button == 3)
		change_color(f);
	else if (button == 1)
	{
		set_dot(&f->mouse.pos, x, y);
		f->mouse.press = 1;
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_fdf *f)
{
	x = y;
	(void)f;
	if (button == 1)
		f->mouse.press = 0;
	return (0);
}

int		mouse_move(int x, int y, t_fdf *f)
{
	t_vector		v;

	if (f->mouse.press == 2)
		f->p->color++;
	else if (f->mouse.press == 1)
	{
		f->mouse.press = 2;
		set_dot(&f->mouse.pos, x, y);
		return (0);
	}
	else
		return (0);
	if (f->mouse.pos.x == x && f->mouse.pos.y == y)
		return (0);
	set_vector(&v, (double)(y - f->mouse.pos.y) / 300, 0,
	(double)(x - f->mouse.pos.x) / 300);
	rotate(f->m, v);
	my_draw(f);
	set_dot(&f->mouse.pos, x, y);
	return (0);
}
