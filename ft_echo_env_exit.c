/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_env_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 01:43:48 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/01 22:57:38 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cd_not_env(t_env *env)
{
	if (!env->flags_env)
	{
		ft_putendl("minishell: cd: HOME not set");
		return (1);
	}
	else if (env->flags_env && ft_search_env(env, "HOME") == -1)
	{
		ft_putendl("minishell: cd: HOME not set");
		return (1);
	}
	ft_cd2(env);
	return (0);
}

void		ft_exit(t_env *env)
{
	(void)env;
	exit(EXIT_SUCCESS);
}

void		ft_env(t_env *env)
{
	int		i;

	if (!env->flags_env)
		return ;
	i = 0;
	while (env->env[i])
		ft_putendl(env->env[i++]);
}

int			ft_verif_echo(t_env *env, int *flags_d, int *flags_c)
{
	if (env->str_s[1] && env->str_s[1][0] == '"')
	{
		*flags_d = 1;
		return (1);
	}
	else if (env->str_s[1] && env->str_s[1][0] == '\'')
	{
		*flags_c = 1;
		return (1);
	}
	return (0);
}

void		ft_echo(t_env *env)
{
	int		i;
	int		j;
	int		flags_d;
	int		flags_c;

	i = 1;
	j = 0;
	flags_d = 0;
	flags_c = 0;
	j += ft_verif_echo(env, &flags_d, &flags_c);
	while (env->str_s[i])
	{
		while (env->str_s[i][j])
		{
			(env->str_s[i][j] == '"' && flags_d) ? j++ : 0;
			(env->str_s[i][j] == '\'' && flags_c) ? j++ : 0;
			ft_putchar(env->str_s[i][j]);
			j++;
		}
		j = 0;
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
