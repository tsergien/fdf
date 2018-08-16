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

void	put_line(t_ptrs *p, t_dot *o1, t_dot *o2)
{
	int		dx;
	int		dy;
	int		D;
	t_dot	i;

	dx = o2->x - o1->x;
	dy = o2->y - o1->y;
	D = 2 * dy - dx;
	i.y= o1->y;
	i.x = o1->x - 1;
	p->color = 0x72d8b3;
	while (++i.x < o2->x)
	{
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, i.x, i.y, p->color);
		if (D > 0)
		{
			i.y = i.y + 1;
			D = D - 2 * dx;
		}
		else
			D = D + 2 * dy;
	}
}

static void	usage()
{
	write(1, "Usage: ./fdf file\n", 18);
}
// oh god, firstly you should read all that stuff!!!
int		main(int argc, char **argv)
{
	t_ptrs			*p;
	int				fd;
	int				**m;

	fd = open(argv[1], O_WRONLY);
	if (argc != 2)
	{
		usage();
		return (0);
	}	
	p = (t_ptrs *)malloc(sizeof(t_ptrs));
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	m = get_matrix(fd);

	mlx_pixel_put(p->mlx_ptr, p->win_ptr, 250, 250, 0xFFFFFF);
	t_dot o1, o2;
	o1.x = 5;
	o1.y = 10;
	o2.x = 800;
	o2.y = 800;
	put_line(p, &o1, &o2);

	mlx_hook(p->win_ptr, 2, 5, deal_key, (void *)0);
	mlx_hook(p->win_ptr, 17, 1L << 17, exit_x, (void *)0);
	mlx_loop(p->mlx_ptr);
	return (0);
}
