/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:51:44 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/14 16:51:44 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_split(char *str, char c)
{
	int		i;
	char		*res;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = (char*)malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] && str[i] != c)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
