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

void			print_help(t_fdf *f)
{
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 0, PINK, "Press H to turn on and off help");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 14, PINK, "For rotating use arrows and 0 and . on num.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 28, PINK, "For move use 8, 4, 6, 2 on num.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 42, PINK, "Back to center - 5 in num.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 56, PINK, "For zoom use + and - or scroll.");
	mlx_string_put(f->p->mlx_ptr, f->p->win_ptr, 20, 70, PINK, "You can also use mouse)");
}

int				help(t_fdf *f)
{
	f->p->help = f->p->help == 1 ? 0 : 1;
	if (f->p->help)
		print_help(f);
	else
	{
		clear_all(f->p);
		my_draw(f);
	}
	return (0);
}

int				deal_keys(int key, t_fdf *f)
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
	else if (key == 257 || key == 256)
		return (high_key(key, f));
	else if (key == 4)
		return (help(f));
	return (0);
}