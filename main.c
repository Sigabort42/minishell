#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	int	i;
	char	*cmd;
	pid_t	ouloulou;
	char	**str_s;
	char	**path;

	if (argc < 2)
		(void)argv;
	if (env[0])
		path = ft_strsplit(env[11], ':');
	while (42)
	{
		write(1, "Sigabort42 $>", 13);
		if (get_next_line(0, &cmd) > 0)
		{
			i = 0;
			str_s = ft_strsplit(cmd, ' ');
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
				ft_printf("{red}%s{eoc}:{fd}2  command not found\n", str_s[0]);
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
