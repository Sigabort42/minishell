#include "minishell.h"

char		**ft_copy_env(char **env, int i)
{
	char    **env_tmp;

	env_tmp = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (env[++i])
		env_tmp[i] = ft_strdup(env[i]);
	env_tmp[i] = 0;
	return (env_tmp);
}


static void	ft_add_elem_env(t_env *env, int i, char **env_tmp)
{
	env->env = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while (env_tmp && env_tmp[i])
	{
		env->env[i] = ft_strdup(env_tmp[i]);
		i++;
	}
	env->env[i] = ft_strjoin(env->str_s[1], "=");
	env->env[i] = ft_strjoin_free(env->env[i], ft_strdup(env->str_s[2]));
	env->env[++i] = 0;
	if (!env->flags_env)
		env->flags_env = 1;
}

void		ft_setenv(t_env *env)
{
	int     i;
	char    **env_tmp;

	if (env->flags_env && env->str_s[2])
	{
		if ((i = ft_search_env(env, env->str_s[1])) != -1)
		{
			free(env->env[i]);
			env->env[i] = ft_strjoin(env->str_s[1], "=");
			env->env[i] = ft_strjoin_free(env->env[i],
			ft_strdup(env->str_s[2]));
		}
		else
		{
			i = ft_count_line_env(env);
			env_tmp = ft_copy_env(env->env, i);
			ft_free_env_tab(env->env);
			ft_add_elem_env(env, i, env_tmp);
			ft_free_env_tab(env_tmp);
		}
	}
	else if (!env->flags_env)
		ft_add_elem_env(env, 0, 0);
	env->builtin[1].f(env);
}

static void	ft_delete_elem_env(t_env *env, int i, char **env_tmp)
{
	int	j;

	j = 0;
	if (env->str_s[1])
	{
		env->env = (char**)malloc(sizeof(char*) * i);
		i = 0;
		while (env_tmp[i])
		{
			if (ft_strncmp(env_tmp[i], env->str_s[1], ft_strlen(env->str_s[1])))
				env->env[j++] = ft_strdup(env_tmp[i++]);
			else
				i++;
		}
		env->env[j] = 0;
	}
}

void		ft_unsetenv(t_env *env)
{
	int     i;
	char    **env_tmp;

	if ((i = ft_search_env(env, env->str_s[1])) != -1)
	{
		i = ft_count_line_env(env);
		env_tmp = ft_copy_env(env->env, i);
	 	ft_free_env_tab(env->env);
		ft_delete_elem_env(env, i, env_tmp);
		ft_free_env_tab(env_tmp);
	}
	env->builtin[1].f(env);
}
