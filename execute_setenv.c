/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 14:04:16 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/25 19:47:24 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// заменить переменную окружения
int			replace_env_var(char **call, char **env)
{
	char	*temp;
	char	*temp1;
	int		len;

	while (*env != NULL)
	{
		len = 0;
		while ((*env)[len] != '=' && (*env)[len])
			len++;
		if (ft_strncmp(call[1], *env, len) == 0)
		{
			free(*env);
			temp = ft_strjoin(call[1], "=");
			temp1 = ft_strjoin(temp, call[2]);
			*env = temp1;
			free(temp);
			return (1);
		}
		env++;
	}
	return (0);
}

// добавить переменную окружения
void		add_env_var(char **call, char ***envi)
{
	char	*temp;
	char	*temp1;
	char	**c_env;
	int		i;
	char	**env;

	c_env = *envi;
	env = (char**)malloc(sizeof(char*) * (get_call_length(c_env) + 2));
	i = 0;
	while (c_env[i] != NULL)
	{
		env[i] = ft_strdup(c_env[i]);
		i++;
	}
	ft_freestrsplit(*envi);
	temp = ft_strjoin(call[1], "=");
	temp1 = ft_strjoin(temp, call[2]);
	free(temp);
	env[i] = temp1;
	env[i + 1] = NULL;
	*envi = env;
}

// добавить или заменить переменуую окружения
void		add_rep_env_var(char **call, char ***env)
{
	if (call[3] != NULL)
		if (call[3][0] == '0' && call[3][1] == 0 &&\
			replace_env_var(call, *env) == 1)
				return ;
	add_env_var(call, env);
}

// проверка и выполнение setenv
void		execute_setenv(char **call, char ***env)
{
	int		call_len;

	if (call[1] == NULL)
	{
		print_env(*env);
		return ;
	}
	call_len = get_call_length(call);
	if (call_len > 4 || call_len == 2)
	{
		ft_putstr("setenv: usage: setenv [arg1] [arg2] [option]\n");
		return ;
	}
	add_rep_env_var(call, env);
}
