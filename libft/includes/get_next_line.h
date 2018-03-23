/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:38:55 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/23 02:21:18 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 42
# include <fcntl.h>

typedef struct	s_varia
{
	int			ret;
	char		*tab[4096];
	char		*rst;
	char		buf[BUFF_SIZE];
}				t_varia;

int				get_next_line(int fd, char **line);

#endif
