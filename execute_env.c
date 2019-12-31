/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:21:03 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 21:16:33 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Создать и вернуть вызов setenv
*/

char		**create_call_setenv(char *val_env)
{
	char	**call;
	int		i;

	call = (char**)malloc(sizeof(char*) * 5);
	call[0] = ft_strdup("setenv");
	i = 0;
	while (val_env[i] != '=')
		i++;
	call[1] = (char*)malloc(ft_strlen(val_env) + 1);
	call[1] = ft_memcpy(call[1], val_env, i);
	call[1][i] = 0;
	call[2] = ft_strdup(val_env + i + 1);
	call[3] = (char*)ft_memalloc(2);
	call[3][0] = '0';
	call[4] = NULL;
	return (call);
}

/*
** Создать и вернуть вызов unsetenv
*/

char		**create_call_unsetenv(char *val_env)
{
	char	**call;

	call = (char**)malloc(sizeof(char*) * 3);
	call[0] = ft_strdup("unsetenv");
	call[1] = ft_strdup(val_env);
	call[2] = NULL;
	return (call);
}

/*
** Добавляет переменные в new_env и возвращает
** индекс исполняемого файла
*/

int			add_env(char ***new_env, char **call)
{
	int		i;
	char	**new_call;

	i = 0;
	while (call[i] != NULL && ft_strchr(call[i], '=') != NULL)
	{
		new_call = create_call_setenv(call[i]);
		execute_setenv(new_call, new_env);
		ft_freestrsplit(new_call);
		i++;
	}
	if (call[i] == NULL)
		return (0);
	return (i + 1);
}

int			env_flags(char ***new_env, char **call)
{
	int		i;
	int		z;

	i = 0;
	while (call[i] != NULL)
	{
		if ((z = env_flags_sup3(new_env, call, i)) == -1)
			break ;
		if (i + 3 == z)
			return (z);
		i = z;
		if (call[i] == NULL)
			return (i);
		i++;
	}
	if (call[i] == NULL)
		return (0);
	return (i + 1);
}

/*
** Проверка и выполнение команды env
*/

void		execute_env(char **call, char ***env)
{
	char	**new_env;
	int		i;

	new_env = copy_env(*env);
	i = 0;
	if (call[1] == NULL)
		print_env(new_env);
	else if (call[1][0] != '-')
		i = add_env(&new_env, call + 1);
	else
		i = env_flags(&new_env, call + 1);
	if (i == 0)
		print_env(new_env);
	else
		execute_bin(call + i, *env, new_env);
	ft_freestrsplit(new_env);
}
