/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:05:25 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 21:11:43 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Проверка на нахождение переменной окружения
*/

int			find_var_env(char **call, char **env)
{
	int		len;

	while (*env != NULL)
	{
		len = 0;
		while ((*env)[len] != '=' && (*env)[len])
			len++;
		if (ft_strncmp(call[1], *env, len) == 0)
			return (1);
		env++;
	}
	return (0);
}

/*
** Удалить переменную окружения
*/

void		delete_var_env(char **call, char ***envi)
{
	char	**c_env;
	char	**env;
	char	**h_env;
	int		len;

	c_env = *envi;
	env = (char**)malloc(sizeof(char*) * (get_call_length(c_env)));
	h_env = env;
	while (*c_env != NULL)
	{
		len = 0;
		while ((*c_env)[len] != '=' && (*c_env)[len])
			len++;
		if (ft_strncmp(call[1], *c_env, len) != 0)
		{
			*env = ft_strdup(*c_env);
			env++;
		}
		c_env++;
	}
	ft_freestrsplit(*envi);
	*env = NULL;
	*envi = h_env;
}

/*
** Проверить и выполнить команду unsetenv
*/

void		execute_unsetenv(char **call, char ***env)
{
	if (get_call_length(call) > 2)
	{
		ft_putstr("unsetenv: usage: unsetenv [arg]\n");
		return ;
	}
	if (find_var_env(call, *env) == 1)
		delete_var_env(call, env);
}
