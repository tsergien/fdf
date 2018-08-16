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
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1200


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

#endif
