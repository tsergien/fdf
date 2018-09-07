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
//before defence:
// system leaks
// flag -g from Makefile
#include "../includes/fdf.h"

static void		free_stuff(t_fdf *f)
{
	int		i;

	i = -1;
	while (++i < f->m->rows)
	{
		free(f->m->m[i]);
		free(f->m->rot_m[i]);
	}
	free(f->m);
	free(f->p->img);
	free(f->p);
}

static int		exit_x(int key, void *param)
{
	(void)param;
	(void)key;
	exit(1);
	return (0);
}

static int	usage(int fd)
{
	if (read(fd, 0, 0) < 0)
		write(1, "./fdf accepts only text files.\n", 31);
	else
		write(1, "Usage: ./fdf file\n", 18);
	return (0);
}

void	print_matrix_rot(t_matrix *m)
{
	int i = -1;
	printf("Matrix rot\n");
	while (++i < m->rows)
	{
		int j = -1;
		while (++j < m->cols)
			printf("%3.0f, %3.0f, %3.0f | ", m->rot_m[i][j].x, m->rot_m[i][j].y, m->rot_m[i][j].z);
		printf("\n");
	}
}
void	print_matrix(t_matrix *m)
{
	int i = -1, j = -1;
	printf("Matrix\n");
	printf("cols: %d, rows: %d\n", m->cols, m->rows);
	while (++i < m->rows)
	{
		j = -1;
		while (++j < m->cols)
			printf("%3d | ", m->m[i][j].x);
			// printf("%3d,%5x | ", m->m[i][j].x, m->m[i][j].y);
		printf("\n");
	}
}

void		init_ptr(t_fdf *f)
{
	t_ptrs			*p;
	int				bits_per_pixel;
	int				size_line;
	int				endian;

	bits_per_pixel = 32;
	size_line = WIN_WIDTH;
	endian = 1;
	p = (t_ptrs *)malloc(sizeof(t_ptrs));
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	p->img_ptr = mlx_new_image(p->mlx_ptr,WIN_WIDTH, WIN_HEIGHT);
	p->img = (int *)mlx_get_data_addr(p->img_ptr, &bits_per_pixel, &size_line, &endian);
	p->color = WHITE;
	f->p = p;
}

// static void	greeting(t_ptrs *p)
// {
// 	t_dotd	o1;
// 	t_dotd	o2;

// 	p->color = 0xe059c5;
// 	o1.x = 0;
// 	o1.y = 0;
// 	o2.x = WIN_WIDTH;
// 	for (int i = 0; i < WIN_HEIGHT; i = i + 25)
// 	{
// 		o2.y = i;
// 		darken(&(p->color), 0.5);
// 		if (i % 500 == 0)
// 			p->color = 0xe059c5;
// 		line_wu(p, o2, o1);
// 		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
// 	}
// 	o2.y = WIN_HEIGHT;
// 	for (int i = WIN_WIDTH; i > 0; i = i - 25)
// 	{
// 		o2.x = i;
// 		darken(&(p->color), 0.5);
// 		if (i % 500 == 0)
// 			p->color = 0xe059c5;
// 		line_wu(p, o1, o2);
// 		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
// 	}
// }

int			main(int argc, char **argv)
{
	int				fd;
	t_fdf			*f;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || read(fd, 0, 0) < 0)
		return (usage(fd));
	f = (t_fdf *)malloc(sizeof(t_fdf));
	init_ptr(f);
	//greeting(f->p);//doesnt work
	f->m = get_matrix(fd);
	if (!f->m)
		return (0);
	rotate_to_start(f->m);
	my_draw(f);

	//system("leaks fdf -quiet");
	//mlx_mouse_hook (f->win_ptr, mouse, f); mouse = int (*funct_ptr)(), 
	mlx_hook(f->p->win_ptr, 2, 5, deal_keys, f);
	mlx_hook(f->p->win_ptr, 17, 1L << 17, exit_x, f);
	mlx_hook(f->p->win_ptr, 4, 1L << 17, mouse_press, f);//int mouse_press(int button, int x, int y, void *param)
	mlx_hook(f->p->win_ptr, 5, 1L << 17, mouse_release, f);//int mouse_release(int button, int x, int y, void *param)
	mlx_hook(f->p->win_ptr, 6, 1L << 17, mouse_move, f);//int mouse_move(int x, int y, void *param)
	mlx_loop(f->p->mlx_ptr);
	free_stuff(f);//mb move higher
	return (0);
}
/*
Mouse button codes
Left button — 1
Right button —  2
Third (Middle) button — 3
Scroll Up — 4
Scroll Down — 5
Scroll Left — 6
Scroll Right — 7
*/