/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 15:23:19 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/25 20:05:31 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// возвращвет количество аргументов в вызове
int			get_call_length(char **call)
{
	int		i;

	i = 0;
	while (call[i] != NULL)
		i++;
	return (i);
}

// выполнение вызова pwd
void		execute_pwd(char **call)
{
	char	dirname[BUFSIZE];

	if (call[1] == NULL)
	{
		getcwd(dirname, BUFSIZE);
		ft_putstr(dirname);
	}
	else
		ft_putstr("pwd: too many arguments");
	write(1, "\n", 1);
}

void		execute_exit(char **call, char **env)
{
	if (*(call + 1) != NULL)
		if (*(call + 2) != NULL)
		{
			ft_putstr("exit: too many arguments\n");
			return ;
		}
	ft_freestrsplit(call);
	ft_freestrsplit(env);
	exit(0);
}

//  проверка и выполнение вызова
void		call_check(char *buf, char ***env)
{
	char	**call;

	if ((call = ft_strsplit(buf, ' ')) != NULL)
	{
		init_call(call, *env);
		if (ft_strcmp(call[0], "pwd") == 0)
			execute_pwd(call);
		else if (ft_strcmp(call[0], "echo") == 0)
			execute_echo(*env, call);
		else if (ft_strcmp(call[0], "cd") == 0)
			execute_cd(call, *env);
		else if (ft_strcmp(call[0], "setenv") == 0)
			execute_setenv(call, env);
		else if (ft_strcmp(call[0], "unsetenv") == 0)
			execute_unsetenv(call, env);
		else if (ft_strcmp(call[0], "exit") == 0)
			execute_exit(call, *env);
		else
			execute_bin(call, *env);
	}
	ft_freestrsplit(call);
}

int			main(int ac, char **av, char **environ)
{
	char	buf[BUFSIZE];
	int		n;
	char	**calls;
	char	**env;

	(void)ac;
	(void)av;
	env = copy_env(environ);
	while (21)
	{
		write(1, "$>", 2);
		n = read(1, buf, BUFSIZE);
		buf[n - 1] = 0;
		if ((calls = ft_strsplit(buf, ';')))
		{
			n = 0;
			while (calls[n] != NULL)
			{
				call_check(calls[n], &env);
				n++;
			}
		}
		ft_freestrsplit(calls);
	}
	return (0);
}
