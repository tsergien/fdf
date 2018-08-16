/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsergien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 18:13:42 by tsergien          #+#    #+#             */
/*   Updated: 2018/08/16 18:13:44 by tsergien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
// Remember to make optimum use of your libft! 
// The use of get_next_line, ft_split and ft_getnbr will 
// allow you to quickly and simply read data from the file.
int			**get_matrix(int fd)
{
	int		**m;
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{

	}
}
