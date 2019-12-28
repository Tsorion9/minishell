/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:13:33 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 21:26:38 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Вернуть пустое окружение
*/

char		**get_new_env(void)
{
	char	**env;

	env = (char**)malloc(sizeof(char*));
	*env = NULL;
	return (env);
}

/*
** Копировать окружение
*/

char		**copy_env(char **environ)
{
	char	**env;
	int		i;

	env = (char**)malloc(sizeof(char*) * (get_call_length(environ) + 1));
	i = 0;
	if (environ != NULL)
		while (environ[i] != NULL)
		{
			env[i] = ft_strdup(environ[i]);
			i++;
		}
	env[i] = NULL;
	return (env);
}

/*
** Печать всех переменных окружения
*/

void		print_env(char **env)
{
	if (env != NULL)
	{
		while (*env != NULL)
		{
			ft_putstr(*env);
			write(1, "\n", 1);
			env++;
		}
	}
}

/*
** Вернуть значение переменной окружения
*/

char		*give_val_env(char **env, char *var)
{
	int		i;
	char	*val;
	size_t	n;

	n = ft_strlen(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, n) == 0)
		{
			if (ft_strlen(env[i]) >= n)
				if (env[i][n] == '=')
				{
					val = ft_strdup(&(env[i][n + 1]));
					return (val);
				}
		}
		i++;
	}
	return (NULL);
}
