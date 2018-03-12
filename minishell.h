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
	struct s_builtin	*builtin;
}						t_env;

typedef struct			s_builtin
{
	char				*name;
	void				(*f)(char **, t_env *, int);
}						t_builtin;

void					ft_chdir(char **str_s, t_env *env, int verif_env);
void					ft_env(char **str_s, t_env *env, int verif_env);
void					ft_setenv(char **str_s, t_env *env, int verif_env);
void					ft_exit(char **str_s, t_env *env, int verif_env);

#endif
