/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:54:34 by elbenkri          #+#    #+#             */
/*   Updated: 2018/04/22 16:39:53 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*g_pwd;

void		ft_verif_env(t_env *env)
{
	if (env->flags_env && ft_search_env(env, "PATH") != -1)
	{
		ft_free_env_tab(env->path);
		env->path = ft_strsplit(&env->env[ft_search_env(env, "PATH")][5], ':');
	}
	else if (env->flags_env && ft_search_env(env, "PATH") == -1)
	{
		ft_free_env_tab(env->path);
		env->path = (char**)malloc(sizeof(char*));
		env->path[0] = 0;
	}
}

void		ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		ft_printf(
		"{cyan}Sigabort42{eoc} {fd}1  {magenta}%s{eoc} {green}$>{eoc}", g_pwd);
	}
}

void		ft_prompt(t_env *env)
{
	free(g_pwd);
	if (env->flags_env && ft_search_env(env, "PWD") != -1)
	{
		if (!ft_strrchr(env->env[ft_search_env(env, "PWD")], '/'))
			g_pwd = ft_strdup(" ");
		else
			g_pwd = ft_strdup(ft_strrchr(env->env[ft_search_env(env, "PWD")],
			'/') + 1);
		ft_printf(
		"{cyan}Sigabort42{eoc} {fd}1  {magenta}%s{eoc} {green}$>{eoc}", g_pwd);
	}
	else
		ft_printf("{cyan}Sigabort42{eoc}%s{fd}1  {green}$>{eoc}",
		g_pwd = ft_strdup(" "));
}

void		ft_run(t_env *env)
{
	char	*trim;

	if (signal(SIGINT, ft_signal) == SIG_ERR)
		;
	g_pwd = ft_strdup(" ");
	while (42)
	{
		ft_prompt(env);
		if (get_next_line(0, &env->cmd) > 0)
		{
			env->str_s = ft_strsplit(trim = ft_strtrim(env->cmd), ' ');
			free(trim);
			if (env->str_s[0] && env->str_s[0][0] == '.')
			{
				ft_free_env_tab(env->str_s);
				free(env->cmd);
				continue;
			}
			if (ft_verif_all(env))
				continue;
		}
		else
			ft_exit(env);
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_env	env;

	(void)argv;
	if (argc < 1)
		exit(EXIT_FAILURE);
	env.flags_env = 0;
	if (envp[0])
		ft_init_env(envp, &env);
	else
	{
		env.path = (char**)malloc(sizeof(char*));
		env.path[0] = 0;
	}
	ft_init_builtin(&env);
	ft_run(&env);
	return (0);
}
