/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gnl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 00:34:30 by sbump             #+#    #+#             */
/*   Updated: 2019/11/28 20:08:49 by sbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		my_break(char **line, char **rmr, char *buf)
{
	char *tmp;
	char *tmp2;
	char *p_n;

	if ((p_n = ft_strchr(buf, '\n')))
	{
		if (buf[0] == '\n')
			tmp = NULL;
		tmp = ft_strsub(buf, 0, (ft_strlen(buf) - ft_strlen(p_n)));
		free(*rmr);
		*rmr = ft_strdup(++p_n);
		if (tmp)
		{
			tmp2 = *line;
			*line = ft_strjoin(*line, tmp);
			free(tmp2);
			free(tmp);
		}
		return (1);
	}
	return (0);
}

int		ch_rmr(char **line, char **rmr)
{
	char	*p_n;
	char	*tmp;

	if (*rmr)
	{
		if ((p_n = ft_strchr(*rmr, '\n')))
		{
			if (*rmr[0] == '\n')
				*line = NULL;
			*line = ft_strsub(*rmr, 0, (ft_strlen(*rmr) - ft_strlen(p_n)));
			tmp = *rmr;
			*rmr = ft_strdup(++p_n);
			free(tmp);
			return (1);
		}
		*line = ft_strdup(*rmr);
		ft_strclr(*rmr);
	}
	return (0);
}

int		get_line(int fd, char **line, char **rmr)
{
	int			n;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || !line || read(fd, buf, 0) || !(BUFF_SIZE))
		return (-1);
	*line = NULL;
	if (ch_rmr(line, rmr) == 1)
		return (1);
	while ((n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		if (my_break(line, rmr, buf) == 1)
			break ;
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		free(tmp);
	}
	return (n || ft_strlen(*line) ? 1 : 0);
}

t_gnl	*source(int fd)
{
	t_gnl	*new;

	new = (t_gnl*)malloc(sizeof(t_gnl));
	new->fd = fd;
	new->rmr = NULL;
	new->next = NULL;
	return (new);
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*tmp;

	if (head == NULL)
		head = source(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = source(fd);
		tmp = tmp->next;
	}
	return (get_line(tmp->fd, line, &tmp->rmr));
}
