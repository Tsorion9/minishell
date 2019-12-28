/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:13:33 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 17:41:28 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_new_env(void)
{
	char	**env;

	env = (char**)malloc(sizeof(char*));
	*env = NULL;
	return (env);
}

// копировать окружение
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

// печать всех переменных окружения
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

// вернуть значение переменной окружения
char		*give_val_env(char **env, char *var)
{
	int		i;
	char	*val;
	int		n;

	n = ft_strlen(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, n) == 0)
		{
			val = ft_strdup(&(env[i][n + 1]));
			return (val);
		}
		i++;
	}
	return (NULL);
}

// Заменить '$' и '~' на соответствующие значения из окружения
void		init_call(char **call, char **env)
{
	char	*temp;
	char	*temp1;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (call[i] != NULL)
	{
		if (call[i][0] == '$' && ft_strchr(call[i], '/'))
		{
			while (call[i][len] != '/')
				len++;
			temp1 = ft_strdup(&(call[i][len]));
			call[i][len] = 0;
			temp = give_val_env(env, &(call[i][1]));
			free(call[i]);
			call[i] = ft_strjoin(temp, temp1);
			free(temp);
			free(temp1);
		}
		else if (call[i][0] == '$' && ft_strchr(call[i], '/') == NULL)
		{
			temp = give_val_env(env, &(call[i][1]));
			free(call[i]);
			call[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
