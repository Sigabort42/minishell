#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include "./libft/libft.h"

typedef struct	s_builtin
{
	char	*name;
	void	(*f)(char **, char **, int);
}		t_builtin;

void	ft_chdir(char **str_s, char **env, int verif_env);
void	ft_env(char **str_s, char **env, int verif_env);
void	ft_setenv(char **str_s, char **env, int verif_env);
void	ft_exit(char **str_s, char **env, int verif_env);

#endif
