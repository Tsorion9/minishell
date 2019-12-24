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

void		execute_pwd(void)
{
	char	dirname[BUFSIZE];

	getcwd(dirname, BUFSIZE);
	ft_putstr(dirname);
	write(1, "\n", 1);
}

//  проверка и выполнение вызова
void		call_check(char *buf, char **env)
{
	char	**call;

	if ((call = ft_strsplit(buf, ' ')) != NULL)
	{
		init_call(call, env);
		if (ft_strcmp(call[0], "pwd") == 0)
			execute_pwd();
		if (ft_strcmp(call[0], "cd") == 0)
			execute_cd(call, env);
	}
	ft_freestrsplit(call);
}

int			main(int ac, char **av, char **env)
{
	char	buf[BUFSIZE];
	int		n;

	(void)ac;
	(void)av;
	while (21)
	{
		write(1, "$>", 2);
		n = read(1, buf, BUFSIZE);
		buf[n - 1] = 0;
		call_check(buf, env);
	}
	return (0);
}
