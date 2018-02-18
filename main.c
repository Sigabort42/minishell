#include "minishell.h"

void			ft_setenv(char **str_s, char **env)
{
	int		i;
	char		**str;

	i = 0;
	str = ft_strsplit(env[i], '=');
	while (ft_strcmp(str_s[1], str[0]))
		str = ft_strsplit(env[++i], '=');
	ft_strcpy(env[i], str[0]);
	ft_strcat(env[i], "=");
	ft_strcat(env[i], str_s[2]);
}

void			ft_env(char **str_s, char **env)
{
	int		i;
	(void)str_s;

	if (!env[0])
		return ;
	i = 0;
	while (env[i])
		ft_putendl(env[i++]);
}

void			ft_chdir(char **str_s, char **env)
{
	char		*tmp;
	char		*tmp_old;

	tmp = 0;
	tmp_old = 0;
	if ((!str_s[1] || !ft_strcmp(str_s[1], "--")) && env[0])
	{
		tmp_old = &env[7][4];
		tmp = ft_strdup(&env[14][5]);
		chdir(&env[14][5]);
	}
	else if (str_s[1] && !ft_strcmp(str_s[1], "-") && env[0])
	{
		tmp_old = &env[7][4];
		tmp = ft_strdup(&env[22][7]);
		chdir(&env[22][7]);
	}
	else
	{
		tmp_old = &env[7][4];
		tmp = ft_strdup(str_s[1]);
		chdir(str_s[1]);
	}
	str_s[1] = "OLDPWD";
	str_s[2] = tmp_old;
	ft_setenv(str_s, env);
	str_s[1] = "PWD";
	str_s[2] = tmp;
	ft_setenv(str_s, env);
	free(tmp);
}

t_builtin		*ft_init_build()
{
	t_builtin	*builtin;

	builtin = (t_builtin*)malloc(sizeof(t_builtin) * 4);
	builtin[0].name = ft_strdup("cd");
	builtin[0].f = &ft_chdir;
	builtin[1].name = ft_strdup("env");
	builtin[1].f = &ft_env;
	builtin[2].name = ft_strdup("setenv");
	builtin[2].f = &ft_setenv;
	builtin[3].name = 0;
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

	build = ft_init_build();
	if (argc < 2)
		(void)argv;
	if (env[0])
		path = ft_strsplit(env[11], ':');
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
			while (build[i].name && ft_strcmp(build[i].name, str_s[0]))
				i++;
			if (build[i].name)
			{
				build[i].f(str_s, env);
				continue;
			}
			i = 0;
			cmd = ft_strjoin(&path[i][4], "/");
			cmd = ft_strjoin_free(cmd, ft_strdup(str_s[0]));
			while (path[i] && (access(cmd, F_OK) == -1))
			{
				free(cmd);
				cmd = ft_strjoin(&path[++i][0], "/");
				cmd = ft_strjoin_free(cmd, ft_strdup(str_s[0]));
			}
			if (!access(cmd, F_OK))
				ouloulou = fork();
			else
				ft_printf("minishell:{fd}2  command not found: {red}%s{eoc}\n", str_s[0]);
			if (ouloulou > 0)
			{
				wait(0);
				free(cmd);
				i = 0;
				while (str_s[i])
					free(str_s[i++]);
			}
			else
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
