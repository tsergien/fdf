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

void				add_lines(t_lines **l, char *line)
{
	t_lines	*tmp;

	if (!(*l))
	{
		(*l) = (t_lines *)malloc(sizeof(t_lines));
		(*l)->data = ft_strdup(line);
		(*l)->next = NULL;
	}
	tmp = *l;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_lines *)malloc(sizeof(t_lines));
	tmp->next->data = ft_strdup(line);
	tmp->next->next = NULL;
}

static t_matrix		*char_to_int(t_lines *l, int lines)
{
	t_matrix*m;
	char	**c;
	int		i;
	int		j;
	int		k;

	m = (t_matrix *)malloc(sizeof(t_matrix));
	m->rows = lines;
	if (l)
		m->cols = count_words(l->data);
	m->m = (int **)malloc(sizeof(int *) * (lines));
	j = -1;
	while (l)
	{
		c = ft_strsplit(l->data, ' ');
		m->m[++j] = (int *)malloc(sizeof(int) * (m->cols));
		i = -1;
		while (c[++i])
			m->m[j][i] = ft_atoi(c[i]);
		l = l->next;
		k = -1;
		while (c[++k])
			free(c[k]);
	}
	return (m);
}

t_matrix			*get_matrix(int fd)
{
	t_lines	*l;
	char	*line;
	int		j;

	j = 0;
	l = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		add_lines(&l, line);
		free(line);
		j++;
	}
	return (char_to_int(l, j));
}