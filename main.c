/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 15:23:19 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/23 19:34:47 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr("no environment variable named ");
	ft_putstr(var);
	write (1, "\n", 1);
	return (NULL);
}

void		call_check(char *buf, char **env)
{
	char	**call;
	int		i;

	if ((call = ft_strsplit(buf, ' ')) != NULL)
	{
		if (ft_strcmp(call[0], "cd") == 0)
			execute_cd(call, env);
	}
	if (call != NULL)
	{
		i = 0;
		while (call[i] != NULL)
		{
			free(call[i]);
			i++;
		}
		free(call);
	}
}

int			main(int ac, char **av, char **env)
{
	char	buf[BUFSIZE];
	char	dirname[BUFSIZE];
	int		n;

	while (21)
	{
		getcwd(dirname, BUFSIZE);
		ft_putstr(dirname);
		write(1, "$>", 2);
		n = read(1, buf, BUFSIZE);
		buf[n - 1] = 0;
		call_check(buf, env);
	}
	return (0);
}
