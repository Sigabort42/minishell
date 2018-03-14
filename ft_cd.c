/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:51:10 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/14 18:00:07 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd2(t_env *env)
{
	char	*path_no_env;
	char	*old_pwd;

	path_no_env = ft_strnew(100);
	if (env->flags_env && ft_search_env(env, "PWD") != -1)
		old_pwd = ft_strdup(&(env)->env[ft_search_env(env, "PWD")][4]);
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

void		ft_cd(t_env *env)
{
	char	*verif;
	char	*relative;

	if (env->flags_env)
	{
		if ((!env->str_s[1] || !ft_strcmp(env->str_s[1], "--") ||
		!ft_strcmp(env->str_s[1], "~")) && ft_search_env(env, "HOME") != -1)
			chdir(&(env)->env[ft_search_env(env, "HOME")][5]);
		else if (env->str_s[1] && !ft_strcmp(env->str_s[1], "-"))
		{
			while (chdir(&(env)->env[ft_search_env(env, "OLDPWD")][7]) == -1)
			{
				verif = ft_strrchr(verif, '/');
				verif[0] = 0;
	 		}
 		}
		else if (env->str_s[1][0] == '~' && ft_search_env(env, "HOME") != -1)
		{
			relative = ft_strdup(ft_strrchr(env->str_s[1], '/'));
			free(env->str_s[1]);
			env->str_s[1] = ft_strdup(&env->env[ft_search_env(env, "HOME")][5]);
			env->str_s[1] = ft_strjoin_free(env->str_s[1], relative);
			chdir(env->str_s[1]);
		}
		else if (!chdir(env->str_s[1]))
			chdir(env->str_s[1]);
	}
	ft_cd2(env);
}
