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

static int			set_matrix_elem(t_matrix *m, char *line, int j)
{
	char	**c;
	int		i;
	char	*ptr;

	c = ft_strsplit(line, ' ');
	i = 0;
	while (c[i])
		i++;
	if (i != m->cols)
		return (error_cols());
	m->m[j] = (t_dot *)malloc(sizeof(t_dot) * m->cols);
	i = -1;
	while (c[++i])
	{
		ptr = ft_strchr(c[i], ',');
		if (ptr && *(ptr + 1) != ' ')
			m->m[j][i].y = ft_atoi_base((ptr + 1), 16);
		else
			m->m[j][i].y = 16777215;
		m->m[j][i].x = ft_atoi(c[i]);
	}
	i = -1;
	while (c[++i])
		free(c[i]);
	return (1);
}

static void			set_rot_matrix(t_matrix *m)
{
	int			i;
	int			j;

	i = -1;
	m->rot_m = (t_vector **)malloc(sizeof(t_vector *) * m->rows);
	while (++i < m->rows)
	{
		j = -1;
		m->rot_m[i] = (t_vector *)malloc(sizeof(t_vector) * m->cols);
		while (++j < m->cols)
		{
			m->rot_m[i][j].x = j;
			m->rot_m[i][j].y = i;
			m->rot_m[i][j].z = m->m[i][j].x;
		}
	}
}

static t_matrix		*lines_to_matrix(t_lines *l, int lines)
{
	t_matrix	*m;
	int			j;
	t_lines		*tmp;
	int			success;
	
	m = (t_matrix *)malloc(sizeof(t_matrix));
	m->rows = lines;
	if (l)
		m->cols = count_words(l->data);
	m->m = (t_dot **)malloc(sizeof(t_dot *) * lines);
	j = 0;
	while (l)
	{
		success = set_matrix_elem(m, l->data, j);
		tmp = l->next;
		free(l->data);
		free(l);
		l = tmp;
		if (!success)
			return (0);
		j++;
	}
	m->scale = (fmin(WIN_HEIGHT, WIN_WIDTH) - fmin(WIN_HEIGHT, WIN_WIDTH)
				/ 8) /  fmax(m->cols, m->rows);
	return (m);
}

t_matrix			*get_matrix(int fd)
{
	t_lines	*l;
	char	*line;
	int		j;
	t_matrix*m;

	j = 0;
	l = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) == 0)// or check if this line is valid at all
			break ;
		add_lines(&l, line);
		free(line);
		j++;
	}
	m = lines_to_matrix(l, j);
	if (!m)
		return (0);
	set_rot_matrix(m);
	m->angle.x = M_PI / 20;
	m->angle.y = 0;
	m->angle.z = M_PI / 20;
	return (m);
}