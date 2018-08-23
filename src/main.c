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

int		exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

static void	usage()
{
	write(1, "Usage: ./fdf file\n", 18);
}
// print net with 0 radians
// look up for rotating formulas
int		main(int argc, char **argv)
{
	t_ptrs			*p;
	int				fd;
	t_matrix		*m;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
	{
		usage();
		return (0);
	}	
	p = (t_ptrs *)malloc(sizeof(t_ptrs));
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");


	m = get_matrix(fd);
/* Matrix printing :)
	// int i = -1, j = -1;
	// while (++i < m->rows)
	// {
	// 	j = -1;
	// 	while (++j < m->cols)
	// 		printf("%3d,%5x | ", m->m[i][j].x, m->m[i][j].y);
	// 	printf("\n");
	// }
*/

	t_dot o1, o2;
	o1.x = 10;
	o1.y = 10;
	o2.x = WIN_WIDTH - 100;
	o2.y = WIN_HEIGHT - 100;
	p->color = 0xedaaed;
	for (int i = 0; i < WIN_WIDTH; i = i + 50)
	{
		o1.x = i;
		//line_wu(p, o2, o1);
		darken(&(p->color), 0.5);
		if (i % 400 == 0)
			p->color = 0xedaaed;
		put_line(p, o1, o2);	
	}
	draw_grid(p, m);

	mlx_hook(p->win_ptr, 2, 5, deal_key, (void *)0);//escape button
	mlx_hook(p->win_ptr, 17, 1L << 17, exit_x, (void *)0);//exit with x
	mlx_loop(p->mlx_ptr);
	// system("leaks fdf -quiet");
	return (0);
}
