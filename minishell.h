/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:56:13 by elbenkri          #+#    #+#             */
/*   Updated: 2018/03/12 17:49:13 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include "./libft/libft.h"

typedef struct			s_env
{
	char				**env;
	char				**str_s;
	char				**path;
	char				*cmd;
	int				flags_env;
	struct s_builtin	*builtin;
}						t_env;

typedef struct			s_builtin
{
	char				*name;
	void				(*f)(t_env *);
}						t_builtin;

void					ft_chdir(t_env *env);
void					ft_env(t_env *env);
void					ft_setenv(t_env *env);
void					ft_exit(t_env *env);
void					ft_unsetenv(t_env *env);
void					ft_free_env_tab(char **env_tmp);
int					ft_search_env(t_env *env, char *av);
int					ft_verif_builtin(t_env *env);
int					ft_count_line_env(t_env *env);
char					*ft_split(char *str, char c);
char					**ft_copy_env(char **env, int i);

#endif
