/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:43:21 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/16 15:43:24 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# define WIN_WIDTH 1800
# define WIN_HEIGHT 1150
# include <stdio.h>//

typedef struct		s_ptrs
{
	void			*win_ptr;
	void			*mlx_ptr;
	int				color;
}					t_ptrs;

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef struct		s_dotd
{
	double			x;
	double			y;
}					t_dotd;
/*
**		for matrix t_dot is: x->[height], y->[color]
*/
typedef struct		s_matrix
{
	t_dot			**m;
	int				rows;
	int				cols;
}					t_matrix;

typedef struct		s_lines
{
	char			*data;
	struct s_lines	*next;
}					t_lines;

/*
**		READING
*/
t_matrix			*get_matrix(int fd);
/*
**		LINES
*/
void				put_line(t_ptrs *p, t_dot o1, t_dot o2);
void				line_wu(t_ptrs *p, t_dot a, t_dot b);
void				darken(int *col, double c);
/*
**		GRID
*/
void				draw_grid(t_ptrs *p, t_matrix *m);
#endif
