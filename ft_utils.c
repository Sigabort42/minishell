/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:51:31 by elbenkri          #+#    #+#             */
/*   Updated: 2018/04/22 16:39:40 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_count_line_env(t_env *env)
{
	int			i;

	i = 0;
	while (env->env[i])
		i++;
	return (i);
}

void			ft_free_env_tab(char **env_tmp)
{
	int			i;

	i = 0;
	while (env_tmp[i])
		free(env_tmp[i++]);
	free(env_tmp);
}

int				ft_search_env(t_env *env, char *av)
{
	int			i;
	char		*env_tmp;

	if (!env->flags_env || !env->env[0])
		return (-1);
	i = 1;
	env_tmp = ft_split(env->env[0], '=');
	while (env->env[i] && ft_strcmp(env_tmp, av))
	{
		free(env_tmp);
		env_tmp = ft_split(env->env[i], '=');
		i++;
	}
	if (!ft_strcmp(env_tmp, av))
	{
		free(env_tmp);
		return (i - 1);
	}
	free(env_tmp);
	if (env->env[i])
		return (i);
	return (-1);
}

int				ft_verif_builtin(t_env *env)
{
	int			i;

	i = 0;
	free(env->cmd);
	while (env->str_s[0] && env->builtin[i].name &&
		ft_strcmp(env->builtin[i].name, env->str_s[0]))
		i++;
	if (!env->str_s[0])
	{
		ft_free_env_tab(env->str_s);
		return (1);
	}
	if (env->builtin[i].name && env->str_s[0])
	{
		env->builtin[i].f(env);
		ft_free_env_tab(env->str_s);
		return (1);
	}
	return (0);
}

int				ft_verif_all(t_env *env)
{
	ft_verif_env(env);
	if (ft_verif_builtin(env))
		return (1);
	ft_search_cmd(env);
	return (0);
}
