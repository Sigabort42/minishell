/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 02:07:09 by elbenkri          #+#    #+#             */
/*   Updated: 2018/04/22 14:57:41 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_init_env(char **envp, t_env *env)
{
	int		i;
	char	buf[100];

	i = 0;
	env->flags_env = 1;
	while (envp[i])
		i++;
	env->env = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	getcwd(buf, 100);
	ft_strcat(buf, "/minishell");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHELL", 5))
		{
			env->env[i] = ft_strdup("SHELL=");
			env->env[i] = ft_strjoin_free(env->env[i], ft_strdup(buf));
			i++;
		}
		env->env[i] = ft_strdup(envp[i]);
	}
	env->env[i] = 0;
	env->path = ft_strsplit(&envp[ft_search_env(env, "PATH")][5], ':');
}

void		ft_init_builtin(t_env *env)
{
	env->builtin = (t_builtin*)malloc(sizeof(t_builtin) * 7);
	env->builtin[0].name = ft_strdup("cd");
	env->builtin[0].f = &ft_cd;
	env->builtin[1].name = ft_strdup("env");
	env->builtin[1].f = &ft_env;
	env->builtin[2].name = ft_strdup("setenv");
	env->builtin[2].f = &ft_setenv;
	env->builtin[3].name = ft_strdup("exit");
	env->builtin[3].f = &ft_exit;
	env->builtin[4].name = ft_strdup("unsetenv");
	env->builtin[4].f = &ft_unsetenv;
	env->builtin[5].name = ft_strdup("echo");
	env->builtin[5].f = &ft_echo;
	env->builtin[6].name = 0;
}

void		ft_free_2(t_env *env)
{
	free(env->cmd);
	ft_free_env_tab(env->str_s);
}

int			ft_exec_cmd(t_env *env)
{
	pid_t	pid;

	if (!access(env->cmd, X_OK))
		pid = fork();
	else
	{
		ft_printf("minishell:{fd}2  command not found: {red}%s{eoc}\n",
		env->str_s[0]);
		ft_free_2(env);
		return (1);
	}
	if (pid > 0)
	{
		wait(0);
		ft_free_2(env);
	}
	else if (!pid)
	{
		if (!env->flags_env)
			execve(env->str_s[0], env->str_s, env->env);
		else
			execve(env->cmd, env->str_s, env->env);
	}
	return (0);
}

void		ft_search_cmd(t_env *env)
{
	int		i;

	i = 0;
	if (env->flags_env)
	{
		env->cmd = ft_strjoin(env->path[i], "/");
		env->cmd = ft_strjoin_free(env->cmd, ft_strdup(env->str_s[0]));
	}
	else
	{
		env->env = 0;
		env->cmd = ft_strdup(env->str_s[0]);
	}
	while (env->flags_env && env->path[i] && (access(env->cmd, F_OK) == -1))
	{
		free(env->cmd);
		env->cmd = ft_strjoin(env->path[++i], "/");
		env->cmd = ft_strjoin_free(env->cmd, ft_strdup(env->str_s[0]));
	}
	ft_exec_cmd(env);
}
