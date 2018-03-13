/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:54:34 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/12 18:02:45 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void            ft_chdir(t_env *env)
{
	(void)env;
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

void		ft_init_env(char **envp, t_env *env)
{
	int		i;
	
	i = 0;
	env->flags_env = 1;
	while (envp[i])
		i++;
	env->env = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (envp[++i])
		env->env[i] = ft_strdup(envp[i]);
	env->env[i] = 0;
	env->path = ft_strsplit(&envp[ft_search_env(env, "PATH")][5], ':');
}

void		ft_init_builtin(t_env *env)
{
	env->builtin = (t_builtin*)malloc(sizeof(t_builtin) * 6);
	env->builtin[0].name = ft_strdup("cd");
	env->builtin[0].f = &ft_chdir;
	env->builtin[1].name = ft_strdup("env");
	env->builtin[1].f = &ft_env;
	env->builtin[2].name = ft_strdup("setenv");
	env->builtin[2].f = &ft_setenv;
	env->builtin[3].name = ft_strdup("exit");
	env->builtin[3].f = &ft_exit;
	env->builtin[4].name = ft_strdup("unsetenv");
	env->builtin[4].f = &ft_unsetenv;
	env->builtin[5].name = 0;
}

void		ft_run(t_env *env)
{
	while (42)
	{
		if (env->flags_env)
			ft_printf("{cyan}Sigabort42{eoc} {magenta}%s{eoc} {green}$>{eoc}",
			ft_strrchr(env->env[ft_search_env(env, "PWD")], '/') + 1);
		else
			ft_printf("{cyan}Sigabort42{eoc}%c{green}$>{eoc}", ' ');
		if (get_next_line(0, &env->cmd) > 0)
		{
			env->str_s = ft_strsplit(env->cmd, ' ');
			if (ft_verif_builtin(env))
				continue;
		}
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
	ft_init_builtin(&env);
	ft_run(&env);
	return (0);
}
