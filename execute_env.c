/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:21:03 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/27 22:14:31 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// создать и вернуть вызов setenv
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
	return (call);
}

// запустить env без флагов или с флагом i
void		run_env_without_flags(char **call, char **env, char **new_env)
{
	char	**new_call;
	int		i;

	i = 1;
	while(call[i] != NULL)
	{
		if (call[i][0] != '-')
		{
			if (ft_strchr(call[i], '=') == NULL)
			{
				execute_bin(&(call[i]), env, new_env);
				return ;
			}
			else
			{
				new_call = create_call_setenv(call[i]);
				execute_setenv(new_call, &new_env);
				ft_freestrsplit(new_call);
			}
		}
		i++;
	}
}

// запустить env с флагом u
void		run_env_u(char **call, char **env, char ***new_env)
{
	if (find_var_env(call + 1, *new_env) == 1)
		delete_var_env(call + 1, new_env);
	if (call[3] == NULL)
		print_env(*new_env);
	else
		execute_bin(&(call[3]), env, *new_env);
}

// выполнить env
void		execute_env(char **call, char ***env)
{
	char	**new_env;
	char	**new_env_i;

	new_env = copy_env(*env);
	if (call[1] == NULL)
		print_env(*env);
	else if (call[1][0] != '-' || ft_strcmp(call[1], "-iu") == 0)
		run_env_without_flags(call, *env, new_env);
	else if (ft_strcmp(call[1], "-i") == 0)
	{
		new_env_i = (char**)malloc(sizeof(char*));
		*new_env_i = NULL;
		run_env_without_flags(call, *env, new_env_i);
	}
	else if (ft_strcmp(call[1], "-u") == 0)
		run_env_u(call, *env, &new_env);
	ft_freestrsplit(new_env);
}
