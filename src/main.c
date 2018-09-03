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

static int	usage()
{
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

// fix grid
// fix rotating
/* write greeting
// for (int i = 0; i < WIN_WIDTH; i = i + 50)
	// {
	// 	o2.y = i;
	// 	darken(&(p->color), 0.5);
	// 	if (i % 500 == 0)
	// 		p->color = 0xe059c5;
	// 	line_wu(p, o2, o1);
	// }*/
/*
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
			   int *size_line, int *endian);
**  endian : 0 = sever X is little endian, 1 = big endian
*/
void		init_ptr(t_fdf *f)
{
	t_ptrs			*p;
	int				*bits_per_pixel;
	int				*size_line;
	int				*endian;

	bits_per_pixel = (int *)malloc(sizeof(int));
	size_line = (int *)malloc(sizeof(int));
	endian = (int *)malloc(sizeof(int));
	*bits_per_pixel = 32;
	*size_line = WIN_WIDTH;
	*endian = 0;
	p = (t_ptrs *)malloc(sizeof(t_ptrs));
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	p->img_ptr = mlx_new_image(p->mlx_ptr,WIN_WIDTH, WIN_HEIGHT);
	p->img = (int *)malloc(sizeof(int) * WIN_HEIGHT * WIN_WIDTH);
	p->img = (int *)mlx_get_data_addr(p->img_ptr, bits_per_pixel, size_line, endian);
	p->color = GREY_BLUE;
	f->p = p;
}

static void	greeting(t_ptrs *p)
{
	t_dotd	o1;
	t_dotd	o2;

	p->color = 0xe059c5;
	o1.x = 0;
	o1.y = 0;
	o2.x = WIN_WIDTH;
	for (int i = 0; i < WIN_HEIGHT; i = i + 25)
	{
		o2.y = i;
		darken(&(p->color), 0.5);
		if (i % 500 == 0)
			p->color = 0xe059c5;
		line_wu(p, o2, o1);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
	o2.y = WIN_HEIGHT;
	for (int i = WIN_WIDTH; i > 0; i = i - 25)
	{
		o2.x = i;
		darken(&(p->color), 0.5);
		if (i % 500 == 0)
			p->color = 0xe059c5;
		line_wu(p, o1, o2);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
}

int			main(int argc, char **argv)
{
	int				fd;
	t_fdf			*f;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
		return (usage());
	f = (t_fdf *)malloc(sizeof(t_fdf));
	init_ptr(f);
	greeting(f->p);//doesnt work
	printf("1__\n");
	f->m = get_matrix(fd);
	rotate(f->m, f->m->angle);
	printf("3__\n");
	my_draw(f);
	printf("4__\n");


	// system("leaks fdf -quiet");
	mlx_hook(f->p->win_ptr, 2, 5, deal_keys, f);
	mlx_hook(f->p->win_ptr, 17, 131071, exit_x, f);
	mlx_loop(f->p->mlx_ptr);
	free_stuff(f);
	return (0);
}
