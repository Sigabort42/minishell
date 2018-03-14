/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:41:28 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/12 15:51:10 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_exit(char **str_s, char **env, int verif_env)
{
	(void)str_s;
	(void)env;
	(void)verif_env;
	exit(EXIT_SUCCESS);
}

void			ft_setenv(char **str_s, char **env, int verif_env)
{
	int		i;
	char		**str;

	i = 0;
	if (env[0] && verif_env)
	{
		str = ft_strsplit(env[i], '=');
		while (env[i] && ft_strcmp(str_s[1], str[0]))
			str = ft_strsplit(env[++i], '=');
		ft_strcpy(env[i], str[0]);
		ft_strcat(env[i], "=");
		ft_strcat(env[i], str_s[2]);
	}
	else
	{
		(!ft_strcmp(str_s[1], "PWD")) ? i++ : 0;
		env[i] = ft_strdup(str_s[1]);
		env[i] = ft_strjoin_free(env[i], ft_strdup("="));
		env[i] = ft_strjoin_free(env[i], ft_strdup(str_s[2]));
	}
}

void			ft_env(char **str_s, char **env, int verif_env)
{
	int		i;

	(void)str_s;
	(void)verif_env;
	if (!env[0])
		return ;
	i = 0;
	while (env[i])
		ft_putendl(env[i++]);
}

void			ft_chdir(char **str_s, char **env, int verif_env)
{
	char		*tmp;
	char		*tmp_old;
	char		*relative;
	char		*verif;
	char		*verif2;

	(void)verif_env;
	tmp = ft_strnew(100);
	verif2 = ft_strnew(100);
	tmp_old = (env[0]) ? ft_strdup(&env[7][4]) : 0;
	if ((!str_s[1] || !ft_strcmp(str_s[1], "--") || !ft_strcmp(str_s[1], "~")) && env[0])
	{
		chdir(&env[15][5]);
			
	}
	else if (str_s[1] && !ft_strcmp(str_s[1], "-") && env[0])
	{
		verif = ft_strdup(&env[23][7]);
		while (chdir(verif) == -1)
		{
			verif2 = ft_strrchr(verif, '/');
			verif2[0] = 0;
		}
	}
	else if (env[0])
	{
		if (str_s[1][0] == '~')
 		{
			relative = ft_strdup(ft_strrchr(str_s[1], '/'));
			str_s[1] = ft_strdup(&env[15][5]);
			str_s[1] = ft_strjoin_free(str_s[1], relative);
		}
		getcwd(tmp, 100);
		if (!chdir(str_s[1]) && !getcwd(verif2, 100))
			chdir(str_s[1]);
	}
	else
	{
		getcwd(tmp, 100);
		chdir(tmp);
		tmp_old = ft_strdup(tmp);
		env = (char **)malloc(sizeof(char*) * 2);
	}
	getcwd(tmp, 100);
	str_s[1] = "OLDPWD";
	str_s[2] = tmp_old;
	ft_setenv(str_s, env, verif_env);
	str_s[1] = "PWD";
	str_s[2] = tmp;
	ft_setenv(str_s, env, verif_env);
	free(tmp);
	free(tmp_old);
}

t_builtin		*ft_init_build()
{
	t_builtin	*builtin;

	builtin = (t_builtin*)malloc(sizeof(t_builtin) * 5);
	builtin[0].name = ft_strdup("cd");
	builtin[0].f = &ft_chdir;
	builtin[1].name = ft_strdup("env");
	builtin[1].f = &ft_env;
	builtin[2].name = ft_strdup("setenv");
	builtin[2].f = &ft_setenv;
	builtin[3].name = ft_strdup("exit");
	builtin[3].f = &ft_exit;
	builtin[4].name = 0;
	return (builtin);
}

int			main(int argc, char **argv, char **env)
{
	int		i;
	char		*cmd;
	pid_t		ouloulou;
	char		**str_s;
	char		**path;
	t_builtin	*build;
	int		verif_env;
	char		*pwd_shell;

	pwd_shell = ft_strnew(80);
	build = ft_init_build();
	ouloulou = -1;
	verif_env = 0;
	if (argc < 2)
		(void)argv;
	if (env[0])
	{
		str_s = (char**)malloc(sizeof(char*) * 3);
		verif_env = 1;
/*		getcwd(pwd_shell, 80);
		ft_strcat(pwd_shell, "/");
		ft_strcat(pwd_shell, "minishell");
		ft_strcpy(env[8], "SHELL=");
		ft_strcat(env[8], pwd_shell);
*/		path = ft_strsplit(env[11], ':');
	}
	while (42)
	{
		if (env[0])
			ft_printf("{cyan}Sigabort42{eoc} {magenta}%s{eoc} {green}$>{eoc}", ft_strrchr(env[7], '/') + 1);
		else
			ft_printf("{cyan}Sigabort42{eoc}%c{green}$>{eoc}", ' ');
		if (get_next_line(0, &cmd) > 0)
		{
			i = 0;
			str_s = ft_strsplit(cmd, ' ');
			while (str_s[0] && build[i].name && ft_strcmp(build[i].name, str_s[0]))
				i++;
			if (!str_s[0])
				continue;
			if (build[i].name && str_s[0])
			{
				build[i].f(str_s, env, verif_env);
				continue;
			}
			i = 0;
			if (env[0])
			{
				cmd = ft_strjoin(&path[i][4], "/");
				cmd = ft_strjoin_free(cmd, ft_strdup(str_s[0]));
			}
			else
				cmd = ft_strdup(str_s[0]);
			while (env[0] && path[i] && (access(cmd, F_OK) == -1))
			{
				free(cmd);
				cmd = ft_strjoin(&path[++i][0], "/");
				cmd = ft_strjoin_free(cmd, ft_strdup(str_s[0]));
			}
			if (!access(cmd, F_OK))
				ouloulou = fork();
			else
			{
				ft_printf("minishell:{fd}2  command not found: {red}%s{eoc}\n", str_s[0]);
				continue;
			}
			if (ouloulou > 0)
			{
				wait(0);
				free(cmd);
				i = 0;
				while (str_s[i])
					free(str_s[i++]);
			}
			else if (ouloulou == 0)
			{
				if (!env[0])
					execve(str_s[0], str_s, env);
				else
					execve(cmd, str_s, env);
			}
			ouloulou = -1;
		}
	}
	return (0);
}
