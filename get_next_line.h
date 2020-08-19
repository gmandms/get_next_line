/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 12:15:24 by sbump             #+#    #+#             */
/*   Updated: 2019/11/14 00:46:16 by sbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# define BUFF_SIZE 3

typedef struct	s_gnl
{
	int						fd;
	char					*rmr;
	struct s_gnl			*next;
}				t_gnl;

int				get_next_line(int fd, char **line);

#endif
