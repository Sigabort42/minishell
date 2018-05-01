/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:51:10 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/01 22:58:42 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			ft_exec_cd(char *path)
{
	struct stat	s;

	if (chdir(path) == -1)
	{
		if (stat(path, 0) && access(path, F_OK))
			ft_printf("cd: {fd}2 no such file or directory: {red}%s{eoc}\n",
			path);
		else if (!stat(path, &s) && !S_ISDIR(s.st_mode))
			ft_printf("cd: {fd}2 not a directory: {red}%s{eoc}\n", path);
		else if (access(path, X_OK))
			ft_printf("cd: {fd}2 permission denied: {red}%s{eoc}\n", path);
	}
}

static void			ft_relative_or_absolute(t_env *env)
{
	char		*relative;

	if (env->str_s[1][0] == '~' && ft_search_env(env, "HOME") != -1)
	{
		relative = ft_strdup(ft_strrchr(env->str_s[1], '/'));
		free(env->str_s[1]);
		env->str_s[1] = ft_strdup(&env->env[ft_search_env(env, "HOME")][5]);
		env->str_s[1] = ft_strjoin_free(env->str_s[1], relative);
		ft_exec_cd(env->str_s[1]);
	}
	else
		ft_exec_cd(env->str_s[1]);
}

static void			ft_cd3(t_env *env, char *path_no_env, char *old_pwd)
{
	ft_free_env_tab(env->str_s);
	env->str_s = (char **)malloc(sizeof(char*) * 4);
	env->str_s[0] = ft_strdup("cd");
	env->str_s[1] = ft_strdup("PWD");
	env->str_s[2] = ft_strdup(path_no_env);
	env->str_s[3] = 0;
	ft_setenv(env);
	free(old_pwd);
	free(path_no_env);
}

void				ft_cd2(t_env *env)
{
	char		*path_no_env;
	char		*old_pwd;

	path_no_env = ft_strnew(100);
	if (env->flags_env && ft_search_env(env, "PWD") != -1)
		old_pwd = ft_strdup(&(env)->env[ft_search_env(env, "PWD")][4]);
	else if (ft_search_env(env, "PWD") == -1)
		old_pwd = ft_strdup("/");
	if (!env->flags_env)
	{
		getcwd(path_no_env, 100);
		chdir(path_no_env);
		old_pwd = ft_strdup(path_no_env);
		env->env = (char **)malloc(sizeof(char*) * 3);
	}
	getcwd(path_no_env, 100);
	ft_free_env_tab(env->str_s);
	env->str_s = (char **)malloc(sizeof(char*) * 4);
	env->str_s[0] = ft_strdup("cd");
	env->str_s[1] = ft_strdup("OLDPWD");
	env->str_s[2] = ft_strdup(old_pwd);
	env->str_s[3] = 0;
	ft_setenv(env);
	ft_cd3(env, path_no_env, old_pwd);
}

void				ft_cd(t_env *env)
{
	char		*verif;
	char		*verif2;

	if (env->flags_env && ft_search_env(env, "HOME") != -1)
	{
		if ((!env->str_s[1] || !ft_strcmp(env->str_s[1], "--") ||
		!ft_strcmp(env->str_s[1], "~")) && ft_search_env(env, "HOME") != -1)
			ft_exec_cd(&(env)->env[ft_search_env(env, "HOME")][5]);
		else if (env->str_s[1] && !ft_strcmp(env->str_s[1], "-") &&
		ft_search_env(env, "OLDPWD") != -1)
		{
			verif = &env->env[ft_search_env(env, "OLDPWD")][7];
			while (chdir(verif) == -1)
			{
				if (!ft_strrchr(verif, '/'))
					break ;
				verif2 = ft_strrchr(verif, '/');
				verif2[0] = 0;
			}
			ft_putendl(verif);
		}
		else
			ft_relative_or_absolute(env);
	}
	ft_cd_not_env(env);
}
