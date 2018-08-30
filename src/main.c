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

int		deal_key(int key, void *param)
{
	param = 0;
	if (key == 53)
		exit(1);
	return (0);
}
/*
** yarik super
*/
int		exit_x(int key, void *par)
{
	par = NULL;
	(void)key;// yarik super
	exit(1);
	return (0);
}

static void	usage()
{
	write(1, "Usage: ./fdf file\n", 18);
}
// print net with 0 radians
// look up for rotating formulas
void	print_matrix_rot(t_matrix *m)
{
	int i = -1;
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


// remake for mlx_image_put
// fix grid
// fix rotating

int		main(int argc, char **argv)
{
	t_ptrs			*p;
	int				fd;
	t_matrix		*m;
	t_fdf			*f;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
	{
		usage();
		return (0);
	}
	f = (t_fdf *)malloc(sizeof(t_fdf));
	p = (t_ptrs *)malloc(sizeof(t_ptrs));
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	m = get_matrix(fd);
	p->color = GREY_BLUE;
	f->m = m;
	f->p = p;

	// for (int i = 0; i < WIN_WIDTH; i = i + 50)
	// {
	// 	o2.y = i;
	// 	darken(&(p->color), 0.5);
	// 	if (i % 500 == 0)
	// 		p->color = 0xe059c5;
	// 	line_wu(p, o2, o1);
	// }

	t_vector angle;
	angle.x = M_PI / 3;
	angle.y = M_PI / 4;
	angle.z = 0;

	my_draw(f);
	f->p->color = RASPBERRY;
	rotate(m, angle);
	my_draw(f);


	mlx_key_hook(p->win_ptr, deal_keys, f);

	mlx_hook(p->win_ptr, 2, 5, deal_key, (void *)0);//escape button
	mlx_hook(p->win_ptr, 17, 131071, exit_x, (void *)0);//exit with x
	mlx_loop(p->mlx_ptr);
	// system("leaks fdf -quiet");
	return (0);
}
