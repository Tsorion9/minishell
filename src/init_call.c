/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:06:11 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/02 10:07:23 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_call_sup(char **call, char **env, int i)
{
	char	*temp;
	char	*temp1;
	int		len;

	len = 0;
	if (call[i][0] == '$' && ft_strchr(call[i], '/') != NULL)
	{
		while (call[i][len] != '/')
			len++;
		temp1 = ft_strdup(&(call[i][len]));
		call[i][len] = 0;
		temp = give_val_env(env, &(call[i][1]));
		free(call[i]);
		if ((call[i] = ft_strjoin(temp, temp1)) == NULL)
			call[i] = ft_strdup(temp1);
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
}

void		init_call_sup1(char **call, char **env, int i)
{
	char	*temp;
	char	*temp1;
	int		len;

	len = 0;
	if (call[i][0] == '~' && ft_strchr(call[i], '/') != NULL)
	{
		while (call[i][len] != '/')
			len++;
		temp1 = ft_strdup(&(call[i][len]));
		call[i][len] = 0;
		temp = give_val_env(env, "HOME");
		free(call[i]);
		if ((call[i] = ft_strjoin(temp, temp1)) == NULL)
			call[i] = ft_strdup(temp1);
		free(temp);
		free(temp1);
	}
}

char		*remove_equal_sig_sup(char *new_call, char *call)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (call[i] != 0)
	{
		if (call[i] != 34)
		{
			new_call[n] = call[i];
			n++;
		}
		i++;
	}
	new_call[n] = 0;
	free(call);
	return (new_call);
}

char		*remove_equal_sig(char *call)
{
	int		i;
	int		n;
	char	*new_call;

	i = 0;
	n = 0;
	while (call[i] != 0)
	{
		if (call[i] == 34)
			n++;
		i++;
	}
	new_call = (char*)malloc(i - n + 1);
	return (remove_equal_sig_sup(new_call, call));
}

/*
** Заменить '$' и '~' на соответствующие значения из окружения
** и убрать все знаки '"'
*/

void		init_call(char **call, char **env)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	while (call[i] != NULL)
	{
		call[i] = remove_equal_sig(call[i]);
		len = 0;
		init_call_sup(call, env, i);
		init_call_sup1(call, env, i);
		if (call[i][0] == '~' && ft_strchr(call[i], '/') == NULL)
		{
			temp = give_val_env(env, "HOME");
			free(call[i]);
			call[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
