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

int			check_bunfile_sup(char *filepath, char *temp, char *filename)
{
	if (filepath)
		free(filepath);
	if (temp)
		free(temp);
	ft_putstr("./");
	ft_putstr(filename);
	write(1, "\n", 1);
	return (0);
}

int			check_binfile(char *filename, char *path)
{
	char		*filepath;
	struct stat	fstat;
	char		*temp;

	temp = ft_strjoin(path, "/");
	filepath = ft_strjoin(temp, filename);
	stat(filepath, &fstat);
	if (access(filepath, F_OK))
	{
		ft_putstr("minishell: no such file or directory: ");
		return (check_bunfile_sup(filepath, temp, filename));
	}
	else if (S_ISDIR(fstat.st_mode))
	{
		ft_putstr("minishell: is a directory: ");
		return (check_bunfile_sup(filepath, temp, filename));
	}
	else if (access(filepath, X_OK))
	{
		ft_putstr("minishell: permission denied: ");
		return (check_bunfile_sup(filepath, temp, filename));
	}
	free(filepath);
	free(temp);
	return (1);
}

void		execute_bin(char **call, char **env, char **new_env)
{
	if (ft_strncmp(call[0], "./", 2) == 0)
	{
		if (check_binfile(&(call[0][2]), "./") == 0)
			return ;
		if (fork() == 0)
			execve(&(call[0][2]), call + 1, new_env);
		else
			wait(NULL);
		return ;
	}
	if (execute_sysbin(call, env, new_env) == 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(call[0]);
		write(1, "\n", 1);
		return ;
	}
}
