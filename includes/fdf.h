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
# include <math.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# define WIN_WIDTH 1800
# define WIN_HEIGHT 1100
# define WW (WIN_HEIGHT * WIN_WIDTH)
# include <stdio.h>//////////////
# define GREY_BLUE 0x667793
# define L_PURPLE 0xa17bc6
# define PINK 0xe7a0ff
# define L_RED 0xdb7891
# define L_BLUE 0x8acbd1
# define D_BLUE 0x3330db
# define GREEN 0x00ff04
# define YELLOW 0xffff00
# define ORANGE 0xfc9f00
# define RED 0xfc1500
# define RASPBERRY 0x7f0347
# define WHITE 0xffffff

// from math.h
// 		M_E             base of natural logarithm, e
//      M_LOG2E         log2(e)
//      M_LOG10E        log10(e)
//      M_LN2           ln(2)
//      M_LN10          ln(10)
//      M_PI            pi
//      M_PI_2          pi / 2
//      M_PI_4          pi / 4
//      M_1_PI          1 / pi
//      M_2_PI          2 / pi
//      M_2_SQRTPI      2 / sqrt(pi)
//      M_SQRT2         sqrt(2)
//      M_SQRT1_2       sqrt(1/2)

typedef struct		s_ptrs
{
	void			*win_ptr;
	void			*mlx_ptr;
	void			*img_ptr;
	int				*img;
	int				color;
}					t_ptrs;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

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
	t_vector		**rot_m;
	int				rows;
	int				cols;
	t_vector		angle;
	double			scale;
}					t_matrix;

typedef struct		s_lines
{
	char			*data;
	struct s_lines	*next;
}					t_lines;

typedef struct		s_fdf
{
	t_ptrs			*p;
	t_matrix		*m;
}					t_fdf;

/*
**		READING
*/
t_matrix			*get_matrix(int fd);
/*
**		LINES
*/
void				line_wu(t_ptrs *p, t_dotd a, t_dotd b);
void				darken(int *col, double c);
int					my_round(double x);
double				my_fpart(double x);
void				my_plot(t_ptrs *p, int x, int y, double c);
void				wu_cycles_steep(t_ptrs *p, t_dotd *ig, double x, t_dotd *pxl);
void				wu_cycles(t_ptrs *p, t_dotd *ig, double x, t_dotd *pxl);
/*
**		GRID
*/
void				my_draw(t_fdf *f);
/*
**		DRAWING
*/
void				clear_all(t_ptrs *p);
void				put_pixel_to_image(t_ptrs *p, int x, int y, int color);
/*
**		ROTATING
*/
void				rotate(t_matrix *m, t_vector angle);
void				rotate_to_start(t_matrix *m);
/*
**		KEYS
*/
int					deal_keys(int key, t_fdf *f);
/*
**		ERRORS
*/
int					error_cols();
#endif
