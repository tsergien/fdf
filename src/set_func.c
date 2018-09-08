/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 16:27:38 by tsergien          #+#    #+#             */
/*   Updated: 2018/09/08 16:27:39 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			set_vector(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void			set_dotd(t_dotd *a, double x, double y)
{
	a->x = x;
	a->y = y;
}

void			set_dot(t_dot *a, int x, int y)
{
	a->x = x;
	a->y = y;
}
