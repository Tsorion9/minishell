/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_sup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:10:32 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 21:18:41 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			env_flags_sup(char ***new_env, char **call, int i)
{
	char	**new_call;

	if (call[i + 1] != NULL)
	{
		new_call = create_call_unsetenv(call[i + 1]);
		execute_unsetenv(new_call, new_env);
		ft_freestrsplit(new_call);
		i++;
		if (call[i + 1] != NULL)
			if (ft_strcmp(call[i + 1], "-i") != 0 && \
				ft_strcmp(call[i + 1], "-u") != 0 && \
				ft_strchr(call[i + 1], '=') == NULL)
				return (i + 2);
	}
	return (i);
}

int			env_flags_sup1(char ***new_env, char **call, int i)
{
	char	**new_call;

	ft_freestrsplit(*new_env);
	*new_env = get_new_env();
	if (call[i + 1] != NULL)
	{
		if (ft_strchr(call[i + 1], '=') != NULL)
		{
			new_call = create_call_setenv(call[i + 1]);
			execute_setenv(new_call, new_env);
			ft_freestrsplit(new_call);
			i++;
		}
		else
			return (i + 2);
	}
	return (i);
}

void		env_flags_sup2(char ***new_env, char **call, int i)
{
	char	**new_call;

	new_call = create_call_setenv(call[i]);
	execute_setenv(new_call, new_env);
	ft_freestrsplit(new_call);
}

int			env_flags_sup3(char ***new_env, char **call, int i)
{
	int	z;

	if (call[i] != NULL && ft_strchr(call[i], '=') != NULL)
		env_flags_sup2(new_env, call, i);
	else if (ft_strcmp(call[i], "-u") == 0)
	{
		z = env_flags_sup(new_env, call, i);
		if (i + 3 == z)
			return (i + 3);
		i = z;
	}
	else if (ft_strcmp(call[i], "-i") == 0)
	{
		z = env_flags_sup1(new_env, call, i);
		if (i + 3 == z)
			return (i + 3);
		i = z;
	}
	else
		return (-1);
	return (i);
}
