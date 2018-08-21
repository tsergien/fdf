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

static void			set_matrix_elem(t_matrix *m, char *line, int j)
{
	char	**c;
	int		k;
	int		i;
	char	*ptr;

	c = ft_strsplit(line, ' ');
	m->m[j] = (t_dot *)malloc(sizeof(t_dot) * (m->cols));
	i = -1;
	while (c[++i])
	{
		ptr = ft_strchr(c[i], ',');
		if (ptr && *(ptr + 1) != ' ')
			m->m[j][i].y = ft_atoi_base(++ptr, 16);
		else
			m->m[j][i].y = 0xffffff;
		m->m[j][i].x = ft_atoi(c[i]);
	}
	k = -1;
	while (c[++k])
		free(c[k]);
}

static t_matrix		*lines_to_matrix(t_lines *l, int lines)
{
	t_matrix	*m;
	int			j;
	t_lines		*tmp;
	
	m = (t_matrix *)malloc(sizeof(t_matrix));
	m->rows = lines;
	if (l)
		m->cols = count_words(l->data);
	m->m = (t_dot **)malloc(sizeof(t_dot *) * (lines));
	j = 0;
	while (l)
	{
		set_matrix_elem(m, l->data, j);
		tmp = l->next;
		free(l->data);
		free(l);
		l = tmp;
		j++;
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
	return (lines_to_matrix(l, j));
}