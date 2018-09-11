/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:14:33 by tsergien          #+#    #+#             */
/*   Updated: 2018/09/05 18:14:35 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		free_char_ar(char **c, int n)
{
	int		i;

	i = -1;
	while (++i < n)
		free(c[i]);
	free(c);
}

int			error_cols(void)
{
	write(2, "Wrong number of cols\n", 21);
	return (0);
}
