/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:50:52 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/13 18:18:13 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				exit_x(int key, t_fdf *f)
{
	(void)key;
	(void)f;
	exit(0);
	return (0);
}

static int		usage(int fd)
{
	if (read(fd, 0, 0) < 0)
		write(1, "./fdf accepts only text files.\n", 31);
	else
		write(1, "Usage: ./fdf file\n", 18);
	return (0);
}

t_fdf			*init_ptr(void)
{
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	t_fdf			*f;

	bits_per_pixel = 32;
	size_line = WIN_WIDTH;
	endian = 1;
	f = (t_fdf *)malloc(sizeof(t_fdf));
	if (!f)
		return (0);
	f->p = (t_ptrs *)malloc(sizeof(t_ptrs));
	f->p->mlx_ptr = mlx_init();
	f->p->win_ptr = mlx_new_window(f->p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	f->p->img_ptr = mlx_new_image(f->p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	f->p->img = (int *)mlx_get_data_addr(f->p->img_ptr, &bits_per_pixel,
			&size_line, &endian);
	f->p->color = WHITE;
	f->p->limit_turn_off = 0;
	f->mouse.press = 0;
	set_dot(&f->mouse.pos, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	f->p->help = 1;
	return (f);
}

int				main(int argc, char **argv)
{
	int				fd;
	t_fdf			*f;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || read(fd, 0, 0) < 0)
		return (usage(fd));
	f = init_ptr();
	f->m = get_matrix(fd);
	if (!f || !f->m)
		return (0);
	rotate(f->m, *f->m->angle);
	set_vector(f->m->angle, 0.5, 0.4, -0.1);
	my_draw(f);
	mlx_hook(f->p->win_ptr, 4, 1L << 2, mouse_press, f);
	mlx_hook(f->p->win_ptr, 5, 1L << 3, mouse_release, f);
	mlx_hook(f->p->win_ptr, 6, 1L << 13, mouse_move, f);
	mlx_hook(f->p->win_ptr, 2, 1L << 0, deal_keys, f);
	mlx_hook(f->p->win_ptr, 17, 1L << 17, exit_x, f);
	system("leaks fdf -q");////////////////////
	mlx_loop(f->p->mlx_ptr);
	return (0);
}
