/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 14:35:27 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/29 14:46:46 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_bunfile_sup(char *filename)
{
	ft_putstr(filename);
	write(1, "\n", 1);
	return (0);
}

int			check_binfile(char *filename)
{
	struct stat	fstat;

	stat(filename, &fstat);
	if (access(filename, F_OK))
	{
		ft_putstr("minishell: no such file or directory: ");
		return (check_bunfile_sup(filename));
	}
	else if (S_ISDIR(fstat.st_mode))
	{
		ft_putstr("minishell: is a directory: ");
		return (check_bunfile_sup(filename));
	}
	else if (access(filename, X_OK))
	{
		ft_putstr("minishell: permission denied: ");
		return (check_bunfile_sup(filename));
	}
	return (1);
}

void		execute_bin(char **call, char **env, char **new_env)
{
	if (ft_strchr(call[0], '/') != 0)
	{
		if (check_binfile(call[0]) == 0)
			return ;
		if (fork() == 0)
			execve(call[0], call, new_env);
		else
			wait(NULL);
		return ;
	}
	else if (execute_sysbin(call, env, new_env) == 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(call[0]);
		write(1, "\n", 1);
		return ;
	}
}
